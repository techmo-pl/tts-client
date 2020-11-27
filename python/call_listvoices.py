import techmo_tts_pb2
import techmo_tts_pb2_grpc
import grpc
import os

def call_listvoices(args):
    channel = grpc.insecure_channel(args.service)
    stub = techmo_tts_pb2_grpc.TTSStub(channel)

    timeout=None
    if args.grpc_timeout > 0:
        timeout = args.grpc_timeout / 1000
    metadata = []
    if args.session_id:
        metadata = [('session_id', args.session_id)]

    request = techmo_tts_pb2.ListVoicesRequest(language=args.language)

    try:
        response = stub.ListVoices(request, timeout=timeout, metadata=metadata)
        print("\nAvailable voices:\n")
        print(response)
    except grpc.RpcError as e:
        print("[Server-side error] Received following RPC error from the TTS service:", str(e))
