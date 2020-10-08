#include <iostream>
#include <stdexcept>
#include <boost/program_options.hpp>
#include <TribuneClient.h>
#include "AudioUtils.h"
#include "VERSION.h"

namespace po = boost::program_options;

po::options_description CreateOptionsDescription(void)
{
	po::options_description optionsDescription("Tribune TTS gRPC client options:");
	optionsDescription.add_options()
		("help", "Print help message.")
		("service-address", po::value<std::string>()->required(),
			"IP address and port (address:port) of a service the client will connect to.")
		("out-path", po::value<std::string>()->default_value(""),
			"Path to output wave file with synthesized audio content.")
		("text", po::value<std::string>()->default_value("Techmo Trybun: Syntezator mowy polskiej."),
			"Text to be synthesized.")
		("session-id", po::value<std::string>()->default_value(""),
			"Session ID to be passed to the service. If not specified, the service will generate a default session ID itself.")
		("grpc-timeout", po::value<int>()->default_value(0), "Timeout in milliseconds used to set gRPC deadline - "
			"how long the client is willing to wait for a reply from the server. "
			"If not specified, the service will set the deadline to a very large number.")
		("audio-encoding", po::value<std::string>()->default_value("pcm16"),
			"Encoding of the output audio, pcm16 (default) or ogg-vorbs.")
		("sample-rate-hertz", po::value<unsigned int>()->default_value(0),
			"Sample rate in Hz of synthesized audio. Set to 0 (default) to use voice's original sample rate.")
		("speech-pitch", po::value<float>()->default_value(0.0f),
			"Allows adjusting the default pitch of the synthesized speech (optional, can be overriden by SSML).")
		("speech-range", po::value<float>()->default_value(0.0f),
			"Allows adjusting the default range of the synthesized speech (optional, can be overriden by SSML).")
		("speech-rate", po::value<float>()->default_value(0.0f),
			"Allows adjusting the default rate (speed) of the synthesized speech (optional, can be overriden by SSML).")
		("speech-volume", po::value<float>()->default_value(0.0),
			"Allows adjusting the default volume of the synthesized speech (optional, can be overriden by SSML).")
		("voice-name", po::value<std::string>()->default_value(""),
			"Name od the voice used to synthesize the phrase (optional, can be overriden by SSML).")
		("voice-gender", po::value<std::string>()->default_value(""),
			"Gender of the voice - female or male (optional, can be overriden by SSML).")
		("language", po::value<std::string>()->default_value(""),
			"ISO 639-1 language code of the phrase to synthesize (optional, can be overriden by SSML).");
	return optionsDescription;
}

int main(int argc, const char* const argv[])
{
	po::options_description optionsDescription(CreateOptionsDescription());
	po::variables_map userOptions;
	try
	{
		po::store(po::command_line_parser(argc, argv).options(optionsDescription).run(), userOptions);

		std::cout << "Tribune TTS gRPC client " << LIBTRIBUNE_CLIENT_VERSION << std::endl;

		if (userOptions.empty() || userOptions.count("help"))
		{
			std::cout << optionsDescription;
			return 0;
		}

		po::notify(userOptions);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cout << optionsDescription;
		return 1;
	}

	try
	{
		techmo::tribune::AudioEncoding encoding{ techmo::tribune::AudioEncoding::PCM16 };
		std::string encodingOption = userOptions["audio-encoding"].as<std::string>();
		if (!encodingOption.empty())
		{
			if (encodingOption == "ogg-vorbis")
			{
				encoding = techmo::tribune::AudioEncoding::OGG_VORBIS;
			}
			else if (encodingOption != "pcm16")
			{
				throw std::runtime_error{ "Unsupported audio-encoding: " + encodingOption + "." };
			}
		}

		const auto sample_rate_hertz = userOptions["sample-rate-hertz"].as<unsigned int>();

		techmo::tribune::TribuneClientConfig config;
		config.session_id = userOptions["session-id"].as<std::string>();
		config.grpc_timeout = userOptions["grpc-timeout"].as<int>();
		config.language = userOptions["language"].as<std::string>();
		config.audio_config.emplace();
		config.audio_config->encoding = encoding;
		config.audio_config->sample_rate_hertz = sample_rate_hertz;
		config.audio_config->pitch = userOptions["speech-pitch"].as<float>();
		config.audio_config->range = userOptions["speech-range"].as<float>();
		config.audio_config->rate = userOptions["speech-rate"].as<float>();
		config.audio_config->volume = userOptions["speech-volume"].as<float>();

		std::string voiceName = userOptions["voice-name"].as<std::string>();
		std::string voiceGender = userOptions["voice-gender"].as<std::string>();
		if (!voiceName.empty() || !voiceGender.empty())
		{
			techmo::tribune::Gender gender{ techmo::tribune::Gender::UNSPECIFIED };

			if (voiceGender == "female")
			{
				gender = techmo::tribune::Gender::FEMALE;
			}
			else if (voiceGender == "male")
			{
				gender = techmo::tribune::Gender::MALE;
			}
			else if (!voiceGender.empty())
			{
				throw std::runtime_error{ "Unsupported voice-gender: " + voiceGender + "." };
			}

			config.voice.emplace();
			config.voice->name = voiceName;
			config.voice->gender = gender;
		}

		std::string outputPath = userOptions["out-path"].as<std::string>();
		if (outputPath.empty())
		{
			if (encoding == techmo::tribune::AudioEncoding::PCM16)
			{
				outputPath = "TechmoTTS.wav";
			}
			else if (encoding == techmo::tribune::AudioEncoding::OGG_VORBIS)
			{
				outputPath = "TechmoTTS.ogg";
			}
		}

		techmo::tribune::TribuneClient tribune_client{ userOptions["service-address"].as<std::string>() };

		const auto audio_data = tribune_client.Synthesize(config, userOptions["text"].as<std::string>());

		if (encoding == techmo::tribune::AudioEncoding::PCM16)
		{
			WriteWaveFile(outputPath, audio_data.sample_rate_hertz, audio_data.audio_bytes);
		}
		else
		{
			WriteEncodedFile(outputPath, audio_data.audio_bytes);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
