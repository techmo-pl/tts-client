#include <grpc++/grpc++.h>
#include <google/protobuf/text_format.h>

#include "tribune_tts.grpc.pb.h"
#include "tribune_client.h"


namespace techmo { namespace tribune {

SynthesizeRequest build_request(const TribuneClientConfig& config, const std::string& text) {
    if(config.encoding == AudioEncoding::OGG_OPUS and config.sample_rate_hertz != 0 ){
        throw std::runtime_error("Custom sample rate is not supported with Opus compression.");
    }

    SynthesizeRequest request;
    request.set_text(text);
    request.mutable_config()->set_sample_rate_hertz(config.sample_rate_hertz);
    request.mutable_config()->set_use_opus(config.use_opus);
    return request;
}

std::string protobuf_message_to_string(const google::protobuf::Message& message) {
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

std::string grpc_status_to_string(const grpc::Status& status) {
    // Status codes and their use in gRPC explanation can be found here:
    // https://github.com/grpc/grpc/blob/master/doc/statuscodes.md
    // https://grpc.io/grpc/cpp/namespacegrpc.html#aff1730578c90160528f6a8d67ef5c43b
    const std::string status_string = [&status]() {
        using code = grpc::StatusCode;
        switch (status.error_code()) {
        // Based on https://grpc.io/grpc/cpp/impl_2codegen_2status__code__enum_8h_source.html
            case code::OK: return "OK";
            case code::CANCELLED: return "CANCELLED";
            case code::UNKNOWN: return "UNKNOWN";
            case code::INVALID_ARGUMENT: return "INVALID_ARGUMENT";
            case code::DEADLINE_EXCEEDED: return "DEADLINE_EXCEEDED";
            case code::NOT_FOUND: return "NOT_FOUND";
            case code::ALREADY_EXISTS: return "ALREADY_EXISTS";
            case code::PERMISSION_DENIED: return "PERMISSION_DENIED";
            case code::UNAUTHENTICATED: return "UNAUTHENTICATED";
            case code::RESOURCE_EXHAUSTED: return "RESOURCE_EXHAUSTED";
            case code::FAILED_PRECONDITION: return "FAILED_PRECONDITION";
            case code::ABORTED: return "ABORTED";
            case code::OUT_OF_RANGE: return "OUT_OF_RANGE";
            case code::UNIMPLEMENTED: return "UNIMPLEMENTED";
            case code::INTERNAL: return "INTERNAL";
            case code::UNAVAILABLE: return "UNAVAILABLE";
            case code::DATA_LOSS: return "DATA_LOSS";
            case code::DO_NOT_USE: return "DO_NOT_USE";
            default: return "Status code not recognized";
        }
    }();

    return status_string + " (" + std::to_string(status.error_code()) + ") " + status.error_message();
}


TribuneAudioData TribuneClient::Synthesize(const TribuneClientConfig& config, const std::string& text) {
    const SynthesizeRequest request = build_request(config, text);

    auto stub = TTS::NewStub(grpc::CreateChannel(service_address_, grpc::InsecureChannelCredentials()));

    grpc::ClientContext context;
    if (not config.session_id.empty()) {
        context.AddMetadata("session_id", config.session_id);
    }
    if (config.grpc_timeout > 0) {
        context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds{ config.grpc_timeout });
    }

    auto reader = stub->Synthesize(&context, request);

    std::string received_audio_bytes = "";
    unsigned int received_sample_rate_hertz = 0;
    SynthesizeResponse response;
    while (reader->Read(&response)) {
        if (error_response(response)) {
            break;
        }

        const auto& audio = response.audio();
        if (received_sample_rate_hertz == 0) {
            if (audio.sample_rate_hertz() == 0) {
                throw std::runtime_error{"Received audio's sample rate 0."};
            }
            received_sample_rate_hertz = audio.sample_rate_hertz();
        }
        else if (audio.sample_rate_hertz() != received_sample_rate_hertz) {
            throw std::runtime_error{"Received audio's sample rate does not match previously received."};
        }

        if (config.sample_rate_hertz != 0 and received_sample_rate_hertz != config.sample_rate_hertz) {
            throw std::runtime_error{"Received audio's sample rate does not match requested."};
        }

        received_audio_bytes += audio.content();

        if (audio.end_of_stream()) {
            break;
        }
    }

    const grpc::Status status = reader->Finish();

    if (not status.ok()) {
        std::cerr << "Synthesize RPC failed with status " << grpc_status_to_string(status) << std::endl;
    }

    return TribuneAudioData{ received_sample_rate_hertz, received_audio_bytes };
}

}}
