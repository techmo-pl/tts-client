#!/bin/bash
# coding=utf-8

python3 -m venv proto_env
# shellcheck disable=SC1091
source proto_env/bin/activate
pip install grpcio-tools==1.38.1

function cleanup() {
    # shellcheck disable=SC1091
    rm -rf proto_env
}
trap cleanup EXIT


echo "Generating TTS Python protobuf/grpc sources."
path_i="../proto"
path_o="."
python3 -m grpc_tools.protoc \
	        -I${path_i} \
            --python_out=${path_o} \
            --grpc_python_out=${path_o} \
            ${path_i}/techmo_tts.proto
