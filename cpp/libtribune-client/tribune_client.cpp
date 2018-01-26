#include <grpc++/grpc++.h>
#include <google/protobuf/text_format.h>

#include "TTS.grpc.pb.h"
#include "tribune_client.h"


namespace techmo { namespace tribune {

SynthesizeRequest build_request(const TribuneClientConfig& config, const std::string& text) {
    SynthesizeRequest request;
    request.set_text(text);
    request.mutable_config()->set_sample_rate_hertz(config.sample_rate_hertz);
    return request;
}

std::string protobuf_message_to_string(const google::protobuf::Message & message)
{
    grpc::string out_str;
    google::protobuf::TextFormat::PrintToString(message, &out_str);
    return out_str;
}

bool error_response(const SynthesizeResponse& response) {
    const auto is_error = response.has_error();

    if (is_error) {
        std::cerr << "Received error response: (" << protobuf_message_to_string(response.error()) << std::endl;
    }

    return is_error;
}


std::string TribuneClient::Synthesize(const TribuneClientConfig& config, const std::string& text) {
    grpc::ClientContext context;
    if (not config.session_id.empty()) {
        context.AddMetadata("session_id", config.session_id);
    }

    const SynthesizeRequest request = build_request(config, text);

    auto stub = TTS::NewStub(grpc::CreateChannel(service_address_, grpc::InsecureChannelCredentials()));

    auto reader = stub->Synthesize(&context, request);

    std::string received_audio_bytes = "";
    SynthesizeResponse response;
    while (reader->Read(&response)) {
        if (error_response(response)) {
            break;
        }

        const auto& audio = response.audio();

        if (audio.sample_rate_hertz() != config.sample_rate_hertz) {
            throw std::runtime_error{"Reveived audio's sample rate does not match requested."};
        }

        received_audio_bytes += audio.content();

        if (audio.end_of_stream()) {
            break;
        }
    }

    const grpc::Status status = reader->Finish();

    if (not status.ok()) {
        std::cerr << "Synthesize RPC failed with status " << status.error_code() << " " << status.error_message() << std::endl;
    }

    return received_audio_bytes;
}

}}
