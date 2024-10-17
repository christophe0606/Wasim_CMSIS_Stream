from cmsis_stream.cg.scheduler import *
from .settings import *

class WavSink(GenericSink):
    def __init__(self,seqType=CType(F32),filename="stream.wav"):
        s = Settings()
        GenericSink.__init__(self,f"Node_{s.new_node_id()}")
        self.addInput("l",CType(F32),s.nb)
        self.addInput("r",CType(F32),s.nb)
        self.addInput("s",seqType,1)
        self.addLiteralArg(filename)

    @property
    def typeName(self):
        return "WavSink"

class AUSink(GenericSink):
    def __init__(self,seqType=CType(F32),context="context"):
        s = Settings()
        GenericSink.__init__(self,f"Node_{s.new_node_id()}")
        self.addInput("l",CType(F32),s.nb)
        self.addInput("r",CType(F32),s.nb)
        self.addInput("s",seqType,1)

        self.addVariableArg(context)

    @property
    def typeName(self):
        return "AUSink"

class WebAudioSink(GenericSink):
    def __init__(self,seqType=CType(F32),outputBuffer="unknown"):
        s = Settings()
        GenericSink.__init__(self,f"Node_{s.new_node_id()}")
        self.addInput("l",CType(F32),s.nb)
        self.addInput("r",CType(F32),s.nb)
        self.addInput("s",seqType,1)
        self.addVariableArg(outputBuffer)
        self.addVariableArg("atomic")

    @property
    def typeName(self):
        return "WebAudioSink"

def sink(args,seqType=CType(F32)):
    if args.mac:
       if args.file:
          return(WavSink(filename = "stream.wav",seqType=seqType))
       else:
          return(AUSink(seqType=seqType))
    else:
       return(WebAudioSink(outputBuffer="output_queue",seqType=seqType))

