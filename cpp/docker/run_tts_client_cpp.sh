#!/bin/bash
# coding=utf-8

# This script sends request to dictation service using tts client inside docker container
# Requires "tts-client-cpp:$IMAGE_VERSION" docker image loaded locally

set -euo pipefail
IFS=$'\n\t'

IMAGE_VERSION=2.2.0

SCRIPT=$(realpath "$0")
SCRIPTPATH=$(dirname "${SCRIPT}")
docker_image="tts-client-cpp:${IMAGE_VERSION}"

output_path="/volume/wav/TechmoTTS.wav"

usage() {

echo "
Techmo TTS gRPC client ${IMAGE_VERSION}

  -h, --help            show this help message and exit
  -s=SERVICE, --service-address=SERVICE
                        An IP address and port (address:port) of a service the client connects to.
  --session-id=SESSION_ID
                        A session ID to be passed to the service. If not specified, the service generates a default session ID.
  --grpc-timeout=GRPC_TIMEOUT
                        A timeout in milliseconds used to set gRPC deadline - how long the client is willing to wait for a reply from the
                        server (optional).
  --list-voices         Lists all available voices.
  -r=RESPONSE, --response=RESPONSE
                        streaming or single, calls the streaming (default) or non-streaming version of Synthesize.
  -t=TEXT, --text=TEXT  A text to be synthesized.
  -o=OUTPUT_FILE, --output-file=OUTPUT_FILE
                        A custom name for output wave file with synthesized audio content (default: 'TechmoTTS.wav'). 
                        File will be generated inside 'wav' directory.
  --tls                 Use SSL/TLS authentication. The credential files (client.crt, client.key, ca.crt) should be placed inside 'tls' directory.
  -f=SAMPLE_RATE, --sample-rate=SAMPLE_RATE
                        A sample rate in Hz of synthesized audio. Set to 0 (default) to use voice's original sample rate.
  --ae=AUDIO_ENCODING, --audio-encoding=AUDIO_ENCODING
                        An encoding of the output audio, pcm16 (default) or ogg-vorbis.
  --sp=SPEECH_PITCH, --speech-pitch=SPEECH_PITCH
                        Allows adjusting the default pitch of the synthesized speech (optional, can be overriden by SSML).
  --sr=SPEECH_RANGE, --speech-range=SPEECH_RANGE
                        Allows adjusting the default range of the synthesized speech (optional, can be overriden by SSML).
  --ss=SPEECH_RATE, --speech-rate=SPEECH_RATE
                        Allows adjusting the default rate (speed) of the synthesized speech (optional, can be overriden by SSML).
  --sv=SPEECH_VOLUME, --speech-volume=SPEECH_VOLUME
                        Allows adjusting the default volume of the synthesized speech (optional, can be overriden by SSML).
  --vn=VOICE_NAME, --voice-name=VOICE_NAME
                        A name od the voice used to synthesize the phrase (optional, can be overriden by SSML).
  --vg=VOICE_GENDER, --voice-gender=VOICE_GENDER
                        A gender of the voice - female or male (optional, can be overriden by SSML).
  --va=VOICE_AGE, --voice-age=VOICE_AGE
                        An age of the voice - adult, child, or senile (optional, can be overriden by SSML).
  -l=LANGUAGE, --language=LANGUAGE
                        ISO 639-1 language code of the phrase to synthesize (optional, can be overriden by SSML).
"
}

optspec="f:hl:o:r:s:t:-:"
while getopts "${optspec}" optchar; do
    case "${optchar}" in
        -)
            val=""
            opt=""
            val=${OPTARG#*=}
            if [[ ${val} != "" ]]; then
                opt=${OPTARG%=$val}
            fi
            case "${opt}" in
                help)   
                    usage; exit 0 
                    ;;
                output-file)  
                    output_path="/volume/wav/${val##*/}"
                    ;;
                list-voices)  
                    opts+=( "--list-voices" )
                    ;;
                tls)
                    opts+=( "--tls-dir" "/volume/tls")   
                    ;;
                ae)
                    opts+=( "--audio-encoding" "${val}" )
                    ;;
                sp)
                    opts+=( "--speech-pitch" "${val}" )
                    ;;
                sr)
                    opts+=( "--speech-range" "${val}" )
                    ;;
                ss)
                    opts+=( "--speech-rate" "${val}" )
                    ;;
                sv)
                    opts+=( "--speech-volume" "${val}" )
                    ;;
                va)
                    opts+=( "--voice-age" "${val}" )
                    ;;
                vg)
                    opts+=( "--voice-gender" "${val}" )
                    ;;
                vn)
                    opts+=( "--voice-name" "${val}" )
                    ;;
                *)
                    if [[ "${OPTARG}" != *"="*  ]]; then
                        echo "Can't find value for option: '$OPTARG'. Maybe '=' sign is missing?" >&2
                        exit 1
                    fi
                    opts+=( "--${opt}" "${val}" )
                    ;;
            esac;;
        f)                      
            val=${OPTARG#*=}
            opts+=( "--sample-rate" "${val}" )
            ;;
        h)  
            usage; exit 0 
            ;;
        l)                      
            val=${OPTARG#*=}
            opts+=( "--language" "${val}" )
            ;;
        o)                      
            val=${OPTARG#*=}
            output_path="/volume/wav/${val##*/}"
            ;;
        r)                      
            val=${OPTARG#*=}
            opts+=( "--response" "${val}" )
            ;;
        s)                      
            val=${OPTARG#*=}
            opts+=( "--service-address" "${val}" )
            ;;
        t)                      
            val=${OPTARG#*=}
            opts+=( "--text" "${val}" )
            ;;
        *)
            if [[ "$OPTARG" == \=* ]]; then
                val=${OPTARG#*=}
                opts+=( "-${optchar}" "${val}" )
            else
                if [[ "$OPTERR" = 1 ]] && [[ "${optspec:0:1}" != ":" ]]; then
                    echo "Unknown option: '$OPTARG'. Maybe '=' sign is missing?" >&2
                    exit 1
                fi
            fi
            ;;
    esac
done

opts+=( "--out-path" "${output_path}" )

echo "${opts[@]}"

docker run --rm -it -v "${SCRIPTPATH}:/volume" --network host "${docker_image}" \
./cpp/build/tts_client "${opts[@]}"
