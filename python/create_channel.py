import os
import grpc


def create_channel(address, ssl_directory):
    if not ssl_directory:
        return grpc.insecure_channel(address)

    def read_file(path):
        with open(path, 'rb') as file:
            return file.read()

    return grpc.secure_channel(address, grpc.ssl_channel_credentials(
        read_file(os.path.join(ssl_directory, 'ca.crt')),
        read_file(os.path.join(ssl_directory, 'client.key')),
        read_file(os.path.join(ssl_directory, 'client.crt')),
    ))