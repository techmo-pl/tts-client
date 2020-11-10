import numpy as np
import sounddevice as sd


class AudioPlayer:
    def __init__(self, sample_rate_hertz=None, encoding='pcm16'):
        self.sample_rate_hertz = sample_rate_hertz
        self.stream = None

        if encoding == 'pcm16':
            self.encoding = np.int16
        elif encoding == 'ogg-vorbis':
            self.encoding = np.float32
        else:
            raise RuntimeError("Unsupported audio-encoding: " + str(encoding))

    def start(self, sample_rate_hertz=None):
        if sample_rate_hertz is not None:
            self.sample_rate_hertz = sample_rate_hertz
        self.stop()
        self.stream = sd.OutputStream(
            samplerate=self.sample_rate_hertz,
            blocksize=1024,
            channels=1,
            dtype=self.encoding
        )
        self.stream.start()

    def append(self, audio):
        self.stream.write(np.fromstring(audio, dtype=self.encoding))

    def stop(self):
        if self.stream is not None:
            self.stream.close()
