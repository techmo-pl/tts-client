#include <iostream>

#include <boost/program_options.hpp>

#include "wave-utils.h"
#include "tribune_client.h"
#include "VERSION.h"


namespace po = boost::program_options;

po::options_description CreateOptionsDescription(void) {
    // command line options
    po::options_description optionsDescription("Tribune TTS gRPC client options:");
    optionsDescription.add_options()
            ("help", "Print help message.")
            ("service-address", po::value<std::string>()->required(),
             "IP address and port (address:port) of a service the client will connect to.")
            ("out-path", po::value<std::string>()->default_value("TechmoTTS.wav"),
             "Path to output wave file with synthesized audio content.")
            ("text", po::value<std::string>()->default_value("Techmo Trybun: Syntezator mowy polskiej."),
             "Text to be synthesized (in polish).")
            ("session-id", po::value<std::string>()->default_value(""),
             "Session ID to be passed to the service. If not specified, the service will generate a default session ID itself.")
            ("grpc-timeout", po::value<int>()->default_value(0), "Timeout in milliseconds used to set gRPC deadline - "
             "how long the client is willing to wait for a reply from the server. "
             "If not specified, the service will set the deadline to a very large number.")
            ("sample-rate-hertz", po::value<unsigned int>()->default_value(0),
             "Sample rate in Hz of synthesized audio. Set to 0 (default) to use voice's original sample rate.");
    return optionsDescription;
}

int main(int argc, const char *const argv[]) {
    po::options_description optionsDescription(CreateOptionsDescription());
    po::variables_map userOptions;
    try {
        po::store(po::command_line_parser(argc, argv).options(optionsDescription).run(), userOptions);

        std::cout << "Tribune TTS gRPC client " << LIBTRIBUNE_CLIENT_VERSION << std::endl;

        if (userOptions.empty() or userOptions.count("help")) {
            std::cout << optionsDescription;
            return 0;
        }

        po::notify(userOptions);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cout << optionsDescription;
        return 1;
    }

    try {
        const auto sample_rate_hertz = userOptions["sample-rate-hertz"].as<unsigned int>();

        techmo::tribune::TribuneClientConfig config;
        config.session_id = userOptions["session-id"].as<std::string>();
        config.grpc_timeout = userOptions["grpc-timeout"].as<int>();
        config.sample_rate_hertz = sample_rate_hertz;

        techmo::tribune::TribuneClient tribune_client{ userOptions["service-address"].as<std::string>() };

        const auto audio_data = tribune_client.Synthesize(config, userOptions["text"].as<std::string>());

        WriteWaveFile(userOptions["out-path"].as<std::string>(), audio_data.sample_rate_hertz, audio_data.audio_bytes);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
