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
  --help                                Print help message.
  --service-address arg                 IP address and port (address:port) of a
                                        service the client will connect to.
  --out-path arg (=TechmoTTS.wav)       Path to output wave file with 
                                        synthesized audio content.
  --text arg (=Techmo Trybun: Syntezator mowy polskiej.)
                                        Text to be synthesized (in polish).
  --session-id arg                      Session ID to be passed to the service.
                                        If not specified, the service will 
                                        generate a default session ID itself.
  --grpc-timeout arg (=0)               Timeout in milliseconds used to set 
                                        gRPC deadline - how long the client is 
                                        willing to wait for a reply from the 
                                        server. If not specified, the service 
                                        will set the deadline to a very large 
                                        number.
  --sample-rate-hertz arg (=0)          Sample rate in Hz of synthesized audio.
                                        Set to 0 (default) to use voice's 
                                        original sample rate.
```

In input text you can use several special tags which can be interpreted. Tags have to be in from `<tag>something special</tag>` and can occur in any place in text. Currently interpreted tags are:

cardinal    cardinal number     "<cardinal>7</cardinal>"    -> "siedem"
signed      number with sign    "<signed>-15</signed>"      -> "minus piętnaście"
ordinal     ordinal number      "<ordinal>1</ordinal>"      -> "pierwszy"
fraction    fractional number   "<fraction>3/4</fraction>"  -> "trzy czwarte"
postal      postal code         "<postal>30-020</postal>"   -> "trzydzieści zero dwadzieścia"
time        time                "<time>22:00</time>"        -> "dwudziesta druga"
date        date                "<date>12/05/2001</date>"   -> "dwunasty maja dwa tysiące jeden"

Note: when interpreting tags only nominal case is supported at the moment.
