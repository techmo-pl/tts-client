#!/bin/bash

# This script generates Markdown documentation from .proto file
# using https://github.com/pseudomuto/protoc-gen-doc
# and puts it in docs for GitHub Pages to read it from there.
#
# Uses a modified template to put services before messages in documentation.
#
# Requirements: docker.io installed and user added to docker group
#
# Run: ./gen_proto_doc.sh

# Pull a docker image.
docker pull pseudomuto/protoc-gen-doc

# Run the docker image.
docker run --rm \
  -v $(pwd):/out \
  -v $(pwd)/../proto:/protos \
  -v $(pwd):/templates \
  pseudomuto/protoc-gen-doc \
  --doc_opt=/templates/markdownServiceFirst.tmpl,index.md
