from cmsis_stream.cg.scheduler import *
from .generic import *

class LowPassFilter(Node):
    def __init__(self,cutoff,q):
        Node.__init__(self,["i"])
        self.addLiteralArg(cutoff,q)

    @property
    def typeName(self):
        return "LowPassFilter"

class HighPassFilter(Node):
    def __init__(self,cutoff,q):
        Node.__init__(self,["i"])
        self.addLiteralArg(cutoff,q)

    @property
    def typeName(self):
        return "HighPassFilter"

def lpf(c,q):
    return(LowPassFilter(c,q))

def hpf(c,q):
    return(HighPassFilter(c,q))
