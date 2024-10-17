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

NBCHANNELS=16

musics=["empire","ghost","overture","pink","toccata","champion"]

def create(args):
    s = Settings()
    
    si = sink(args)
    s.g.connect(null_src().o,si.s)
    
    seq = midi(musics[0],nb_channels=NBCHANNELS)
    c = []
    for i in range(NBCHANNELS):
        m = midi_wav()
        e = midi_env()
        c.append(e)
        seqOutput = chr(ord('A')+i)
        s.g.connect(seq[seqOutput],m.i)
        s.g.connect(seq[seqOutput],e.c)
        s.g.connect(m.o,e.i)


    even=c[0::2]
    odd=c[1::2]
    ra = mixing(even)
    rb = mixing(odd)
    s.g.connect(ra.o,si.l)
    s.g.connect(rb.o,si.r)



    return[]