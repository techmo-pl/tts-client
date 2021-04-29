#!/bin/bash
# coding=utf-8

# This script sends request to dictation service using tts client inside docker container
# Requires "tts-client-cpp:2.0.0" docker image loaded locally

set -euo pipefail
IFS=$'\n\t'

SCRIPT=$(realpath "$0")
SCRIPTPATH=$(dirname "${SCRIPT}")


docker_image="tts-client-cpp:2.0.0"

service_address="UNSPECIFIED"
session_id="UNSPECIFIED"
grpc_timeout="UNSPECIFIED"
list_voices="UNSPECIFIED"
response="UNSPECIFIED"
text="UNSPECIFIED"
output_file="UNSPECIFIED"
sample_rate="UNSPECIFIED"
audio_encoding="UNSPECIFIED"
speech_pitch="UNSPECIFIED"
speech_range="UNSPECIFIED"
speech_rate="UNSPECIFIED"
speech_volume="UNSPECIFIED"
voice_name="UNSPECIFIED"
voice_gender="UNSPECIFIED"
voice_age="UNSPECIFIED"
language="UNSPECIFIED"

service_address_option=""
session_id_option=""
grpc_timeout_option=""
list_voices_option=""
response_option=""
text_option=""
output_file_option=""
sample_rate_option=""
audio_encoding_option=""
speech_pitch_option=""
speech_range_option=""
speech_rate_option=""
speech_volume_option=""
voice_name_option=""
voice_gender_option=""
voice_age_option=""
language_option=""


usage() {

echo "
Techmo TTS gRPC client 2.0.0

  -h, --help            show this help message and exit
  -s SERVICE, --service-address SERVICE
                        An IP address and port (address:port) of a service the client connects to.
  --session-id SESSION_ID
                        A session ID to be passed to the service. If not specified, the service generates a default session ID.
  --grpc-timeout GRPC_TIMEOUT
                        A timeout in milliseconds used to set gRPC deadline - how long the client is willing to wait for a reply from the
                        server (optional).
  --list-voices         Lists all available voices.
  -r RESPONSE, --response RESPONSE
                        streaming or single, calls the streaming (default) or non-streaming version of Synthesize.
  -t TEXT, --text TEXT  A text to be synthesized.
                        A name of the plaintext file with text to be synthesized. File should be placed inside 'txt' directory.
  -o OUTPUT_FILE, --output-file OUTPUT_FILE
                        A custom name for output wave file with synthesized audio content (default: 'TechmoTTS.wav'). 
                        File will be generated inside 'wav' directory.
  -f SAMPLE_RATE, --sample-rate SAMPLE_RATE
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
  --play                Play synthesized audio. Works only with pcm16 (default) encoding.
"
}

while [[ "$#" -gt 0 ]]; do
    case $1 in
        -h|--help)                   usage; exit 0 ;;
        -s|--service-address)        service_address="$2"; shift ;;
        --session-id)                session_id="$2"; shift ;;
        --grpc-timeout)              grpc_timeout="$2"; shift ;;
        --list-voices)               list_voices="true";;
        -r|--response)               response="$2"; shift ;;
        -t|--text)                   text="$2"; shift ;;                                    
        -o|--output-file)            output_file="$2"; shift ;;
        -f|--sample-rate)            sample_rate="$2"; shift ;;
        -ae|--audio-encoding)        audio_encoding="$2"; shift ;;
        -sp|--speech-pitch)          speech_pitch="$2"; shift ;;
        -sr|--speech-range)          speech_range="$2"; shift ;;
        -ss|--speech-rate)           speech_rate="$2"; shift ;;
        -sv|--speech-volume)         speech_volume="$2"; shift ;;
        -vn|--voice-name)            voice_name="$2"; shift ;;
        -vg|--voice-gender)          voice_gender="$2"; shift ;;
        -va|--voice-age)             voice_age="$2"; shift ;;
        -l|--language)               language="$2"; shift ;;
        *) usage; exit 0 ;;
    esac
    shift
done               


if [[ "${service_address}" = "UNSPECIFIED" ]]; then
    echo "Service addres not specified! Use option '-s | --service-address ADDRESS:PORT' to specify service address"
    exit 0
else
    service_address_option="--service-address ${service_address}"
fi
if [[ "${text}" = "UNSPECIFIED" ]]; then
    echo "No input specified! Use '-t | --text TEXT' to specify text to be synthesized."
else
    text_option="--text"
fi
if [[ "${session_id}" != "UNSPECIFIED" ]]; then
    session_id_option="--session-id ${session_id}"
fi
if [[ "${grpc_timeout}" != "UNSPECIFIED" ]]; then
    grpc_timeout_option="--grpc-timeout ${grpc_timeout}"
fi
if [[ "${list_voices}" != "UNSPECIFIED" ]]; then
    list_voices_option="--list-voices"
fi
if [[ "${response}" != "UNSPECIFIED" ]]; then
    response_option="--response ${response}"
fi
if [[ "${output_file}" != "UNSPECIFIED" ]]; then
    output_file_option="--out-path /volumen/wav/${output_file##*/}"
else
    output_file_option="--out-path /volumen/wav/TechmoTTS.wav"
fi
if [[ "${sample_rate}" != "UNSPECIFIED" ]]; then
    sample_rate_option="--sample-rate-hertz ${sample_rate}"
fi
if [[ "${session_id}" != "UNSPECIFIED" ]]; then
    session_id_option="--session-id ${session_id}"
fi
if [[ "${audio_encoding}" != "UNSPECIFIED" ]]; then
    audio_encoding_option="--audio-encoding ${audio_encoding}"
fi
if [[ "${speech_pitch}" != "UNSPECIFIED" ]]; then
    speech_pitch_option="--speech-pitch ${speech_pitch}"
fi
if [[ "${speech_range}" != "UNSPECIFIED" ]]; then
    speech_range_option="--speech-range ${speech_range}"
fi
if [[ "${speech_rate}" != "UNSPECIFIED" ]]; then
    speech_rate_option="--speech-rate ${speech_rate}"
fi
if [[ "${speech_volume}" != "UNSPECIFIED" ]]; then
    speech_volume_option="--speech-volume ${speech_volume}"
fi
if [[ "${voice_name}" != "UNSPECIFIED" ]]; then
    voice_name_option="--voice-name ${voice_name}"
fi
if [[ "${voice_gender}" != "UNSPECIFIED" ]]; then
    voice_gender_option="--voice-gender ${voice_gender}"
fi
if [[ "${voice_age}" != "UNSPECIFIED" ]]; then
    voice_age_option="--voice-age ${voice_age}"
fi
if [[ "${language}" != "UNSPECIFIED" ]]; then
    language_option="--language ${language}"
fi

IFS=$'\x20'

docker run --rm -it -v "${SCRIPTPATH}:/volumen" --network host "${docker_image}" \
./cpp/build/tts_client \
${service_address_option} \
${text_option} "${text}" \
${session_id_option} \
${grpc_timeout_option} \
${list_voices_option} \
${response_option} \
${output_file_option} \
${sample_rate_option} \
${audio_encoding_option} \
${speech_pitch_option} \
${speech_range_option} \
${speech_rate_option} \
${speech_volume_option} \
${voice_name_option} \
${voice_gender_option} \
${voice_age_option} \
${language_option} 
