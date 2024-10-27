from cmsis_stream.cg.scheduler import *
from .settings import *



class Node(GenericNode):
    def __init__(self,names,input_nb=None,the_input_type = CType(F32)):
        s = Settings()
        GenericNode.__init__(self,f"Node_{s.new_node_id()}")
        inb = s.nb 
        if input_nb:
            inb = input_nb
        for n in names:
            self.addInput(n,the_input_type,inb)
        self.addOutput("o",CType(F32),s.nb)

    def __rshift__(self,b):
        s = Settings()
        if hasattr(b, 'i'):
           s.g.connect(self.o,b.i)
        return(b)

class Source(GenericSource):
    def __init__(self,nb=None,name=None,the_type = CType(F32)):
        s = Settings()
        if name is None:
            name = f"Node_{s.new_node_id()}"
        GenericSource.__init__(self,name)
        if nb:
           self.addOutput("o",the_type,nb)
        else:
           self.addOutput("o",the_type,s.nb)

    def __rshift__(self,b):
        s = Settings()
        if hasattr(b, 'i'):
           s.g.connect(self.o,b.i)
        return(b)

class Virtual():
    def __init__(self,src,remap):
        self._src = src 
        self._remap = remap

    def __getattr__(self,name):
        if name in self._remap:
            return(self._remap[name])
        else:
            return(self._src[name])

    def __getitem__(self,name):
        if name in self._remap:
            return(self._remap[name])
        else:
            return(self._src[name])

    def __rshift__(self,b):
        s = Settings()
        if hasattr(b, 'i'):
           s.g.connect(self.o,b.i)
        return(b)

class SubGraph():
    def __init__(self,src,dst):
        self._src = src 
        self._dst = dst

    def __getattr__(self,name):
        if name=="i":
            return(self._src.i)
        if name=="o":
            return(self._dst.o)
        return AttributeError

    def __getitem__(self,name):
        if name=="i":
            return(self._src.i)
        if name=="o":
            return(self._dst.o)
        return IndexError

    def __rshift__(self,b):
        s = Settings()
        if hasattr(b, 'i'):
           s.g.connect(self.o,b.i)
        return(b)


def dup():
    s = Settings()
    d = Duplicate(f"dup_{s.new_node_id()}",CType(F32),s.nb,2)
    return(d)