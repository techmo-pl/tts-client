import techmo_tts_pb2
import techmo_tts_pb2_grpc
import grpc
import os
from audio_player import AudioPlayer
from audio_saver import AudioSaver
from create_channel import create_channel


def call_synthesize(args, text):
    audio_encoding = get_audio_encoding(args)
    out_path = create_out_path(args, audio_encoding)

    channel = create_channel(args.service, args.tls_directory)
    stub = techmo_tts_pb2_grpc.TTSStub(channel)

    config = techmo_tts_pb2.SynthesizeConfig(
        language=args.language,
        audio_config=techmo_tts_pb2.AudioConfig(
            audio_encoding=audio_encoding,
            sample_rate_hertz=int(args.sample_rate),
            pitch=args.speech_pitch,
            range=args.speech_range,
            rate=args.speech_rate,
            volume=args.speech_volume),
        voice=create_voice(args))
    request = techmo_tts_pb2.SynthesizeRequest(text=text, config=config)

    timeout=None
    if args.grpc_timeout > 0:
        timeout = args.grpc_timeout / 1000 # milliseconds to seconds
    metadata = []
    if args.session_id:
        metadata = [('session_id', args.session_id)]

    audioPlayer = None
    if args.play:
        audioPlayer = AudioPlayer(
            sample_rate_hertz=int(args.sample_rate),
            encoding=args.audio_encoding
        )
    audioSaver = AudioSaver()
    audioSaver.setEncoding(audio_encoding)

    try:
        if args.response == "streaming":
            internal_synthesize_streaming(stub, request, timeout, metadata, audioSaver, audioPlayer)
        elif args.response == "single":
            internal_synthesize(stub, request, timeout, metadata, audioSaver, audioPlayer)
        else:
            raise RuntimeError("Unsupported response type: " + args.response)
        audioSaver.save(out_path)
    except grpc.RpcError as e:
        print("[Server-side error] Received following RPC error from the TTS service:", str(e))
    finally:
        if args.play:
            audioPlayer.stop()
    audioSaver.clear()

def get_audio_encoding(args):
    if args.audio_encoding == "pcm16":
        return techmo_tts_pb2.AudioEncoding.PCM16
    elif args.audio_encoding == "ogg-vorbis":
        return techmo_tts_pb2.AudioEncoding.OGG_VORBIS
    else:
        raise RuntimeError("Unsupported audio-encoding: " + args.audio_encoding)

def create_out_path(args, audio_encoding):
    out_path = args.out_path
    if out_path == "":
        if audio_encoding == techmo_tts_pb2.AudioEncoding.PCM16:
            out_path = "TechmoTTS.wav"
        else:
            out_path = "TechmoTTS.ogg"
    return os.path.join(out_path)

def create_voice(args):
    if args.voice_name != "" or args.voice_gender != "" or args.voice_age != "":
        gender = techmo_tts_pb2.Gender.GENDER_UNSPECIFIED
        if args.voice_gender == "female":
            gender = techmo_tts_pb2.Gender.FEMALE
        elif args.voice_gender == "male":
            gender = techmo_tts_pb2.Gender.MALE
        elif args.voice_gender != "":
            raise RuntimeError("Unsupported voice-gender: " + args.voice_gender)

        age = techmo_tts_pb2.Age.AGE_UNSPECIFIED
        if args.voice_age == "adult":
            age = techmo_tts_pb2.Age.ADULT
        elif args.voice_age == "child":
            age = techmo_tts_pb2.Age.CHILD
        elif args.voice_age == "senile":
            age = techmo_tts_pb2.Age.SENILE
        elif args.voice_age != "":
            raise RuntimeError("Unsupported voice-age: " + args.voice_age)

        return techmo_tts_pb2.Voice(
            name=args.voice_name,
            gender=gender,
            age=age)
    else:
        return None

def internal_synthesize_streaming(stub, request, timeout, metadata, audio_saver, audio_player):
    if audio_player is not None:
        audio_player.start()
    for response in stub.SynthesizeStreaming(request, timeout=timeout, metadata=metadata):
        if audio_saver._framerate:
            if audio_saver._framerate != response.audio.sample_rate_hertz:
                raise RuntimeError("Sample rate does not match previously received.")
        else:
            audio_saver.setFrameRate(response.audio.sample_rate_hertz)
        if audio_player is not None:
            audio_player.append(response.audio.content)
        audio_saver.append(response.audio.content)

def internal_synthesize(stub, request, timeout, metadata, audio_saver, audio_player):
    response = stub.Synthesize(request, timeout=timeout, metadata=metadata)
    if audio_player is not None:
        audio_player.start(sample_rate=response.audio.sample_rate_hertz)
        audio_player.append(response.audio.content)
    audio_saver.setFrameRate(response.audio.sample_rate_hertz)
    audio_saver.append(response.audio.content)
