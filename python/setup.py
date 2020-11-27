#!/usr/bin/env python

import codecs
import os.path
from setuptools import setup, find_packages
from VERSION import TTS_CLIENT_VERSION

def read(rel_path):
    here = os.path.abspath(os.path.dirname(__file__))
    with codecs.open(os.path.join(here, rel_path), "r") as fp:
        return fp.read()


with open("README.md") as f:
    README = f.read()

setup(
    name='techmo_tts',
    version=TTS_CLIENT_VERSION,
    py_packages=find_packages(),
    description="Python implementation of Techmo TTS gRPC client",
    long_description=README,
    url="https://github.com/techmo-pl/tts-client",
)
