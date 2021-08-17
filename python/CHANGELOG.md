# Techmo TTS gRPC Python client Changelog

## [2.2.0] - 2021-08-10
### Added
- The`--tls-dir` option [bool], for enabling SSL/TLS communication

## [2.1.1] - 2021-07-21
### Changed
 - Switch GRPC version to 1.38.1

## [2.1.0] - 2021-04-21
### Removed
- Duplicate mechanism for error handling (it relies on GRPC status now)

## [2.0.0] - 2020-11-25
### Added
- The `--audio-encoding` option, with `pcm16` (default) and `ogg-vorbis`.
- The `--play` option, with `pcm16` (default).
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

## [1.2.1] - 2019-04-19
### Fixed
- Multithreading buffer access collision.

## [1.2.0] - 2018-12-12
### Added
- Support for setting gRPC deadline (how long the client is willing to wait for a reply from the server).

## [1.1.0] - 2018-08-28
### Added
- A possibility to use the client as a module.

## [1.0.0] - 2018-01-31
### Added
- Initial implementation.
