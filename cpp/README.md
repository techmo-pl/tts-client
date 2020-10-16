C++ implementation of Tribune TTS gRPC client.

Contents:
- `libtribune-client`     Library implementing communication with Techmo Tribune TTS gRPC service.
- `tribune-client`        Example of program using the library.

This project uses cmake build.

Dependencies are:  
- Boost     provided as `boost_pkg`  
    Default location: `/opt/boost_1.60.0`  
    If not installed, from parent directory run `sudo ./tools/install_boost.sh`  
- gRPC      provided as `grpc_pkg`  
    Default location: `/opt/grpc_v1.24.3`  
    If not installed, from parent directory run `sudo ./tools/install_grpc.sh`  
- OpenSSL   provided as `ssl_pkg`  
- DL        provided as `dl_pkg`  

To regenerate sources from `.proto`, run:
```
./make_proto.sh
```
This might be required when using other gRPC or Protocol Buffers version.

Build:
```
mkdir build && cd build && cmake .. && make -j 4
```

Run:
```
./build/tribune_client --service-address 192.168.1.1:4321 --text "Polski tekst do syntezy."
```

Options:
```
--help                Print help message.
--service-address     IP address and port (address:port) of a service the client will connect to.
--out-path            Path to output wave file with synthesized audio content (optional, default: TechmoTTS.wav or TechmoTTS.ogg).
--text                Text to be synthesized (optional, default: 'Techmo Trybun: Syntezator mowy polskiej.').
--session-id          Session ID to be passed to the service. If not specified, the service generates a default session ID itself.
--grpc-timeout        Timeout in milliseconds used to set gRPC deadline - how long the client is willing to wait for a reply from the 
                      server. If not specified, the service will set the deadline to a very large number (optional, default: 0).
--audio-encoding      Encoding of the output audio, pcm16 (default) or ogg-vorbs.
--sample-rate-hertz   Sample rate in Hz of synthesized audio. Set to 0 (default) to use voice's original sample rate.
--speech-pitch        Allows adjusting the default pitch of the synthesized speech (optional, can be overriden by SSML).
--speech-range        Allows adjusting the default range of the synthesized speech (optional, can be overriden by SSML).
--speech-rate         Allows adjusting the default rate (speed) of the synthesized speech (optional, can be overriden by SSML).
--speech-volume       Allows adjusting the default volume of the synthesized speech (optional, can be overriden by SSML).
--voice-name          Name od the voice used to synthesize the phrase (optional, can be overriden by SSML).
--voice-gender        Gender of the voice - female or male (optional, can be overriden by SSML).
--voice-age           Age of the voice - adult, child, or senile (optional, can be overriden by SSML).
--language            ISO 639-1 language code of the phrase to synthesize (optional, can be overriden by SSML).
```

The input text can be either a plain text or SSML (https://w3.org/TR/speech-synthesis11/).
Currently the following SSML tags are supported:
- `<speak>` - root xml node, with optional `xml:lang` attribute,
- `<prosody>` - supported attributes: `pitch`, `range`, `rate`, and `volume`,
- `<break>` - supported attributes: `strength` and `time`,
- `<emphasis>` - supported attribute: `level`,
- `<say-as>` - supported attribute: `interpret-as` (consult Techmo TTS documentation for the complete list of all available implementations),
- `<lang>` - supported attribute: `xml:lang`,
- `<voice>` - supported attributes: `name`, `gender`, and `age`.
