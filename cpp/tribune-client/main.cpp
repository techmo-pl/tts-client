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
		("text", po::value<std::string>()->default_value("Techmo Trybun: Syntezator mowy."),
			"Text to be synthesized.")
		("session-id", po::value<std::string>()->default_value(""),
			"Session ID to be passed to the service. If not specified, the service will generate a default session ID itself.")
		("grpc-timeout", po::value<int>()->default_value(0), "Timeout in milliseconds used to set gRPC deadline - "
			"how long the client is willing to wait for a reply from the server. "
			"If not specified, the service will set the deadline to a very large number.")
		("list-voices", "Lists all available voices.")
		("response", po::value<std::string>()->default_value("streaming"),
			"streaming or single, calls the streaming (default) or non-streaming version of Synthesize.")
		("audio-encoding", po::value<std::string>()->default_value("pcm16"),
			"Encoding of the output audio, pcm16 (default) or ogg-vorbs.")
		("sample-rate-hertz", po::value<unsigned int>()->default_value(0),
			"Sample rate in Hz of synthesized audio. Set to 0 (default) to use voice's original sample rate.")
		("speech-pitch", po::value<float>()->default_value(1.0f),
			"Allows adjusting the default pitch of the synthesized speech (optional, can be overriden by SSML).")
		("speech-range", po::value<float>()->default_value(1.0f),
			"Allows adjusting the default range of the synthesized speech (optional, can be overriden by SSML).")
		("speech-rate", po::value<float>()->default_value(1.0f),
			"Allows adjusting the default rate (speed) of the synthesized speech (optional, can be overriden by SSML).")
		("speech-volume", po::value<float>()->default_value(1.0f),
			"Allows adjusting the default volume of the synthesized speech (optional, can be overriden by SSML).")
		("voice-name", po::value<std::string>()->default_value(""),
			"Name od the voice used to synthesize the phrase (optional, can be overriden by SSML).")
		("voice-gender", po::value<std::string>()->default_value(""),
			"Gender of the voice - female or male (optional, can be overriden by SSML).")
		("voice-age", po::value<std::string>()->default_value(""),
			"Age of the voice - adult, child, or senile (optional, can be overriden by SSML).")
		("language", po::value<std::string>()->default_value(""),
			"ISO 639-1 language code of the phrase to synthesize (optional, can be overriden by SSML).");
	return optionsDescription;
}

void printVoices(const std::vector<techmo::tribune::SynthesizeVoiceInfo>& voices);
techmo::tribune::AudioEncoding encodingFromString(std::string_view encodingString);
techmo::tribune::Gender genderFromString(std::string_view genderString);
techmo::tribune::Age ageFromString(std::string_view ageString);

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
		techmo::tribune::TribuneClient tribuneClient{ userOptions["service-address"].as<std::string>() };

		techmo::tribune::TribuneClientConfig clientConfig;
		clientConfig.session_id = userOptions["session-id"].as<std::string>();
		clientConfig.grpc_timeout = userOptions["grpc-timeout"].as<int>();

		if (userOptions.count("list-voices"))
		{
			printVoices(tribuneClient.ListVoices(
				clientConfig, userOptions["language"].as<std::string>()));
			return 0;
		}

		techmo::tribune::AudioEncoding encoding{
			encodingFromString(userOptions["audio-encoding"].as<std::string>()) };

		techmo::tribune::TribuneSynthesizeConfig synthesizeConfig;
		synthesizeConfig.language = userOptions["language"].as<std::string>();
		synthesizeConfig.audio_config.emplace();
		synthesizeConfig.audio_config->encoding = encoding;
		synthesizeConfig.audio_config->sample_rate_hertz = userOptions["sample-rate-hertz"].as<int>();
		synthesizeConfig.audio_config->pitch = userOptions["speech-pitch"].as<float>();
		synthesizeConfig.audio_config->range = userOptions["speech-range"].as<float>();
		synthesizeConfig.audio_config->rate = userOptions["speech-rate"].as<float>();
		synthesizeConfig.audio_config->volume = userOptions["speech-volume"].as<float>();

		std::string voiceName = userOptions["voice-name"].as<std::string>();
		std::string voiceGender = userOptions["voice-gender"].as<std::string>();
		std::string voiceAge = userOptions["voice-age"].as<std::string>();
		if (!voiceName.empty() || !voiceGender.empty() || !voiceAge.empty())
		{
			synthesizeConfig.voice.emplace();
			synthesizeConfig.voice->name = voiceName;
			synthesizeConfig.voice->gender = genderFromString(voiceGender);
			synthesizeConfig.voice->age = ageFromString(voiceAge);
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

		bool useStreaming;
		if (userOptions["response"].as<std::string>() == "streaming")
		{
			useStreaming = true;
		}
		else if (userOptions["response"].as<std::string>() == "single")
		{
			useStreaming = false;
		}
		else
		{
			std::string message{ "Unsupported response: " };
			message += userOptions["response"].as<std::string>();
			message += ".";
			throw std::runtime_error{ message };
		}

		std::string requestText = userOptions["text"].as<std::string>();
		const auto audio_data = (useStreaming ?
			tribuneClient.SynthesizeStreaming(clientConfig, synthesizeConfig, requestText) :
			tribuneClient.Synthesize(clientConfig, synthesizeConfig, requestText));

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

void printVoices(const std::vector<techmo::tribune::SynthesizeVoiceInfo>& voices)
{
	std::cout << std::endl << "Available voices:" << std::endl;
	for (const auto& voice: voices)
	{
		std::cout << "name: '" << voice.voice.name << "'" << std::endl;
		std::cout << "gender: " << voice.voice.gender << std::endl;
		std::cout << "age: " << voice.voice.age << std::endl << std::endl;
	}
}

techmo::tribune::AudioEncoding encodingFromString(std::string_view encodingString)
{
	if (encodingString.empty() || encodingString == "pcm16")
	{
		return techmo::tribune::AudioEncoding::PCM16;
	}
	if (encodingString == "ogg-vorbis")
	{
		return techmo::tribune::AudioEncoding::OGG_VORBIS;
	}

	std::string message{ "Unsupported audio-encoding: " };
	message += encodingString;
	message += ".";
	throw std::runtime_error{ message };
}

techmo::tribune::Gender genderFromString(std::string_view genderString)
{
	if (genderString == "female")
	{
		return techmo::tribune::Gender::FEMALE;
	}
	else if (genderString == "male")
	{
		return techmo::tribune::Gender::MALE;
	}
	else if (genderString.empty())
	{
		return techmo::tribune::Gender::GENDER_UNSPECIFIED;
	}

	std::string message{ "Unsupported voice-gender: " };
	message += genderString;
	message += ".";
	throw std::runtime_error{ message };
}

techmo::tribune::Age ageFromString(std::string_view ageString)
{
	if (ageString == "adult")
	{
		return techmo::tribune::Age::ADULT;
	}
	else if (ageString == "child")
	{
		return techmo::tribune::Age::CHILD;
	}
	else if (ageString == "senile")
	{
		return techmo::tribune::Age::SENILE;
	}
	else if (ageString.empty())
	{
		return techmo::tribune::Age::AGE_UNSPECIFIED;
	}

	std::string message{ "Unsupported voice-age: " };
	message += ageString;
	message += ".";
	throw std::runtime_error{ message };
}
