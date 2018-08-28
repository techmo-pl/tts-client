Python implementation of Tribune TTS gRPC client.

To regenerate sources from `.proto`, run:
```
./make_proto.sh
```
This might be required when using other gRPC or Protocol Buffers version.

To run:
 - Use Python 3 with virtual environment and install required packages:
```
virtualenv -p python3 venv
source venv/bin/activate
pip install -r requirements.txt
```

Run:
```
python tribune_client.py -s "192.168.1.1:4321" -f 44100 -t "Polski tekst do syntezy."
```

Usage:
```
usage: tribune_client.py [-h] -s SERVICE [-t TEXT] [-i INPUTFILE]
                         [-o OUT_PATH] [-f SAMPLE_RATE]

optional arguments:
  -h, --help            show this help message and exit
  -s SERVICE, --service-address SERVICE
                        IP address and port (address:port) of a service the
                        client will connect to.
  -t TEXT, --text TEXT  Text to be synthesized (in polish).
  -i INPUTFILE, --input_text_file INPUTFILE
                        A file with text to be synthesized (in polish).
  -o OUT_PATH, --out-path OUT_PATH
                        Path to output wave file with synthesized audio
                        content.
  -f SAMPLE_RATE, --sample_rate SAMPLE_RATE
                        Sample rate in Hz of synthesized audio.
```

In input text you can use several special tags which can be interpreted. Tags have to be in from `<tag>something special</tag>` and can occur in any place in text. Currently interpreted tags are:

cardinal    cardinal number     "<cardinal>7</cardinal>"    -> "siedem"
signed      number with sign    "<signed>-15</signed>"      -> "minus piętnaście"
ordinal     ordinal number      "<ordinal>1</ordinal>"      -> "pierwszy"
fraction    fractional number   "<fraction>3/4</fraction>"  -> "trzy czwarte"
postal      postal code         "<postal>30-020</postal>"   -> "trzydzieści zero dwadzieścia"
time        time                "<time>22:00</time>"        -> "dwudziesta druga"
date        date                "<date>12/05/2001</date>"   -> "dwunasty maja dwa tysiące jeden"

Note: when interpreting tags only nominal case is supported at the moment.

Module:

You can use the client as a module for Python3. Install the package to your environment:
```
pip install -e ./python/.
```
This package provides a module `call_synthesize` with a function with the same name, which runs the client. Here is an example how to use it as a module:
```
from call_synthesize import call_synthesize
call_synthesize(service, text, out_path, sample_rate)
```
Function parameters are described in usage section above.