from io import BytesIO
import numpy as np
import sounddevice as sd


class AudioPlayer:
    def __init__(self, sample_rate_hertz=None, encoding='pcm16'):
        self.sample_rate_hertz = sample_rate_hertz
        self.stream = None

        if encoding == 'pcm16':
            self.encoding = np.int16
        elif encoding == 'ogg-vorbis':
            raise RuntimeError("OGG-Vorbis audio-encoding is not implemented.")
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
        self.stream.write(np.fromstring(audio, dtype=np.int16))

    def stop(self):
        if self.stream is not None:
            self.stream.close()
