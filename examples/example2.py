from cmsis_stream.cg.scheduler import *

from nodes.enveloppe import *
from nodes.filter import *
from nodes.generator import *
from nodes.instrument import *
from nodes.noise import *
from nodes.operator import *
from nodes.oscillator import *
from nodes.params import *
from nodes.sink import *
from nodes.settings import *

def create(args):
    s = Settings()
    slow = sine(2.0) >> mul(0.5) >> add(0.5)
    l = sine(440) >> mul(slow)
    r = sine(1000)
    si = sink(args)
    s.g.connect(l.o, si.l)
    s.g.connect(r.o, si.r)
    s.g.connect(null_src().o,si.s)

    return[]