#!/bin/bash
# coding=utf-8

grpc_root="/opt/grpc_v1.24.3"

PROTOC="$grpc_root/build/third_party/protobuf/protoc"
PLUGIN="--plugin=protoc-gen-grpc=$grpc_root/build/grpc_cpp_plugin"

if [ ! -x ${PROTOC} ]; then
    echo "${PROTOC}; no such file."
    exit 1
fi

echo "Generating TTS C++ protobuf/grpc sources..."
path_i="../proto"
path_o="libtts-client"
${PROTOC}   -I${path_i} \
            ${PLUGIN} \
            --cpp_out=${path_o} \
            --grpc_out=${path_o} \
            ${path_i}/techmo_tts.proto
