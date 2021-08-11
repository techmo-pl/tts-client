# C++ implementation of Techmo TTS gRPC client.


## Docker usage

#### Build docker image

To prepare docker image with c++ implementation of tts client, open project's main directory and run:

```
docker build -f Dockerfile-cpp -t tts-client-cpp:2.2.0 . 
```
**Note:** the build process may take several dozen minutes. If you don't want to wait so long, use Python implementation instead.
When the build process is complete, you will receive a message:
```
Successfully tagged tts-client-cpp:2.2.0
```

#### Run tts client

To use tts client on a Docker container, go to `tts-client/cpp/docker` directory and run `run_tts_client_cpp.sh` script.

To send simple request to the TTS service, use:
```
./run_tts_client_cpp.sh --service-address IP_ADDRESS:PORT --text "Sample text to be synthesised"
```

To print list of available options, use:
```
./run_tts_client_cpp.sh --help
```
Output audio files will be created inside `tts-client/cpp/docker/wav` directory.

**NOTE:** Unlike a local tts-client instance, the `run_tts_client_cpp.sh` script not allows to set custom paths to output files. Instead it uses predefined directory (`wav`). When using option: `--output-file (-o)`, user should provide only filename.



## Local instance usage


### Contents:
- `libtts-client`     Library implementing communication with Techmo Techmo TTS gRPC service.
- `tts-client`        Example of program using the library.

This project uses cmake build.

### Dependencies:  

- Boost     provided as `boost_pkg`  
    Default location: `/opt/boost_1_74_0`  
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

### Build:
```
mkdir build && cd build && cmake .. && make -j 4
```

### Run:
```
./build/tts_client --service-address 192.168.1.1:4321 --text "Polski tekst do syntezy."
```

Options:
```
--help                Prints this help message.
--service-address     An IP address and port (address:port) of a service the client will connect to.
--out-path            A path to output wave file with synthesized audio content (optional, default: TechmoTTS.wav or TechmoTTS.ogg).
--text                A text to be synthesized (optional, default: 'Techmo Trybun: Syntezator mowy polskiej.').
--session-id          A session ID to be passed to the service. If not specified, the service generates a default session ID itself.
--grpc-timeout        A timeout in milliseconds used to set gRPC deadline - how long the client is willing to wait for a reply from the
                      server (optional).
--list-voices         Lists all available voices.
--response            streaming or single, calls the streaming (default) or non-streaming version of Synthesize.
--audio-encoding      An encoding of the output audio, pcm16 (default) or ogg-vorbs.
--sample-rate-hertz   A sample rate in Hz of synthesized audio. Set to 0 (default) to use voice's original sample rate.
--speech-pitch        Allows adjusting the default pitch of the synthesized speech (optional, can be overriden by SSML).
--speech-range        Allows adjusting the default range of the synthesized speech (optional, can be overriden by SSML).
--speech-rate         Allows adjusting the default rate (speed) of the synthesized speech (optional, can be overriden by SSML).
--speech-volume       Allows adjusting the default volume of the synthesized speech (optional, can be overriden by SSML).
--voice-name          A name od the voice used to synthesize the phrase (optional, can be overriden by SSML).
--voice-gender        A gender of the voice - female or male (optional, can be overriden by SSML).
--voice-age           An age of the voice - adult, child, or senile (optional, can be overriden by SSML).
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
