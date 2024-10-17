from cmsis_stream.cg.scheduler import *
from .generic import *
from .SeqParser import seqVals

midCmdType=CStructType("midi_cmd_t",16)

class NullSource(Source):
    def __init__(self):
        Source.__init__(self,nb=1)

    @property
    def typeName(self):
        return "NullSource"

class MIDISeq(Source):
    def __init__(self,music,nb_channels=16):
        s = Settings()
        GenericSource.__init__(self,f"Node_{s.new_node_id()}")


        for i in range(nb_channels):
            self.addOutput(chr(ord('A')+i),midCmdType,1)

        self.addVariableArg(music)

    @property
    def args(self):
        """String of fifo args for object initialization
            with literal argument and variable arguments"""
        allArgs=self.listOfargs
        nb = len(allArgs) 
        others = "{" + "".join(joinit([x.pointer for x in allArgs[1:]],",")) + "}"
        # Add specific argrs after FIFOs
        sched = []
        if self.schedArgs:
            for lit in self.schedArgs:
                sched.append(lit.arg)
        if sched:
            return (others + "," + "".join(joinit(sched,",")))
        else:
           return (others)

    def ioTemplate(self):
        """ioTemplate is different for window
        """
        theType=self._outputs[self.outputNames[0]].ctype  
        ios="%s,%d" % (theType,1)
        return(ios)


    @property
    def typeName(self):
        return "MIDISeq"

class MIDIWav(Node):
    def __init__(self):
        Node.__init__(self,["i"],input_nb=1,the_input_type=midCmdType)

    @property
    def typeName(self):
        return "MIDIWav"

class MIDIEnv(Node):
    def __init__(self):
        s = Settings()
        GenericNode.__init__(self,f"Node_{s.new_node_id()}")

        self.addInput("i",CType(F32),s.nb)
        self.addInput("c",midCmdType,1)

        self.addOutput("o",CType(F32),s.nb)

    @property
    def typeName(self):
        return "MIDIEnv"

class Imp(Source):
    def __init__(self,v):
        Source.__init__(self)
        self.addLiteralArg(v)

    @property
    def typeName(self):
        return "Imp"

class Choose(Source):
    def __init__(self,v):
        Source.__init__(self)
        self.addVariableArg(v)

    @property
    def typeName(self):
        return "Choose"

class Seq(Node):
    def __init__(self,v):
        Node.__init__(self,[])
        self.addInput("i",CType(F32),1)
        self.addVariableArg(v)

    @property
    def typeName(self):
        return "Seq"


def midi(v,nb_channels=16):
    src = MIDISeq(v,nb_channels=nb_channels)
    return(src)

def midi_wav():
    src = MIDIWav()
    return(src)

def midi_env():
    src = MIDIEnv()
    return(src)

def imp(v):
    src = Imp(v)
    return(src)

def null_src():
    src = NullSource()
    return(src)

def choose(v):
    if isinstance(v,list):
        v = ",".join([str(x) for x in v])
    src = Choose("{"+v+"}")
    return(src)

def seq(v):
    r="{}"
    if isinstance(v,str):
        r = seqVals(v)
    src = Seq(r)
    return(src)



        