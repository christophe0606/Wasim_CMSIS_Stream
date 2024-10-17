from cmsis_stream.cg.scheduler import *
from .generic import *

from .operator import *
from .enveloppe import *
from .params import *
from .oscillator import *
from .noise import *
from .filter import *
from .settings import *

def echo(ms=1.0,gain=1.0):
    se = Settings()
    nb = int(1e-3*ms*se.sampling_freq)
    d=dup() 
    m=mul(gain)
    s=Binary("arm_add_f32",CType(F32),se.nb)
    vadd = Virtual(s,{})
    se.g.connectWithDelay(d.aaaaaa,m.i,nb)
    se.g.connect(d.aaaaab,vadd.ia)
    se.g.connect(m.o,vadd.ib)
    return(SubGraph(d,vadd))
