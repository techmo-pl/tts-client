import tribune_tts_pb2
import tribune_tts_pb2_grpc
import grpc
import os
from wave_saver import WaveSaver


def call_synthesize(args, text):
    # determine the output format
    out_format = tribune_tts_pb2.OutputFormat.PCM16
    if args.out_format == "ogg-vorbis":
        out_format = tribune_tts_pb2.OutputFormat.OGG_VORBIS
    elif args.out_format != "pcm16":
        raise RuntimeError("Unsupported output-format: " + args.out_format)

    # Output file determination
    out_path = args.out_path
    if out_path == "":
        if out_format == tribune_tts_pb2.OutputFormat.PCM16:
            out_path = "TechmoTTS.wav"
        else:
            out_path = "TechmoTTS.ogg"
    wavefilename = os.path.join(out_path)

    # Establish GRPC channel
    channel = grpc.insecure_channel(args.service)
    stub = tribune_tts_pb2_grpc.TTSStub(channel)

    # Synthesis request
    config = tribune_tts_pb2.SynthesizeConfig(sample_rate_hertz=int(args.sample_rate), output_format=out_format)
    request = tribune_tts_pb2.SynthesizeRequest(text=text, config=config)
    ws = WaveSaver()

    timeout=None
    if args.grpc_timeout > 0:
        timeout = args.grpc_timeout / 1000 # milliseconds to seconds
    metadata = []
    if args.session_id:
        metadata = [('session_id', args.session_id)]

    try:
        for response in stub.SynthesizeStreaming(request, timeout=timeout, metadata=metadata):
            if response.HasField('error'):
                print("Error [" + str(response.error.code) + "]: " + response.error.description)
                break
            else:
                if ws._framerate:
                    if ws._framerate != response.audio.sample_rate_hertz:
                        raise RuntimeError("Sample rate does not match previously received.")
                else:
                    ws.setFrameRate(response.audio.sample_rate_hertz)
                ws.append(response.audio.content)

        if out_format == tribune_tts_pb2.OutputFormat.PCM16:
            ws.save(wavefilename)
        else:
            ws.saveOggVorbis(wavefilename)
    except grpc.RpcError as e:
        print("[Server-side error] Received following RPC error from the TTS service:", str(e))
    ws.clear()
