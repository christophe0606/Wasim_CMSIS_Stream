from cmsis_stream.cg.scheduler import *
from .generic import *

class Noise(Source):
    def __init__(self):
        Source.__init__(self)

    @property
    def typeName(self):
        return "Noise"

def noise():
    src = Noise()
    return(src)