# tribune-client
Tribune TTS gRPC client

Contents:  
- `proto`   Protocol Buffers API definition.  
- `cpp`     Tribune TTS gRPC client C++ implementation.  
- `tools`   Utilities. Scripts for dependencies installation.  

Required steps:
- Install Boost:
```
./tools/install_boost.sh
```
- Install gRPC:
```
./tools/install_grpc.sh
```

To regenerate sources from `.proto`, run:
```
./proto/make_proto.sh
```
This might be required when using other gRPC or Protocol Buffers version.


# Techmo TTS Service API

Techmo TTS Service API is defined in `proto/TTS.proto` file.

Service's `Synthesize` method accepts `SynthesizeRequest` object which contains whole phrase to be synthesized.
You have to put the phrase as a string in `text` field of `SynthesizeRequest`. The string has to be in orthographic form. In that string you can use several special tags which can be interpreted. Tags have to be in from `<tag>something special</tag>` and can occur in any place in text. Currently interpreted tags are:

cardinal    cardinal number     "<cardinal>7</cardinal>"    -> "siedem"
signed      number with sign    "<signed>-15</signed>"      -> "minus piętnaście"
ordinal     ordinal number      "<ordinal>1</ordinal>"      -> "pierwszy"
fraction    fractional number   "<fraction>3/4</fraction>"  -> "trzy czwarte"
postal      postal code         "<postal>30-020</postal>"   -> "trzydzieści zero dwadzieścia"
time        time                "<time>22:00</time>"        -> "dwudziesta druga"
date        date                "<date>12/05/2001</date>"   -> "dwunasty maja dwa tysiące jeden"

Note: when interpreting tags only nominal case is supported at the moment.

You can set `SynthesizeConfig`'s fields to specify parameters of synthesis. Currently supported option is only `sample_rate_hertz`, which is desired sampling frequency (in hertz) of synthesized audio.

`SynthesizeRequest` can be sent to the service via gRPC insecure channel (that does not require authentication).

`Synthesize` returns synthesized audio in `SynthesizeResponse` as a stream. When reading from the stream you have to check if `SynthesizeResponse` contains `error` field. If it does you can print its `code` and `description`. No `error` field in `SynthesizeResponse` means everything worked fine and its `audio` contains byte `content` that can be appended to received audio samples with `sample_rate_hertz` sampling frequency in hertz. When receiving `SynthesizeResponse` with `audio` you have to check if its `end_of_stream` flag is set to true. When it is set to true it means service has fnished synthesis and you can save your wave file with received synthesized audio content.

We provide sample TTS Client written in C++ in `cpp`. The example accepts text to be synthesized as a command line string. By default it saves "TechmoTTS.wav" file with received synthesized audio content. To use it, you have to specify provided by us service IP address and port using `--service-address` option with string in form "address:port".
