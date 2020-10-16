#ifndef __TRIBUNE_CLIENT_H__
#define __TRIBUNE_CLIENT_H__

#include <optional>
#include <string>
#include "tribune_tts.grpc.pb.h"

namespace techmo::tribune
{
	// Desfines the parameters of synthesized speech.
	struct SynthesizeAudioConfig
	{
		// Encoding of the output data stream. Either PCM16 without any header or Ogg/Vorbis.
		AudioEncoding encoding{ AudioEncoding::PCM16 };

		// Sample rate in Hz of synthesized audio. If set to 0, the service will use voice's originalsynthesizer default sample rate.
		int sample_rate_hertz{ 0 };

		// The average speech pitch scaling factor. The value 1.0 is a neutral value.
		float pitch{ 1.0f };

		// The speech range scaling factor. The value 1.0 is a neutral value.
		float range{ 1.0f };

		// The speech rate (speed) scaling factor. The value 1.0 is a neutral value.
		float rate{ 1.0f };

		// The speech volume scaling factor. The value 1.0 is a neutral value.
		float volume{ 1.0f };
	};

	// Voice definition. If there is no voice satisfying all the required criteria,
	// the voice is selected according to name (if defined) first, gender (if defined) second,
	// and age (if defined) third.
	struct SynthesizeVoice
	{
		// The name of the voice (empty string means default voice).
		std::string name;

		// Gender of the voice (GENDER_UNSPECIFIED is default).
		Gender gender{ Gender::GENDER_UNSPECIFIED };

		// Age of the voice (AGE_UNSPECIFIED is default).
		Age age{ Age::AGE_UNSPECIFIED };
	};

	struct TribuneClientConfig
	{
		// Session ID to be passed to the service. If not specified, the service will generate a default session ID itself.
		// Session ID is the best way to match log's from client application with these on server side.
		std::string session_id;

		// Timeout in milliseconds used to set gRPC deadline - how long the client is willing to wait for a reply from the server.
		int grpc_timeout{ 0 };

		// ISO 639-1 code of the language of text to be synthesized (optional, may be overriden by SSML tags in request text).
		std::string language;

		// Parameters to configure the audio synthesis (optional).
		std::optional<SynthesizeAudioConfig> audio_config;

		// Requested voice to be used to synthesize the text (may be overriden by SSML tags in request text).
		std::optional<SynthesizeVoice> voice;
	};

	struct TribuneAudioData
	{
		// Sample rate in Hz of received audio data.
		unsigned int sample_rate_hertz = 0;

		// Received audio data.
		std::string audio_bytes = "";
	};

	class TribuneClient
	{
	public:
		TribuneClient(const std::string& service_address) : service_address_{ service_address } {}

		// Returns synthesized audio bytes.
		TribuneAudioData Synthesize(const TribuneClientConfig& config, const std::string& text);

	private:
		const std::string service_address_;
	};

}

#endif //__TRIBUNE_CLIENT_H__
