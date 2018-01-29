#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

#include "tribune_client.h"
#include "VERSION.h"


namespace po = boost::program_options;

/// WAVE file header structure
struct WAV_HEADER//from sarmata/utils/WaveFile.h
{
    char               RIFF[4];        // RIFF Header      Magic header
    unsigned int       ChunkSize;      // RIFF Chunk Size
    char               WAVE[4];        // WAVE Header
    char               fmt[4];         // FMT header
    unsigned int       Subchunk1Size;  // Size of the fmt chunk
    unsigned short     AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    unsigned short     NumOfChan;      // Number of channels 1=Mono 2=Sterio
    unsigned int       SamplesPerSec;  // Sampling Frequency in Hz
    unsigned int       bytesPerSec;    // bytes per second
    unsigned short     blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    unsigned short     bitsPerSample;  // Number of bits per sample
    char               Subchunk2ID[4]; // "data"  string
    unsigned int       Subchunk2Size;  // Sampled data length
};

void write_wave_file(const std::string & wave_path, unsigned int sample_rate, const std::string & audio_bytes)
{
    std::fstream wave_file(wave_path, std::ios::binary | std::ios::trunc | std::ios::out);

    WAV_HEADER _header;
    memcpy(_header.RIFF, "RIFF", 4);
    _header.ChunkSize = 36 + 0;
    memcpy(_header.WAVE, "WAVE", 4);
    memcpy(_header.fmt, "fmt ", 4);
    _header.Subchunk1Size = 16;
    _header.AudioFormat = 1;
    _header.NumOfChan = 1;
    _header.SamplesPerSec = sample_rate;
    _header.bytesPerSec = sample_rate * 1 * 16/8;
    _header.blockAlign = 1 * 16/8;
    _header.bitsPerSample = 16;
    memcpy(_header.Subchunk2ID, "data", 4);
    _header.Subchunk2Size = 0;
    _header.Subchunk2Size = (unsigned)audio_bytes.size();
    _header.ChunkSize = 36 + _header.Subchunk2Size;

    wave_file.write((char*)(&_header), sizeof(_header));
    wave_file.write((char*)&audio_bytes[0], audio_bytes.size());
    wave_file.flush();
}

po::options_description CreateHelpOptions(void) {
    // command line options
    po::options_description helpOptions("Tribune TTS gRPC client options:");
    helpOptions.add_options()
            ("help", "Print help message.")
            ("service-address", po::value<std::string>(),
             "IP address and port (address:port) of a service the client will connect to.")
            ("out-path", po::value<std::string>()->default_value("TechmoTTS.wav"),
             "Path to output wave file with synthesized audio content.")
            ("text", po::value<std::string>()->default_value("Techmo Trybun: Syntezator mowy polskiej."),
             "Text to be synthesized (in polish).")
            ("session-id", po::value<std::string>()->default_value(""),
             "Session ID to be passed to the service. If not specified, the service will generate a default session ID itself.")
            ("sample-rate-hertz", po::value<unsigned int>()->default_value(44100),
             "Sample rate in Hz of synthesized audio.");
    return helpOptions;
}

int main(int argc, const char *const argv[]) {
    po::options_description helpOptions(CreateHelpOptions());
    po::variables_map userOptions;
    try {
        po::store(po::command_line_parser(argc, argv).options(helpOptions).run(), userOptions);
        po::notify(userOptions);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (userOptions.count("help")) {
        std::cout << helpOptions;
        return 0;
    }

    std::cout << "Tribune TTS gRPC client " << LIBTRIBUNE_CLIENT_VERSION << std::endl;

    if (not userOptions.count("service-address")) {//bad usage
        std::cerr << "Usage: " << argv[0] << " --service-address host:address --out-path /path/to/output.wav --text \"Polski tekst do syntezy\"" << std::endl;
        return 1;
    }

    try {
        const auto sample_rate_hertz = userOptions["sample-rate-hertz"].as<unsigned int>();

        techmo::tribune::TribuneClientConfig config;
        config.session_id = userOptions["session-id"].as<std::string>();
        config.sample_rate_hertz = sample_rate_hertz;

        techmo::tribune::TribuneClient tribune_client{ userOptions["service-address"].as<std::string>() };

        const auto audio_bytes = tribune_client.Synthesize(config, userOptions["text"].as<std::string>());

        write_wave_file(userOptions["out-path"].as<std::string>(), sample_rate_hertz, audio_bytes);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
