# API Documentation
<a name="top"/>

### Table of Contents

- [techmo_tts.proto](#techmo_tts.proto)
    - [TTS](#techmo.tts.grpc_api.TTS)
    - [AudioConfig](#techmo.tts.grpc_api.AudioConfig)
    - [AudioData](#techmo.tts.grpc_api.AudioData)
    - [DeleteLexiconRequest](#techmo.tts.grpc_api.DeleteLexiconRequest)
    - [DeleteLexiconResponse](#techmo.tts.grpc_api.DeleteLexiconResponse)
    - [GetLexiconRequest](#techmo.tts.grpc_api.GetLexiconRequest)
    - [GetLexiconResponse](#techmo.tts.grpc_api.GetLexiconResponse)
    - [ListLexiconsRequest](#techmo.tts.grpc_api.ListLexiconsRequest)
    - [ListLexiconsResponse](#techmo.tts.grpc_api.ListLexiconsResponse)
    - [ListVoicesRequest](#techmo.tts.grpc_api.ListVoicesRequest)
    - [ListVoicesResponse](#techmo.tts.grpc_api.ListVoicesResponse)
    - [PutLexiconRequest](#techmo.tts.grpc_api.PutLexiconRequest)
    - [PutLexiconResponse](#techmo.tts.grpc_api.PutLexiconResponse)
    - [SynthesizeConfig](#techmo.tts.grpc_api.SynthesizeConfig)
    - [SynthesizeRequest](#techmo.tts.grpc_api.SynthesizeRequest)
    - [SynthesizeResponse](#techmo.tts.grpc_api.SynthesizeResponse)
    - [Voice](#techmo.tts.grpc_api.Voice)
    - [VoiceInfo](#techmo.tts.grpc_api.VoiceInfo)
    - [Age](#techmo.tts.grpc_api.Age)
    - [AudioEncoding](#techmo.tts.grpc_api.AudioEncoding)
    - [Gender](#techmo.tts.grpc_api.Gender)
  
- [Scalar Value Types](#scalar-value-types)



<a name="techmo_tts.proto"/>
<p align="right"><a href="#top">Top</a></p>

## techmo_tts.proto
Techmo TTS API
version: 2.1.0
authors: Dawid Skurzok, Paweł Jaciów, Michał Radziszewski
date:    2021-04-21


<a name="techmo.tts.grpc_api.TTS"/>

### TTS
Service that implements Techmo Text-To-Speech (TTS) API.

| Method Name | Request Type | Response Type | Description |
| ----------- | ------------ | ------------- | ------------|
| ListVoices | [ListVoicesRequest](#techmo.tts.grpc_api.ListVoicesRequest) | [ListVoicesResponse](#techmo.tts.grpc_api.ListVoicesRequest) | Lists all available voices which can be used to synthesize speech. |
| SynthesizeStreaming | [SynthesizeRequest](#techmo.tts.grpc_api.SynthesizeRequest) | [SynthesizeResponse](#techmo.tts.grpc_api.SynthesizeRequest) | Synthesizes the speech (audio signal) based on the requested phrase and the optional configuration. Returns audio signal with synthesized speech (streaming version, one or more response packets). |
| Synthesize | [SynthesizeRequest](#techmo.tts.grpc_api.SynthesizeRequest) | [SynthesizeResponse](#techmo.tts.grpc_api.SynthesizeRequest) | Synthesizes the speech (audio signal) based on the requested phrase and the optional configuration. Returns audio signal with synthesized speech (non-streaming version, always one repsonse packet). |
| PutLexicon | [PutLexiconRequest](#techmo.tts.grpc_api.PutLexiconRequest) | [PutLexiconResponse](#techmo.tts.grpc_api.PutLexiconRequest) | Adds a new lexicon with the requested name or overwrites the existing one if there is already a lexicon with such name. |
| DeleteLexicon | [DeleteLexiconRequest](#techmo.tts.grpc_api.DeleteLexiconRequest) | [DeleteLexiconResponse](#techmo.tts.grpc_api.DeleteLexiconRequest) | Removes the lexicon with the requested name. |
| GetLexicon | [GetLexiconRequest](#techmo.tts.grpc_api.GetLexiconRequest) | [GetLexiconResponse](#techmo.tts.grpc_api.GetLexiconRequest) | Sends back the content of the lexicon with the requested name. Returns the lexicon content. |
| ListLexicons | [ListLexiconsRequest](#techmo.tts.grpc_api.ListLexiconsRequest) | [ListLexiconsResponse](#techmo.tts.grpc_api.ListLexiconsRequest) | Lists all client-defined lexicons which can be referred by `<lexicon>` tag in synthesize requests. Returns the list of names of lexicons. |

 <!-- end services -->


<a name="techmo.tts.grpc_api.AudioConfig"/>

### AudioConfig
Desfines the parameters of synthesized speech.


| Field | Type | Description |
| ----- | ---- | ----------- |
| audio_encoding | [AudioEncoding](#techmo.tts.grpc_api.AudioEncoding) | Requested format of the output audio stream. |
| sample_rate_hertz | [int32](#int32) | Desired sampling frequency in hertz of synthesized audio. The value 0 means use the default Synthesizer sampling rate. |
| pitch | [float](#float) | The average speech pitch scaling factor. The value 1.0 is a neutral value. |
| range | [float](#float) | The speech range scaling factor. The value 1.0 is a neutral value. |
| rate | [float](#float) | The speech rate (speed) scaling factor. The value 1.0 is a neutral value. |
| volume | [float](#float) | The speech volume scaling factor. The value 1.0 is a neutral value. |






<a name="techmo.tts.grpc_api.AudioData"/>

### AudioData
Audio data corresponding to a portion of the text
that is currently being processed.


| Field | Type | Description |
| ----- | ---- | ----------- |
| sample_rate_hertz | [int32](#int32) | Sampling frequency in hertz. |
| content | [bytes](#bytes) | Audio data bytes encoded by default as Linear PCM (uncompressed 16-bit signed little-endian samples). Using `output_format` in request it can be changed to Ogg/Vorbis encoded stream. |






<a name="techmo.tts.grpc_api.DeleteLexiconRequest"/>

### DeleteLexiconRequest
The top-level message sent by the client to delete the requested pronounciation lexicon.


| Field | Type | Description |
| ----- | ---- | ----------- |
| name | [string](#string) | Name of the lexicon to delete. |






<a name="techmo.tts.grpc_api.DeleteLexiconResponse"/>

### DeleteLexiconResponse
Status of the DeleteLexicon call.

Empty, just verify returned GRPC status.






<a name="techmo.tts.grpc_api.GetLexiconRequest"/>

### GetLexiconRequest
The top-level message sent by the client to get the content the requested pronounciation lexicon.


| Field | Type | Description |
| ----- | ---- | ----------- |
| name | [string](#string) | Name of the lexicon to list its content. |






<a name="techmo.tts.grpc_api.GetLexiconResponse"/>

### GetLexiconResponse
Result of the GetLexicon call.


| Field | Type | Description |
| ----- | ---- | ----------- |
| content | [string](#string) | If successful, contains the content of the lexicon, in SSML/XML format. |






<a name="techmo.tts.grpc_api.ListLexiconsRequest"/>

### ListLexiconsRequest
The top-level message sent by the client to obtain the list of all available lexicons.


| Field | Type | Description |
| ----- | ---- | ----------- |
| language | [string](#string) | ISO 639-1 language code. Optional. When defined, limits the listed lexicons to the lexicons supprting the requested language. |






<a name="techmo.tts.grpc_api.ListLexiconsResponse"/>

### ListLexiconsResponse
Result of the ListLexicons call.


| Field | Type | Description |
| ----- | ---- | ----------- |
| names | [string](#string) | The list of names of all available lexicons. |






<a name="techmo.tts.grpc_api.ListVoicesRequest"/>

### ListVoicesRequest
The top-level message sent by the client to request listing of available voices.


| Field | Type | Description |
| ----- | ---- | ----------- |
| language | [string](#string) | ISO 639-1 language code. Optional. When defined, limits the listed voices to the voices supprting the requested language. |






<a name="techmo.tts.grpc_api.ListVoicesResponse"/>

### ListVoicesResponse
The listing of available voices returned by a `ListVoices` call.


| Field | Type | Description |
| ----- | ---- | ----------- |
| voices | [VoiceInfo](#techmo.tts.grpc_api.VoiceInfo) | The list of all available voices or voices supproting the requested laguage. |






<a name="techmo.tts.grpc_api.PutLexiconRequest"/>

### PutLexiconRequest
The top-level message sent by the client to put the new pronounciation lexicon.


| Field | Type | Description |
| ----- | ---- | ----------- |
| name | [string](#string) | Name of the lexicon, used as `uri` attributes of `<lexicon>` tags in synthesize requests. |
| content | [string](#string) | Content of the lexicon, shall comply to https://www.w3.org/TR/pronunciation-lexicon/. |






<a name="techmo.tts.grpc_api.PutLexiconResponse"/>

### PutLexiconResponse
Status of the PutLexicon call.

Empty, just verify returned GRPC status.






<a name="techmo.tts.grpc_api.SynthesizeConfig"/>

### SynthesizeConfig
Provides information to the synthesizer that specifies how to process the request.


| Field | Type | Description |
| ----- | ---- | ----------- |
| language | [string](#string) | ISO 639-1 code of the language of text to be synthesized (may be overriden by SSML tags in request text). |
| audio_config | [AudioConfig](#techmo.tts.grpc_api.AudioConfig) | Optional. Overrides the default synthesized speech parameters |
| voice | [Voice](#techmo.tts.grpc_api.Voice) | Requested voice to be used to synthesize the text (may be overriden by SSML tags in request text). If there is no voice satisfying all the required criteria, the voice is selected according to name (if defined) first, gender (if defined) second, and age (if defined) third. |






<a name="techmo.tts.grpc_api.SynthesizeRequest"/>

### SynthesizeRequest
The top-level message sent by the client for `Synthesize` and `SynthesizeStreaming` methods.
It contains a text to be synthesized and a configuration.
The phrase to synthesize is put as a string in `text` field. The string has to be in orthographic form.
The string can be either a plain text or SSML (https://w3.org/TR/speech-synthesis11/).
Currently the following SSML tags are supported:
`<speak>` - root xml node, with optional `xml:lang` attribute,
`<prosody>` - supported attributes: `pitch`, `range`, `rate`, and `volume`,
`<break>` - supported attributes: `strength` and `time`,
`<emphasis>` - supported attribute: `level`,
`<say-as>` - supported attribute: `interpret-as` (consult Techmo TTS documentation for the complete list of all available implementations),
`<lang>` - supported attribute: `xml:lang`,
`<voice>` - supported attributes: `name`, `gender`, and `age`.
`SynthesizeConfig`'s fields can be set to specify parameters of synthesis (sampling rate, language, and voice) and a format of the output (PCM16 or Ogg/Vorbis compression).


| Field | Type | Description |
| ----- | ---- | ----------- |
| text | [string](#string) | Text to be synthesized. |
| config | [SynthesizeConfig](#techmo.tts.grpc_api.SynthesizeConfig) | Configuration. |






<a name="techmo.tts.grpc_api.SynthesizeResponse"/>

### SynthesizeResponse
`SynthesizeResponse` is the only message returned to the client by `SynthesizeStreaming` and `Synthesize`.
During `SynthesizeStreaming`, a series of one or more `SynthesizeResponse` messages are streamed back to the client.
During `Synthesize` always one message is generated.


| Field | Type | Description |
| ----- | ---- | ----------- |
| audio | [AudioData](#techmo.tts.grpc_api.AudioData) | Audio data corresponding to a portion of the text that is currently being processed. |






<a name="techmo.tts.grpc_api.Voice"/>

### Voice
Voice definition used to describe requested voice in SynthesizeConfig,
and voice parameters in ListVoices (as a part of VoiceInfo).


| Field | Type | Description |
| ----- | ---- | ----------- |
| name | [string](#string) | The name of the voice. |
| gender | [Gender](#techmo.tts.grpc_api.Gender) | Gender of the voice. |
| age | [Age](#techmo.tts.grpc_api.Age) | Age of the voice. |






<a name="techmo.tts.grpc_api.VoiceInfo"/>

### VoiceInfo
Information about a voice, returned by ListVoices call.
Both the supported_languages and voice are always defined, i.e. non-empy.


| Field | Type | Description |
| ----- | ---- | ----------- |
| supported_languages | [string](#string) | The list of ISO 639-1 codes of laguages supported by the voice. |
| voice | [Voice](#techmo.tts.grpc_api.Voice) | The voice parameters. |





 <!-- end messages -->


<a name="techmo.tts.grpc_api.Age"/>

### Age
Age of the voice.

| Name | Number | Description |
| ---- | ------ | ----------- |
| AGE_UNSPECIFIED | 0 |  |
| ADULT | 1 |  |
| CHILD | 2 |  |
| SENILE | 3 |  |



<a name="techmo.tts.grpc_api.AudioEncoding"/>

### AudioEncoding
The requested format of the response audio data.

| Name | Number | Description |
| ---- | ------ | ----------- |
| PCM16 | 0 | Uncompressed 16-bit signed integer samples, without any header. |
| OGG_VORBIS | 1 | Ogg/Vorbis endoded data stream. |



<a name="techmo.tts.grpc_api.Gender"/>

### Gender
Gender of the voice.

| Name | Number | Description |
| ---- | ------ | ----------- |
| GENDER_UNSPECIFIED | 0 |  |
| FEMALE | 1 |  |
| MALE | 2 |  |


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

