#ifndef __TRIBUNE_CLIENT_H__
#define __TRIBUNE_CLIENT_H__


namespace techmo { namespace tribune {

struct TribuneClientConfig {
    std::string session_id = "";            // Session ID to be passed to the service. If not specified, the service will generate a default session ID itself.
                                            // Session ID is the best way to match log's from client application with these on server side.
    int grpc_timeout = 0;                   // Timeout in milliseconds used to set gRPC deadline - how long the client is willing to wait for a reply from the server.
    unsigned int sample_rate_hertz = 0;     // Sample rate in Hz of synthesized audio. If set to 0, the service will use voice's original sample rate.
};

struct TribuneAudioData {
    unsigned int sample_rate_hertz = 0;     // Sample rate in Hz of received audio data.
    std::string audio_bytes = "";           // Received audio data.
};

class TribuneClient {
public:
    TribuneClient(const std::string& service_address) : service_address_{ service_address } {}

    // Returns synthesized audio bytes.
    TribuneAudioData Synthesize(const TribuneClientConfig& config, const std::string& text);

private:
    TribuneClient(); // Disable default constructor.

    const std::string service_address_;    // IP address and port (address:port) of a service the client will connect to.
};

}}


#endif //__TRIBUNE_CLIENT_H__
