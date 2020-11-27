Python implementation of Techmo TTS gRPC client.

To regenerate sources from `.proto`, run:
```
./make_proto.sh
```
This might be required when using other gRPC or Protocol Buffers version.

To run:
 - Use Python 3 with virtual environment and install required packages:
```
virtualenv -p python3 venv
source venv/bin/activate
pip install -r requirements.txt
```

Run:
```
python tts_client.py -s "192.168.1.1:4321" -f 44100 -t "Polski tekst do syntezy."
```

Usage:
```
usage: tts_client.py [-h] -s SERVICE [--session-id SESSION_ID]
                         [--grpc-timeout GRPC_TIMEOUT] [--list-voices]
                         [-r RESPONSE] [-t TEXT] [-i INPUTFILE] [-o OUT_PATH]
                         [-f SAMPLE_RATE] [-ae AUDIO_ENCODING]
                         [-sp SPEECH_PITCH] [-sr SPEECH_RANGE]
                         [-ss SPEECH_RATE] [-sv SPEECH_VOLUME]
                         [-vn VOICE_NAME] [-vg VOICE_GENDER] [-va VOICE_AGE]
                         [-l LANGUAGE] [--play]

optional arguments:
  -h, --help            Shows this help message and exits.
  -s SERVICE, --service-address SERVICE
                        An IP address and port (address:port) of a service the client connects to.
  --session-id SESSION_ID
                        A session ID to be passed to the service. If not specified, the service generates a default session ID.
  --grpc-timeout GRPC_TIMEOUT
                        A timeout in milliseconds used to set gRPC deadline - how long the client is willing to wait for a reply from the server (optional).
  --list-voices         Lists all available voices.
  -r RESPONSE, --response RESPONSE
                        streaming or single, calls the streaming (default) or non-streaming version of Synthesize.
  -t TEXT, --text TEXT  Text to be synthesized.
  -i INPUTFILE, --input_text_file INPUTFILE
                        A file with text to be synthesized.
  -o OUT_PATH, --out-path OUT_PATH
                        A path to the output wave file with synthesized audio content.
  -f SAMPLE_RATE, --sample_rate SAMPLE_RATE
                        A sample rate in Hz of synthesized audio. Set to 0 (default) to use voice's original sample rate.
  -ae AUDIO_ENCODING, --audio-encoding AUDIO_ENCODING
                        An encoding of the output audio, pcm16 (default) or ogg-vorbis.
  -sp SPEECH_PITCH, --speech-pitch SPEECH_PITCH
                        Allows adjusting the default pitch of the synthesized speech (optional, can be overriden by SSML).
  -sr SPEECH_RANGE, --speech-range SPEECH_RANGE
                        Allows adjusting the default range of the synthesized speech (optional, can be overriden by SSML).
  -ss SPEECH_RATE, --speech-rate SPEECH_RATE
                        Allows adjusting the default rate (speed) of the synthesized speech (optional, can be overriden by SSML).
  -sv SPEECH_VOLUME, --speech-volume SPEECH_VOLUME
                        Allows adjusting the default volume of the synthesized speech (optional, can be overriden by SSML).
  -vn VOICE_NAME, --voice-name VOICE_NAME
                        A name od the voice used to synthesize the phrase (optional, can be overriden by SSML).
  -vg VOICE_GENDER, --voice-gender VOICE_GENDER
                        A gender of the voice - female or male (optional, can be overriden by SSML).
  -va VOICE_AGE, --voice-age VOICE_AGE
                        An age of the voice - adult, child, or senile (optional, can be overriden by SSML).
  -l LANGUAGE, --language LANGUAGE
                        ISO 639-1 language code of the phrase to synthesize (optional, can be overriden by SSML).
  --play
                        Play synthesized audio. Works only with pcm16 (default) encoding.
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

Module:

You can use the client as a module for Python3. Install the package to your environment:
```
pip install -e ./python/.
```
This package provides modules `call_synthesize` and `call_listvoices` with functions with the same name, which run the client. Here are examples how to use them as a module:
```
from call_synthesize import call_synthesize
call_synthesize(args, text)
```
and
```
from call_listvoices import call_listvoices
call_listvoices(args)
```
The `args` are a parsed command line arguments, and `text` is a request text to synthesize (either a plain text or SSML).
Function parameters are described in usage section above.
