import tribune_tts_pb2
import tribune_tts_pb2_grpc
import grpc
import os
from audio_saver import AudioSaver


def call_synthesize(args, text):
    audio_encoding = get_audio_encoding(args)
    out_path = create_out_path(args, audio_encoding)

    channel = grpc.insecure_channel(args.service)
    stub = tribune_tts_pb2_grpc.TTSStub(channel)

    config = tribune_tts_pb2.SynthesizeConfig(
        language=args.language,
        audio_config=tribune_tts_pb2.AudioConfig(
            audio_encoding=audio_encoding,
            sample_rate_hertz=int(args.sample_rate),
            pitch=args.speech_pitch,
            range=args.speech_range,
            rate=args.speech_rate,
            volume=args.speech_volume),
        voice=create_voice(args))
    request = tribune_tts_pb2.SynthesizeRequest(text=text, config=config)

    timeout=None
    if args.grpc_timeout > 0:
        timeout = args.grpc_timeout / 1000 # milliseconds to seconds
    metadata = []
    if args.session_id:
        metadata = [('session_id', args.session_id)]

    asv = AudioSaver()
    asv.setEncoding(audio_encoding)

    try:
        for response in stub.SynthesizeStreaming(request, timeout=timeout, metadata=metadata):
            if response.HasField('error'):
                print("Error [" + str(response.error.code) + "]: " + response.error.description)
                break
            else:
                if asv._framerate:
                    if asv._framerate != response.audio.sample_rate_hertz:
                        raise RuntimeError("Sample rate does not match previously received.")
                else:
                    asv.setFrameRate(response.audio.sample_rate_hertz)
                asv.append(response.audio.content)
        asv.save(out_path)
    except grpc.RpcError as e:
        print("[Server-side error] Received following RPC error from the TTS service:", str(e))
    asv.clear()

def get_audio_encoding(args):
    if args.audio_encoding == "pcm16":
        return tribune_tts_pb2.AudioEncoding.PCM16
    elif args.audio_encoding == "ogg-vorbis":
        return tribune_tts_pb2.AudioEncoding.OGG_VORBIS
    else:
        raise RuntimeError("Unsupported audio-encoding: " + args.audio_encoding)

def create_out_path(args, audio_encoding):
    out_path = args.out_path
    if out_path == "":
        if audio_encoding == tribune_tts_pb2.AudioEncoding.PCM16:
            out_path = "TechmoTTS.wav"
        else:
            out_path = "TechmoTTS.ogg"
    return os.path.join(out_path)

def create_voice(args):
    if args.voice_name != "" or args.voice_gender != "" or args.voice_age != "":
        gender = tribune_tts_pb2.Gender.GENDER_UNSPECIFIED
        if args.voice_gender == "female":
            gender = tribune_tts_pb2.Gender.FEMALE
        elif args.voice_gender == "male":
            gender = tribune_tts_pb2.Gender.MALE
        elif args.voice_gender != "":
            raise RuntimeError("Unsupported voice-gender: " + args.voice_gender)

        age = tribune_tts_pb2.Age.AGE_UNSPECIFIED
        if args.voice_age == "adult":
            age = tribune_tts_pb2.Age.ADULT
        elif args.voice_age == "child":
            age = tribune_tts_pb2.Age.CHILD
        elif args.voice_age == "senile":
            age = tribune_tts_pb2.Age.SENILE
        elif args.voice_age != "":
            raise RuntimeError("Unsupported voice-age: " + args.voice_age)

        return tribune_tts_pb2.Voice(
            name=args.voice_name,
            gender=gender,
            age=age)
    else:
        return None
