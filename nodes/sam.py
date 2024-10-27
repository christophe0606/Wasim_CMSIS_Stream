from cmsis_stream.cg.scheduler import *
from .generic import *

class Sam(Source):
    def __init__(self):
        Source.__init__(self,name="SAM")
        self.addVariableArg("(char*)txt")


    @property
    def typeName(self):
        return "Sam"