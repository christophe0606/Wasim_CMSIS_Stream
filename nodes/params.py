from cmsis_stream.cg.scheduler import *
from .settings import *
from .generic import *

class Const(Source):
    def __init__(self,name,v,nb=1):
        Source.__init__(self,nb)
        self.v = v
        self.valName = name
        self.addLiteralArg(v)

    @property
    def typeName(self):
        return "Const"

    @property
    def graphvizName(self):
        """Name for graph vizualization"""
        return ("%s=%f<BR/>(%s)" % (self.valName,self.v,self.typeName))

class Param(Source):
    def __init__(self,name,v,nb=1):
        Source.__init__(self,nb)
        self.v = v
        self.valName = name
        self.addLiteralArg(self.valName,v)

    @property
    def typeName(self):
        return "Param"

    @property
    def graphvizName(self):
        """Name for graph vizualization"""
        return ("%s<BR/>(%s)" % (self.valName,self.typeName))

def onlyAr(x):
    if hasattr(x, 'arOnly'):
        if x.arOnly:
            return(True)
    return(False)

# by default a const or param has length 1
def connectGen(f,anInput,name="val"):
    s = Settings()
    # By default const are kr and generate only one sample
    # But when connecting to some nodes like arm_mult
    # they can't and need to be ar
    if isinstance(f, float):
        if not onlyAr(anInput):
           c = Const(name,f)
           anInput._nbSamples=1
        else:
           c = Const(name,f,nb=s.nb)
        s.g.connect(c.o,anInput)
    elif isinstance(f, int):
        if not onlyAr(anInput):
           c = Const(name,f)
           anInput._nbSamples=1
        else:
           c = Const(name,f,nb=s.nb)
        s.g.connect(c.o,anInput)
    else:
        # if the node is only ar, both side must have nb
        # samples
        # If it is not possible it will be catched on C++ side
        if not onlyAr(anInput):
           anInput._nbSamples=f.o._nbSamples
        else:
            anInput._nbSamples=s.nb
            f.o._nbSamples=s.nb
        s.g.connect(f.o,anInput)

def amp(v):
    c = Const("amp",v)
    return(c)

def param(s,d):
    p = Param(s,d)
    return(p)

def speed(v):
    c = Const("speed",v)
    return(c)
