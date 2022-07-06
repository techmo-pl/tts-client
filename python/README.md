# Python implementation of Techmo TTS gRPC client.

## Docker usage

### Build docker image

To prepare a docker image with Python implementation of the TTS Client, open the project's main directory and run following command:

```
docker build -f Dockerfile-python -t tts-client-python:2.2.0 . 
```
The build process will take several minutes.
When the build process is complete, you will receive a message:
```
Successfully tagged tts-client-python:2.2.0
```

### Run TTS Client

To use the TTS Client on a Docker container, go to the `tts-client/python/docker` directory and run `run_tts_client_python.sh` script.

To send a simple request to the TTS service, use:
```
./run_tts_client_python.sh --service-address=IP_ADDRESS:PORT --text="Sample text to be synthesised"
```

To print the list of available options, use:
```
./run_tts_client_python.sh --help
```
Output audio files will be created inside `tts-client/python/docker/wav` directory.
Source text files should be placed inside `tts-client/python/docker/txt` directory, if used.

**NOTE:** Unlike a local TTS Client instance, the `run_tts_client_python.sh` script doesn't allow to set custom paths to the input/output files. Instead it uses predefined directories (`wav` and `txt`). When using options: `--input-text-file (-i)` and `--output-file (-o)`, user should only provide filenames.



## Local instance usage

### Basic Usage

TTS Client includes scripts for automatic environment configuration and launching on systems from the Debian Linux family. For launching TTS Client on other Linux-based OS or Windows, check out the "Manual Usage" section.


#### Before run

To install required dependencies and to prepare the virtual environment, run:
```
./setup.sh
```

#### Run

To run the TTS Client, use the `run.sh` script, e.g.:
```
./run --service-address IP_ADDRESS:PORT --text 'Some text to be synthesized'
```
To print usage description, use:
```
./run --help
```


### Manual Usage

#### Before run

##### Dependencies


Then install the required dependencies inside the virtual environment (this step only needs to be done the first time, for the further usage it is enough to use the existing virtual environment).


- On Linux:

Use Python 3 with the virtual environment and install required packages (supported Python versions are: 3.5, 3.6, 3.7, 3.8, 3.9):

```
python3 -m venv .env
source .env/bin/activate
pip install -r requirements.txt
```
For Python 3.5 instead of `requirements.txt` use the `requirements_python_3.5.txt` file.

- On Windows 10:

Temporarily change the PowerShell's execution policy to allow scripting. Start the PowerShell with `Run as Administrator` and use command:

```
Set-ExecutionPolicy RemoteSigned
```
then confirm your choice.

Use Python 3 with virtual environment and install required packages (supported Python versions are: 3.5, 3.6, 3.7, 3.8, 3.9):

```
python3 -m venv .env
.\.env\Scripts\activate
pip install -r requirements.txt
```
For Python 3.5 instead of `requirements.txt` use the `requirements_python_3.5.txt` file.

To switch back PowerShell's execution policy to the default, use command:

```
Set-ExecutionPolicy Restricted
```

##### Proto sources

To build the sources from `.proto`, run:
```
./make_proto.sh
```


#### Run

To run the TTS Client, activate the virtual environment first:
- On Linux:
```
source .env/bin/activate
```
- On Windows:
```
.\.env\Scripts\activate
```
Then run TTS Client. Sample use:

```
python tts_client.py -s "192.168.1.1:4321" -f 44100 -t "Some text to be synthesized"
```

For each request you have to provide the service address and the input text (directly as argument's value or from text file).


## Usage:
```
Basic usage: tts_client.py --service-address ADDRESS --text INPUT_TEXT
```

Available options:
```

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
  -f SAMPLE_RATE, --sample-rate SAMPLE_RATE
                        A sample rate in Hz of synthesized audio. Set to 0 (default) to use voice's original sample rate.
  --ae AUDIO_ENCODING, --audio-encoding AUDIO_ENCODING
                        An encoding of the output audio, pcm16 (default) or ogg-vorbis.
  --sp SPEECH_PITCH, --speech-pitch SPEECH_PITCH
                        Allows adjusting the default pitch of the synthesized speech (optional, can be overriden by SSML).
  --sr SPEECH_RANGE, --speech-range SPEECH_RANGE
                        Allows adjusting the default range of the synthesized speech (optional, can be overriden by SSML).
  --ss SPEECH_RATE, --speech-rate SPEECH_RATE
                        Allows adjusting the default rate (speed) of the synthesized speech (optional, can be overriden by SSML).
  --sv SPEECH_VOLUME, --speech-volume SPEECH_VOLUME
                        Allows adjusting the default volume of the synthesized speech (optional, can be overriden by SSML).
  --vn VOICE_NAME, --voice-name VOICE_NAME
                        A name od the voice used to synthesize the phrase (optional, can be overriden by SSML).
  --vg VOICE_GENDER, --voice-gender VOICE_GENDER
                        A gender of the voice - female or male (optional, can be overriden by SSML).
  --va VOICE_AGE, --voice-age VOICE_AGE
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

You can use the TTS Client as a module for Python3. Install the package to your environment:
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
