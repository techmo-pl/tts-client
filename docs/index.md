# API Documentation
<a name="top"/>

### Table of Contents

- [tribune_tts.proto](#tribune_tts.proto)
    - [TTS](#techmo.tribune.TTS)
    - [AudioData](#techmo.tribune.AudioData)
    - [Error](#techmo.tribune.Error)
    - [SynthesizeConfig](#techmo.tribune.SynthesizeConfig)
    - [SynthesizeRequest](#techmo.tribune.SynthesizeRequest)
    - [SynthesizeResponse](#techmo.tribune.SynthesizeResponse)
    - [ErrorCode](#techmo.tribune.ErrorCode)
  
- [Scalar Value Types](#scalar-value-types)



<a name="tribune_tts.proto"/>
<p align="right"><a href="#top">Top</a></p>

## tribune_tts.proto
Techmo Tribune TTS API
version: 1.1.0
authors: Dawid Skurzok, Paweł Jaciów
date:    2018-01-25


<a name="techmo.tribune.TTS"/>

### TTS
Service that implements Techmo Text-To-Speech (TTS) API.

Service's `Synthesize` method accepts `SynthesizeRequest` object which contains whole phrase to be synthesized.
You have to put the phrase as a string in `text` field of `SynthesizeRequest`. The string has to be in orthographic form. In that string you can use several special tags which can be interpreted. Tags have to be in from `<tag>something special</tag>` and can occur in any place in text. Currently interpreted tags are:

| Tag | Description | Example (input) | Example (output) |
| --- | ----------- | --------------- | ---------------- |
| **cardinal** | *cardinal number* | `<cardinal>7</cardinal>` | *siedem* |
| **signed** | *number with sign* | `<signed>-15</signed>` | *minus piętnaście* |
| **ordinal** | *ordinal number* | `<ordinal>1</ordinal>` | *pierwszy* |
| **fraction** | *fractional number* | `<fraction>3/4</fraction>` | *trzy czwarte* |
| **postal** | *postal code* | `<postal>30-020</postal>` | *trzydzieści zero dwadzieścia* |
| **time** | *time* | `<time>22:00</time>` | *dwudziesta druga* |
| **date** | *date* | `<date>12/05/2001</date>` | *dwunasty maja dwa tysiące jeden* |

Note: when interpreting tags only nominal case is supported at the moment.

You can set `SynthesizeConfig`'s fields to specify parameters of synthesis. Currently supported option is only `sample_rate_hertz`, which is desired sampling frequency (in hertz) of synthesized audio.

`SynthesizeRequest` can be sent to the service via gRPC insecure channel (that does not require authentication).

`Synthesize` returns synthesized audio in `SynthesizeResponse` as a stream. When reading from the stream you have to check if `SynthesizeResponse` contains `error` field. If it does you can print its `code` and `description`. No `error` field in `SynthesizeResponse` means everything worked fine and its `audio` contains byte `content` that can be appended to received audio samples with `sample_rate_hertz` sampling frequency in hertz. When receiving `SynthesizeResponse` with `audio` you have to check if its `end_of_stream` flag is set to true. When it is set to true it means service has fnished synthesis and you can save your wave file with received synthesized audio content.

| Method Name | Request Type | Response Type | Description |
| ----------- | ------------ | ------------- | ------------|
| Synthesize | [SynthesizeRequest](#techmo.tribune.SynthesizeRequest) | [SynthesizeResponse](#techmo.tribune.SynthesizeRequest) | Returns audio signal with synthesized speech, given text and optional configuration. |

 <!-- end services -->


<a name="techmo.tribune.AudioData"/>

### AudioData
Audio data corresponding to a portion of the text
that is currently being processed.


| Field | Type | Description |
| ----- | ---- | ----------- |
| sample_rate_hertz | [int32](#int32) | Sampling frequency in hertz. |
| content | [bytes](#bytes) | Audio data bytes encoded by default as Linear PCM (uncompressed 16-bit signed little-endian samples). |
| end_of_stream | [bool](#bool) | Last message flag. If set to true, no more data will be sent. |






<a name="techmo.tribune.Error"/>

### Error
Received error details.


| Field | Type | Description |
| ----- | ---- | ----------- |
| code | [ErrorCode](#techmo.tribune.ErrorCode) | Error code. |
| description | [string](#string) | Error description. |






<a name="techmo.tribune.SynthesizeConfig"/>

### SynthesizeConfig
Provides information to the synthesizer that specifies how to process the request.


| Field | Type | Description |
| ----- | ---- | ----------- |
| sample_rate_hertz | [int32](#int32) | Desired sampling frequency in hertz of synthesized audio. |






<a name="techmo.tribune.SynthesizeRequest"/>

### SynthesizeRequest
`SynthesizeRequest` is the top-level message sent by the client for
the `Synthesize` method. It contains a text to be synthesized and a configuration.


| Field | Type | Description |
| ----- | ---- | ----------- |
| text | [string](#string) | Text to be synthesized. |
| config | [SynthesizeConfig](#techmo.tribune.SynthesizeConfig) | Configuration. |






<a name="techmo.tribune.SynthesizeResponse"/>

### SynthesizeResponse
`SynthesizeResponse` is the only message returned to the client by
`Synthesize`. A series of one or more `SynthesizeResponse`
messages are streamed back to the client.


| Field | Type | Description |
| ----- | ---- | ----------- |
| audio | [AudioData](#techmo.tribune.AudioData) | Audio data corresponding to a portion of the text that is currently being processed. |
| error | [Error](#techmo.tribune.Error) | If set, specifies the error for the operation. |





 <!-- end messages -->


<a name="techmo.tribune.ErrorCode"/>

### ErrorCode
Indicates the type of the error for the operation.

| Name | Number | Description |
| ---- | ------ | ----------- |
| UNKNOWN | 0 | Unknown error. |
| LICENCE | 1 | Licence related error. |
| TEXT_NORMALIZATION | 2 | Error during text normalization. |
| TRANSCRIPTION | 3 | Error during orthographic to phonetic transcription. |
| SYNTHESIS | 4 | Error during speech synthesis. |


 <!-- end enums -->

 <!-- end HasExtensions -->



<p align="right"><a href="#top">Top</a></p>
## Scalar Value Types

| .proto Type | Notes | C++ Type | Java Type | Python Type |
| ----------- | ----- | -------- | --------- | ----------- |
| <a name="double" /> double |  | double | double | float |
| <a name="float" /> float |  | float | float | float |
| <a name="int32" /> int32 | Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint32 instead. | int32 | int | int |
| <a name="int64" /> int64 | Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint64 instead. | int64 | long | int/long |
| <a name="uint32" /> uint32 | Uses variable-length encoding. | uint32 | int | int/long |
| <a name="uint64" /> uint64 | Uses variable-length encoding. | uint64 | long | int/long |
| <a name="sint32" /> sint32 | Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int32s. | int32 | int | int |
| <a name="sint64" /> sint64 | Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int64s. | int64 | long | int/long |
| <a name="fixed32" /> fixed32 | Always four bytes. More efficient than uint32 if values are often greater than 2^28. | uint32 | int | int |
| <a name="fixed64" /> fixed64 | Always eight bytes. More efficient than uint64 if values are often greater than 2^56. | uint64 | long | int/long |
| <a name="sfixed32" /> sfixed32 | Always four bytes. | int32 | int | int |
| <a name="sfixed64" /> sfixed64 | Always eight bytes. | int64 | long | int/long |
| <a name="bool" /> bool |  | bool | boolean | boolean |
| <a name="string" /> string | A string must always contain UTF-8 encoded or 7-bit ASCII text. | string | String | str/unicode |
| <a name="bytes" /> bytes | May contain any arbitrary sequence of bytes. | string | ByteString | str |

