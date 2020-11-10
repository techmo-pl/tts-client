import numpy as np
import sounddevice as sd


class AudioPlayer:
    def __init__(self, sample_rate_hertz:int):
        self.sample_rate_hertz = sample_rate_hertz
        self.stream = None

    def start(self):
        self.stop()
        self.stream = sd.OutputStream(
            samplerate=self.sample_rate_hertz,
            blocksize=1024,
            channels=1,
            dtype=np.int16
        )
        self.stream.start()

    def append(self, audio):
        self.stream.write(np.fromstring(audio, dtype=np.int16))

    def stop(self):
        if self.stream is not None:
            self.stream.close()
