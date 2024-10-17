from cmsis_stream.cg.scheduler import *
from .generic import *

class Enveloppe(Node):
    def __init__(self,attack=0.01,decay=0.1):
        Node.__init__(self,["i"])
        self.addLiteralArg(attack)
        self.addLiteralArg(decay)


    @property
    def typeName(self):
        return "Enveloppe"

def env(attack=0.01,decay=0.1):
    src = Enveloppe(attack=attack,decay=decay)
    return(src)