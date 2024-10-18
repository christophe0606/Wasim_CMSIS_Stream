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
from nodes.sam import *

def create(args):
    s = Settings()

    si = sink(args)
    sam = Sam()
    s.g.connect(sam.o,si.l)
    s.g.connect(sam.o,si.r)
    s.g.connect(null_src().o,si.s)

    return []

