# TTS Client
This repository contains Techmo TTS gRPC service API and client implementations.

Contents:
- `proto`   Protocol Buffers API definition.  
- `cpp`     Techmo TTS gRPC client C++ implementation.  
- `python`  Techmo TTS gRPC client Python implementation.  
- `tools`   Utilities. Scripts for dependencies installation.  

Language-specific build instructions can be found in their respective directories.

# Techmo TTS Service API

Techmo TTS Service API is defined in `proto/techmo_tts.proto` file.

Service's `SynthesizeStreaming` and `Synthesize` methods accept `SynthesizeRequest` object which contains whole phrase to be synthesized.
The phrase has to be placed as a string in `text` field of `SynthesizeRequest`. The string has to be in orthographic form.
The input text can be either a plain text or SSML (https://w3.org/TR/speech-synthesis11/).
Currently the following SSML tags are supported:
- `<speak>` - root xml node, with optional `xml:lang` attribute,
- `<prosody>` - supported attributes: `pitch`, `range`, `rate`, and `volume`,
- `<break>` - supported attributes: `strength` and `time`,
- `<emphasis>` - supported attribute: `level`,
- `<say-as>` - supported attribute: `interpret-as` (consult Techmo TTS documentation for the complete list of all available implementations),
- `<lang>` - supported attribute: `xml:lang`,
- `<voice>` - supported attributes: `name`, `gender`, and `age`.

The `SynthesizeConfig` can be used to specify parameters of synthesis, like sampling rate, output encoding, language, default voice, etc.

`SynthesizeRequest` can be sent to the service via gRPC insecure channel (that does not require authentication).

`SynthesizeStreaming` returns synthesized audio in `SynthesizeResponse` as a stream and `Synthesize` returns the single response.
If the call has been successful, the response `audio` contains byte `content` that can be appended to received audio samples with `sample_rate_hertz` sampling frequency in hertz.

We provide sample TTS Client written in:
- C++ in `cpp` (accepts text to be synthesized as a command line string),  
- Python in `python` (accepts text to be synthesized as a command line string or as a content of given text file).  
By default it saves `"TechmoTTS.wav"` file with received synthesized audio content. To use it, you have to specify provided by us service IP address and port using `--service-address` option with string in form "address:port".
