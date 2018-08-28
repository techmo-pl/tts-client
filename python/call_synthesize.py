import tribune_tts_pb2
import tribune_tts_pb2_grpc
import grpc
import os
from wave_saver import WaveSaver
#from argparse import ArgumentParser


def call_synthesize(args):
    # Output file determination
    wavefilename = os.path.join(args.out_path)

    # Establish GRPC channel
    channel = grpc.insecure_channel(args.service)
    stub = tribune_tts_pb2_grpc.TTSStub(channel)

    # Synthesis request
    config = tribune_tts_pb2.SynthesizeConfig(sample_rate_hertz=int(args.sample_rate))
    request = tribune_tts_pb2.SynthesizeRequest(text=args.text, config=config)
    ws = WaveSaver()
    try:
        for response in stub.Synthesize(request):
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
                if response.audio.end_of_stream:
                    ws.save(wavefilename)
    except grpc.RpcError as e:
        print("[Server-side error] Received following RPC error from the TTS service:", str(e))
    ws.clear()
