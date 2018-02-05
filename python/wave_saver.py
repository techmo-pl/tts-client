import wave
import struct
import sys

class WaveSaver:
    """Wave Saver for TTS"""
    buffer = bytearray()
    _framerate = None
    _nchannels = 1
    _sampwidth = 2

    def __init__(self, sampling_frequency = None):
        self._framerate = sampling_frequency
      
    def setFrameRate(self, sampling_frequency):
        self._framerate = sampling_frequency

    def append(self, audiodata):
        self.buffer += audiodata

    def clear(self):
        self.buffer.clear()

    def save(self, filename):
        if not self._framerate:
            raise RuntimeError("Sample rate has not been set")
        with wave.open(filename, 'w') as w:
            params = (self._nchannels, self._sampwidth, self._framerate, len(self.buffer), 'NONE', 'not compressed')
            w.setparams(params)
            w.writeframes(self.buffer)
    
    def load(self, filename):
        with wave.open(filename, 'r') as wr:
            self.buffer = wr.readframes(wr.getnframes())
            
    def isEqualTo(self, ws):
        return self.buffer == ws.buffer

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
# def ws_main():
#     ws = WaveSaver()
#     audiodata = mock_bytearray()
#     ws.append(audiodata)
#     ws.save('output_wav.wav')
#     ws.print()
#
# ws_main()

