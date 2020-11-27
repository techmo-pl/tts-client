import wave
import struct
import sys
import techmo_tts_pb2

class AudioSaver:
    """Wave Saver for TTS"""
    buffer = None
    _framerate = None
    _nchannels = None
    _sampwidth = None
    _encoding = None

    def __init__(self, sampling_frequency = None):
        self.buffer = bytearray()
        self._framerate = sampling_frequency
        self._nchannels = 1
        self._sampwidth = 2

    def setEncoding(self, encoding):
        self._encoding = encoding

    def setFrameRate(self, sampling_frequency):
        self._framerate = sampling_frequency

    def append(self, audiodata):
        self.buffer += audiodata

    def clear(self):
        self.buffer.clear()

    def save(self, filename):
        if self._encoding == techmo_tts_pb2.AudioEncoding.PCM16:
            if not self._framerate:
                raise RuntimeError("Sample rate has not been set")
            with wave.open(filename, 'w') as w:
                params = (self._nchannels, self._sampwidth, self._framerate, len(self.buffer), 'NONE', 'not compressed')
                w.setparams(params)
                w.writeframes(self.buffer)
        else:
            f = open(filename, 'wb')
            f.write(self.buffer)
            f.close()

    def load(self, filename):
        with wave.open(filename, 'r') as wr:
            self.buffer = wr.readframes(wr.getnframes())

    def isEqualTo(self, asv):
        return self.buffer == asv.buffer

    def print(self):
        if len(self.buffer) > 0:
            header = struct.pack('<4sL4s4sLHHLLHH4sL', b'RIFF',
                                 36 + len(self.buffer), b'WAVE', b'fmt ', 16,
                                 0x0001, self._nchannels, self._framerate,
                                 self._nchannels * self._framerate * self._sampwidth,
                                 self._nchannels * self._sampwidth,
                                 self._sampwidth * 8, b'data', len(self.buffer))
            sys.stdout.buffer.write(header + bytes(self.buffer))


# def mock_bytearray():
#     with wave.open("w.wav", 'r') as wr:
#         ar = wr.readframes(wr.getnframes())
#         return ar
#
#
# def asv_main():
#     asv = AudioSaver()
#     audiodata = mock_bytearray()
#     asv.append(audiodata)
#     asv.save('output_wav.wav')
#     asv.print()
#
# asv_main()
