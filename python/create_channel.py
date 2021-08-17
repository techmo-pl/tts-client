import os
import grpc


def create_channel(address, tls_directory):
    if not tls_directory:
        return grpc.insecure_channel(address)

    def read_file(path):
        with open(path, 'rb') as file:
            return file.read()

    return grpc.secure_channel(address, grpc.ssl_channel_credentials(
        read_file(os.path.join(tls_directory, 'ca.crt')),
        read_file(os.path.join(tls_directory, 'client.key')),
        read_file(os.path.join(tls_directory, 'client.crt')),
    ))
