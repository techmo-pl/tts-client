#include <grpc++/grpc++.h>
#include <google/protobuf/text_format.h>
#include "Client.h"

namespace techmo::tts
{
	void build_context(grpc::ClientContext& context, const ClientConfig& clientConfig)
	{
		if (!clientConfig.session_id.empty())
		{
			context.AddMetadata("session_id", clientConfig.session_id);
		}

		if (clientConfig.grpc_timeout > 0)
		{
			context.set_deadline(std::chrono::system_clock::now()
				+ std::chrono::milliseconds{ clientConfig.grpc_timeout });
		}
	}

	grpc_api::SynthesizeRequest build_request(const SynthesizeConfig& input_config, std::string_view text)
	{
		grpc_api::SynthesizeRequest request;
		request.set_text(std::string{ text });
		grpc_api::SynthesizeConfig* grpc_synthesize_config = request.mutable_config();

		grpc_synthesize_config->set_language(input_config.language);

		if (input_config.audio_config)
		{
			const ClientAudioConfig& input_audio_config = *input_config.audio_config;
			grpc_api::AudioConfig* grpc_audio_config = grpc_synthesize_config->mutable_audio_config();

			grpc_audio_config->set_audio_encoding(input_audio_config.encoding);
			grpc_audio_config->set_sample_rate_hertz(input_audio_config.sample_rate_hertz);
			grpc_audio_config->set_pitch(input_audio_config.pitch);
			grpc_audio_config->set_range(input_audio_config.range);
			grpc_audio_config->set_rate(input_audio_config.rate);
			grpc_audio_config->set_volume(input_audio_config.volume);
		}

		if (input_config.voice)
		{
			const Voice& input_voice = *input_config.voice;
			grpc_api::Voice* grpc_voice = grpc_synthesize_config->mutable_voice();

			grpc_voice->set_name(input_voice.name);
			grpc_voice->set_gender(input_voice.gender);
			grpc_voice->set_age(input_voice.age);
		}

		return request;
	}

	std::string protobuf_message_to_string(const google::protobuf::Message& message)
	{
		grpc::string out_str;
		google::protobuf::TextFormat::PrintToString(message, &out_str);
		return out_str;
	}

	std::string grpc_status_to_string(const grpc::Status& status)
	{
		// Status codes and their use in gRPC explanation can be found here:
		// https://github.com/grpc/grpc/blob/master/doc/statuscodes.md
		// https://grpc.io/grpc/cpp/namespacegrpc.html#aff1730578c90160528f6a8d67ef5c43b
		const std::string status_string = [&status]()
		{
			using code = grpc::StatusCode;
			switch (status.error_code())
			{
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

	void fillVoiceInfo(VoiceInfo& voiceInfo, const grpc_api::VoiceInfo& grpcVoiceInfo)
	{
		for (int i = 0; i < grpcVoiceInfo.supported_languages_size(); ++i)
		{
			voiceInfo.supported_languages.push_back(grpcVoiceInfo.supported_languages(i));
		}
		voiceInfo.voice.name = grpcVoiceInfo.voice().name();
		voiceInfo.voice.gender = grpcVoiceInfo.voice().gender();
		voiceInfo.voice.age = grpcVoiceInfo.voice().age();
	}

	std::vector<VoiceInfo> Client::ListVoices(
		const ClientConfig& clientConfig,
		std::string_view language) const
	{
		auto stub = grpc_api::TTS::NewStub(grpc::CreateChannel(m_serviceAddress, grpc::InsecureChannelCredentials()));
		grpc::ClientContext context;
		build_context(context, clientConfig);

		grpc_api::ListVoicesRequest request;
		request.set_language(std::string{ language });
		grpc_api::ListVoicesResponse response;
		grpc::Status status = stub->ListVoices(&context, request, &response);
		if (status.ok())
		{
			std::vector<VoiceInfo> voices;
			for (int i = 0; i < response.voices_size(); ++i)
			{
				VoiceInfo voiceInfo;
				fillVoiceInfo(voiceInfo, response.voices(i));
				voices.push_back(voiceInfo);
			}
			return voices;
		}
		else
		{
			throw std::runtime_error{ "Synthesize RPC failed with status "
				+ grpc_status_to_string(status) };
		}
	}

	AudioData Client::SynthesizeStreaming(
		const ClientConfig& clientConfig,
		const SynthesizeConfig& synthesizeConfig,
		std::string_view text) const
	{
		auto stub = grpc_api::TTS::NewStub(grpc::CreateChannel(m_serviceAddress, grpc::InsecureChannelCredentials()));
		grpc::ClientContext context;
		build_context(context, clientConfig);

		const grpc_api::SynthesizeRequest request = build_request(synthesizeConfig, text);

		auto reader = stub->SynthesizeStreaming(&context, request);

		std::string received_audio_bytes;
		int received_sample_rate_hertz{ 0 };
		grpc_api::SynthesizeResponse response;

		int requested_sample_rate_hertz{ 0 };
		if (synthesizeConfig.audio_config)
		{
			requested_sample_rate_hertz = synthesizeConfig.audio_config->sample_rate_hertz;
		}

		while (reader->Read(&response))
		{
			if (response.has_error())
			{
				throw std::runtime_error{ "Received error response: ("
					+ protobuf_message_to_string(response.error()) };
			}

			const auto& audio = response.audio();
			if (received_sample_rate_hertz == 0)
			{
				if (audio.sample_rate_hertz() == 0)
				{
					throw std::runtime_error{ "Received audio's sample rate 0." };
				}
				received_sample_rate_hertz = audio.sample_rate_hertz();
			}
			else if (audio.sample_rate_hertz() != received_sample_rate_hertz)
			{
				throw std::runtime_error{ "Received audio's sample rate does not match previously received." };
			}

			if (requested_sample_rate_hertz != 0 && received_sample_rate_hertz != requested_sample_rate_hertz)
			{
				throw std::runtime_error{ "Received audio's sample rate does not match requested." };
			}

			received_audio_bytes += audio.content();
		}

		const grpc::Status status = reader->Finish();

		if (!status.ok())
		{
			throw std::runtime_error{ "SynthesizeStreaming RPC failed with status "
				+ grpc_status_to_string(status) };
		}

		return AudioData{ received_sample_rate_hertz, received_audio_bytes };
	}

	AudioData Client::Synthesize(
		const ClientConfig& clientConfig,
		const SynthesizeConfig& synthesizeConfig,
		std::string_view text) const
	{
		auto stub = grpc_api::TTS::NewStub(grpc::CreateChannel(m_serviceAddress, grpc::InsecureChannelCredentials()));
		grpc::ClientContext context;
		build_context(context, clientConfig);

		const grpc_api::SynthesizeRequest request = build_request(synthesizeConfig, text);
		grpc_api::SynthesizeResponse response;
		grpc::Status status = stub->Synthesize(&context, request, &response);
		if (status.ok())
		{
			if (response.has_error())
			{
				throw std::runtime_error{ "Received error response: ("
					+ protobuf_message_to_string(response.error()) };
			}
			return response.has_audio() ? AudioData{
				response.audio().sample_rate_hertz(), response.audio().content() } : AudioData{ };
		}
		else
		{
			throw std::runtime_error{ "Synthesize RPC failed with status "
				+ grpc_status_to_string(status) };
		}
	}
}
