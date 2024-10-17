from cmsis_stream.cg.scheduler import *
from .generic import *
from .params import *

class SineOscillator(Node):
    def __init__(self):
        Node.__init__(self,["f"])

    @property
    def typeName(self):
        return "SineOscillator"

class SawOscillator(Node):
    def __init__(self):
        Node.__init__(self,["f"])

    @property
    def typeName(self):
        return "SawOscillator"

class SquareOscillator(Node):
    def __init__(self):
        Node.__init__(self,["f"])

    @property
    def typeName(self):
        return "SquareOscillator"




def sine(freq=440.0):
    
    src=SineOscillator()

    connectGen(freq,src.f,name="freq")


    return(src)

def saw(freq=440.0):
    
    src=SawOscillator()

    connectGen(freq,src.f,name="freq")

    return(src)

def square(freq=440.0):
    
    src=SquareOscillator()

    connectGen(freq,src.f,name="freq")


    return(src)
