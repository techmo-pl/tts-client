# Protocol Documentation
<a name="top"/>

## Table of Contents

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
Service that implements Techmo TTS API

| Method Name | Request Type | Response Type | Description |
| ----------- | ------------ | ------------- | ------------|
| Synthesize | [SynthesizeRequest](#techmo.tribune.SynthesizeRequest) | [SynthesizeResponse](#techmo.tribune.SynthesizeRequest) | Return speech using given text and optional configuration. |

 <!-- end services -->


<a name="techmo.tribune.AudioData"/>

### AudioData
Audio data corresponding to a portion of the text
that is currently being processed.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| sample_rate_hertz | [int32](#int32) |  | Sampling frequency in Hertz. |
| content | [bytes](#bytes) |  | Audio data bytes encoded by default as 16bit PCM. |
| end_of_stream | [bool](#bool) |  | Last message flag. If set to true, no more data will be sent. |






<a name="techmo.tribune.Error"/>

### Error
Received error details.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| code | [ErrorCode](#techmo.tribune.ErrorCode) |  | Error code. |
| description | [string](#string) |  | Error description. |






<a name="techmo.tribune.SynthesizeConfig"/>

### SynthesizeConfig
Provides information to the synthesizer that specifies how to process the request.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| sample_rate_hertz | [int32](#int32) |  | Desired sampling frequency in hertz of synthesized audio. |






<a name="techmo.tribune.SynthesizeRequest"/>

### SynthesizeRequest
`SynthesizeRequest` is the top-level message sent by the client for
the `Synthesize` method. It contains a text to be synthesized and a configuration.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| text | [string](#string) |  | Text to be synthesized. |
| config | [SynthesizeConfig](#techmo.tribune.SynthesizeConfig) |  | Configuration. |






<a name="techmo.tribune.SynthesizeResponse"/>

### SynthesizeResponse
`SynthesizeResponse` is the only message returned to the client by
`Synthesize`. A series of one or more `SynthesizeResponse`
messages are streamed back to the client.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| audio | [AudioData](#techmo.tribune.AudioData) |  | Audio data corresponding to a portion of the text that is currently being processed. |
| error | [Error](#techmo.tribune.Error) |  | If set, specifies the error for the operation. |





 <!-- end messages -->


<a name="techmo.tribune.ErrorCode"/>

### ErrorCode
Indicates the type of the error for the operation.

| Name | Number | Description |
| ---- | ------ | ----------- |
| UNKNOWN | 0 | Unknown error |
| LICENCE | 1 | Licence related error |
| TEXT_NORMALIZATION | 2 | Error during text normalization |
| TRANSCRIPTION | 3 | Error during orthographic to phonetic transcription |
| SYNTHESIS | 4 | Error during speech synthesis |


 <!-- end enums -->

 <!-- end HasExtensions -->



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

