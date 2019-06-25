import tribune_tts_pb2
import tribune_tts_pb2_grpc
import grpc
import os
from wave_saver import WaveSaver

class SimpleSaver:
    """Raw saver for TTS"""
    buffer = None
    _framerate = None

    def __init__(self, sampling_frequency = None):
        self.buffer = bytearray()
        _framerate = None

    def setFrameRate(self, sampling_frequency):
        self._framerate = sampling_frequency

    def append(self, audiodata):
        self.buffer += audiodata

    def clear(self):
        self.buffer.clear()

    def save(self, filename):
        with open(filename, 'w+b') as f:
            f.write(self.buffer)

class SaverFactory:
    @staticmethod
    def get_saver(encoding):
        if encoding == tribune_tts_pb2.AudioEncoding.Value('OGG_OPUS'):
            return SimpleSaver()
        else:
            return WaveSaver()
