#ifndef __TRIBUNE_CLIENT_H__
#define __TRIBUNE_CLIENT_H__


namespace techmo { namespace tribune {

struct TribuneClientConfig {
    std::string session_id = "";            // Session ID to be passed to the service. If not specified, the service will generate a default session ID itself.
    unsigned int sample_rate_hertz = 44100; // Sample rate in Hz of synthesized audio.
};

class TribuneClient {
public:
    TribuneClient(const std::string& service_address) : service_address_{ service_address } {}

    // Returns synthesized audio bytes.
    std::string Synthesize(const TribuneClientConfig& config, const std::string& text);

private:
    TribuneClient(); // Disable default constructor.

    const std::string service_address_;    // IP address and port (address:port) of a service the client will connect to.
};

}}


#endif //__TRIBUNE_CLIENT_H__
