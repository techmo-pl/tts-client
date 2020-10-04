# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: tribune_tts.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='tribune_tts.proto',
  package='techmo.tribune',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x11tribune_tts.proto\x12\x0etechmo.tribune\"S\n\x11SynthesizeRequest\x12\x0c\n\x04text\x18\x01 \x01(\t\x12\x30\n\x06\x63onfig\x18\x02 \x01(\x0b\x32 .techmo.tribune.SynthesizeConfig\"\x9a\x01\n\x10SynthesizeConfig\x12\x19\n\x11sample_rate_hertz\x18\x01 \x01(\x05\x12\x33\n\routput_format\x18\x02 \x01(\x0e\x32\x1c.techmo.tribune.OutputFormat\x12\x10\n\x08language\x18\x03 \x01(\t\x12$\n\x05voice\x18\x04 \x01(\x0b\x32\x15.techmo.tribune.Voice\"_\n\x05Voice\x12\x0c\n\x04name\x18\x01 \x01(\t\x12&\n\x06gender\x18\x02 \x01(\x0e\x32\x16.techmo.tribune.Gender\x12 \n\x03\x61ge\x18\x03 \x01(\x0e\x32\x13.techmo.tribune.Age\"d\n\x12SynthesizeResponse\x12(\n\x05\x61udio\x18\x01 \x01(\x0b\x32\x19.techmo.tribune.AudioData\x12$\n\x05\x65rror\x18\x02 \x01(\x0b\x32\x15.techmo.tribune.Error\"N\n\tAudioData\x12\x19\n\x11sample_rate_hertz\x18\x01 \x01(\x05\x12\x0f\n\x07\x63ontent\x18\x02 \x01(\x0c\x12\x15\n\rend_of_stream\x18\x03 \x01(\x08\"E\n\x05\x45rror\x12\'\n\x04\x63ode\x18\x01 \x01(\x0e\x32\x19.techmo.tribune.ErrorCode\x12\x13\n\x0b\x64\x65scription\x18\x02 \x01(\t*)\n\x0cOutputFormat\x12\t\n\x05PCM16\x10\x00\x12\x0e\n\nOGG_VORBIS\x10\x01*$\n\x03\x41ge\x12\t\n\x05\x41\x44ULT\x10\x00\x12\t\n\x05\x43HILD\x10\x01\x12\x07\n\x03OLD\x10\x02*\x1e\n\x06Gender\x12\n\n\x06\x46\x45MALE\x10\x00\x12\x08\n\x04MALE\x10\x01*_\n\tErrorCode\x12\x0b\n\x07UNKNOWN\x10\x00\x12\x0b\n\x07LICENCE\x10\x01\x12\x16\n\x12TEXT_NORMALIZATION\x10\x02\x12\x11\n\rTRANSCRIPTION\x10\x03\x12\r\n\tSYNTHESIS\x10\x04\x32\\\n\x03TTS\x12U\n\nSynthesize\x12!.techmo.tribune.SynthesizeRequest\x1a\".techmo.tribune.SynthesizeResponse0\x01\x62\x06proto3')
)

_OUTPUTFORMAT = _descriptor.EnumDescriptor(
  name='OutputFormat',
  full_name='techmo.tribune.OutputFormat',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='PCM16', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='OGG_VORBIS', index=1, number=1,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=629,
  serialized_end=670,
)
_sym_db.RegisterEnumDescriptor(_OUTPUTFORMAT)

OutputFormat = enum_type_wrapper.EnumTypeWrapper(_OUTPUTFORMAT)
_AGE = _descriptor.EnumDescriptor(
  name='Age',
  full_name='techmo.tribune.Age',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='ADULT', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CHILD', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='OLD', index=2, number=2,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=672,
  serialized_end=708,
)
_sym_db.RegisterEnumDescriptor(_AGE)

Age = enum_type_wrapper.EnumTypeWrapper(_AGE)
_GENDER = _descriptor.EnumDescriptor(
  name='Gender',
  full_name='techmo.tribune.Gender',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='FEMALE', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MALE', index=1, number=1,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=710,
  serialized_end=740,
)
_sym_db.RegisterEnumDescriptor(_GENDER)

Gender = enum_type_wrapper.EnumTypeWrapper(_GENDER)
_ERRORCODE = _descriptor.EnumDescriptor(
  name='ErrorCode',
  full_name='techmo.tribune.ErrorCode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='UNKNOWN', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LICENCE', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TEXT_NORMALIZATION', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TRANSCRIPTION', index=3, number=3,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SYNTHESIS', index=4, number=4,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=742,
  serialized_end=837,
)
_sym_db.RegisterEnumDescriptor(_ERRORCODE)

ErrorCode = enum_type_wrapper.EnumTypeWrapper(_ERRORCODE)
PCM16 = 0
OGG_VORBIS = 1
ADULT = 0
CHILD = 1
OLD = 2
FEMALE = 0
MALE = 1
UNKNOWN = 0
LICENCE = 1
TEXT_NORMALIZATION = 2
TRANSCRIPTION = 3
SYNTHESIS = 4



_SYNTHESIZEREQUEST = _descriptor.Descriptor(
  name='SynthesizeRequest',
  full_name='techmo.tribune.SynthesizeRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='text', full_name='techmo.tribune.SynthesizeRequest.text', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='config', full_name='techmo.tribune.SynthesizeRequest.config', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=37,
  serialized_end=120,
)


_SYNTHESIZECONFIG = _descriptor.Descriptor(
  name='SynthesizeConfig',
  full_name='techmo.tribune.SynthesizeConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='sample_rate_hertz', full_name='techmo.tribune.SynthesizeConfig.sample_rate_hertz', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='output_format', full_name='techmo.tribune.SynthesizeConfig.output_format', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='language', full_name='techmo.tribune.SynthesizeConfig.language', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='voice', full_name='techmo.tribune.SynthesizeConfig.voice', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=123,
  serialized_end=277,
)


_VOICE = _descriptor.Descriptor(
  name='Voice',
  full_name='techmo.tribune.Voice',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='techmo.tribune.Voice.name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='gender', full_name='techmo.tribune.Voice.gender', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='age', full_name='techmo.tribune.Voice.age', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=279,
  serialized_end=374,
)


_SYNTHESIZERESPONSE = _descriptor.Descriptor(
  name='SynthesizeResponse',
  full_name='techmo.tribune.SynthesizeResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='audio', full_name='techmo.tribune.SynthesizeResponse.audio', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='error', full_name='techmo.tribune.SynthesizeResponse.error', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=376,
  serialized_end=476,
)


_AUDIODATA = _descriptor.Descriptor(
  name='AudioData',
  full_name='techmo.tribune.AudioData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='sample_rate_hertz', full_name='techmo.tribune.AudioData.sample_rate_hertz', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='content', full_name='techmo.tribune.AudioData.content', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='end_of_stream', full_name='techmo.tribune.AudioData.end_of_stream', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=478,
  serialized_end=556,
)


_ERROR = _descriptor.Descriptor(
  name='Error',
  full_name='techmo.tribune.Error',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='code', full_name='techmo.tribune.Error.code', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='description', full_name='techmo.tribune.Error.description', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=558,
  serialized_end=627,
)

_SYNTHESIZEREQUEST.fields_by_name['config'].message_type = _SYNTHESIZECONFIG
_SYNTHESIZECONFIG.fields_by_name['output_format'].enum_type = _OUTPUTFORMAT
_SYNTHESIZECONFIG.fields_by_name['voice'].message_type = _VOICE
_VOICE.fields_by_name['gender'].enum_type = _GENDER
_VOICE.fields_by_name['age'].enum_type = _AGE
_SYNTHESIZERESPONSE.fields_by_name['audio'].message_type = _AUDIODATA
_SYNTHESIZERESPONSE.fields_by_name['error'].message_type = _ERROR
_ERROR.fields_by_name['code'].enum_type = _ERRORCODE
DESCRIPTOR.message_types_by_name['SynthesizeRequest'] = _SYNTHESIZEREQUEST
DESCRIPTOR.message_types_by_name['SynthesizeConfig'] = _SYNTHESIZECONFIG
DESCRIPTOR.message_types_by_name['Voice'] = _VOICE
DESCRIPTOR.message_types_by_name['SynthesizeResponse'] = _SYNTHESIZERESPONSE
DESCRIPTOR.message_types_by_name['AudioData'] = _AUDIODATA
DESCRIPTOR.message_types_by_name['Error'] = _ERROR
DESCRIPTOR.enum_types_by_name['OutputFormat'] = _OUTPUTFORMAT
DESCRIPTOR.enum_types_by_name['Age'] = _AGE
DESCRIPTOR.enum_types_by_name['Gender'] = _GENDER
DESCRIPTOR.enum_types_by_name['ErrorCode'] = _ERRORCODE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

SynthesizeRequest = _reflection.GeneratedProtocolMessageType('SynthesizeRequest', (_message.Message,), {
  'DESCRIPTOR' : _SYNTHESIZEREQUEST,
  '__module__' : 'tribune_tts_pb2'
  # @@protoc_insertion_point(class_scope:techmo.tribune.SynthesizeRequest)
  })
_sym_db.RegisterMessage(SynthesizeRequest)

SynthesizeConfig = _reflection.GeneratedProtocolMessageType('SynthesizeConfig', (_message.Message,), {
  'DESCRIPTOR' : _SYNTHESIZECONFIG,
  '__module__' : 'tribune_tts_pb2'
  # @@protoc_insertion_point(class_scope:techmo.tribune.SynthesizeConfig)
  })
_sym_db.RegisterMessage(SynthesizeConfig)

Voice = _reflection.GeneratedProtocolMessageType('Voice', (_message.Message,), {
  'DESCRIPTOR' : _VOICE,
  '__module__' : 'tribune_tts_pb2'
  # @@protoc_insertion_point(class_scope:techmo.tribune.Voice)
  })
_sym_db.RegisterMessage(Voice)

SynthesizeResponse = _reflection.GeneratedProtocolMessageType('SynthesizeResponse', (_message.Message,), {
  'DESCRIPTOR' : _SYNTHESIZERESPONSE,
  '__module__' : 'tribune_tts_pb2'
  # @@protoc_insertion_point(class_scope:techmo.tribune.SynthesizeResponse)
  })
_sym_db.RegisterMessage(SynthesizeResponse)

AudioData = _reflection.GeneratedProtocolMessageType('AudioData', (_message.Message,), {
  'DESCRIPTOR' : _AUDIODATA,
  '__module__' : 'tribune_tts_pb2'
  # @@protoc_insertion_point(class_scope:techmo.tribune.AudioData)
  })
_sym_db.RegisterMessage(AudioData)

Error = _reflection.GeneratedProtocolMessageType('Error', (_message.Message,), {
  'DESCRIPTOR' : _ERROR,
  '__module__' : 'tribune_tts_pb2'
  # @@protoc_insertion_point(class_scope:techmo.tribune.Error)
  })
_sym_db.RegisterMessage(Error)



_TTS = _descriptor.ServiceDescriptor(
  name='TTS',
  full_name='techmo.tribune.TTS',
  file=DESCRIPTOR,
  index=0,
  serialized_options=None,
  serialized_start=839,
  serialized_end=931,
  methods=[
  _descriptor.MethodDescriptor(
    name='Synthesize',
    full_name='techmo.tribune.TTS.Synthesize',
    index=0,
    containing_service=None,
    input_type=_SYNTHESIZEREQUEST,
    output_type=_SYNTHESIZERESPONSE,
    serialized_options=None,
  ),
])
_sym_db.RegisterServiceDescriptor(_TTS)

DESCRIPTOR.services_by_name['TTS'] = _TTS

# @@protoc_insertion_point(module_scope)
