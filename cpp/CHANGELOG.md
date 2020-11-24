# Tribune TTS gRPC C++ client Changelog

## [2.0.0] - 2020-11-04
### Added
- The `--audio-encoding` option, with `pcm16` (default) and `ogg-vorbis`.
- The `--speech-pitch`, `--speech-range`, `--speech-rate`, and `--speech-volume`, options for controlling speech parameters
- The `--voice-name`, `--voice-gender`, and `--voice-age` options for controlling voice
- The `--language` option for specifying request text language
- The `--list-voices` option to list all available voices on the service
- The `--no-streaming` option to call the non-streaming version of `Synthesize`
### Changed
- Updated the proto to version 2.0.0.

## [1.3.0] - 2020-03-30
### Changed
- Switch GRPC version to `1.24.3`.

## [1.2.0] - 2018-12-12
### Added
- Support for setting gRPC deadline (how long the client is willing to wait for a reply from the server).

## [1.1.0] - 2018-07-02
### Changed
- `Synthesize` method to return a structure with received both sample rate and audio bytes.

## [1.0.1] - 2018-01-31
### Added
- Separate file for wave utilities.
- gRPC status code names printing on error.

### Changed
- Updates in Readmes.

### Fixed
- sh to bash in tools scripts.

## [1.0.0] - 2018-01-26
### Added
- Initial implementation.
