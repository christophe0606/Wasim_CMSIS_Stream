from cmsis_stream.cg.scheduler import *
from .generic import *

from .operator import *
from .enveloppe import *
from .params import *
from .oscillator import *
from .noise import *
from .filter import *
from .settings import *


def sawsynth(attack=0.01,decay=0.1):
    s = Settings()
    d = dup()
    #print(d._outputs)
    pitch = mul(261.626)
    s.g.connect(d.aaaaaa, pitch.i)
    envn = env(attack=attack,decay=decay)
    s.g.connect(d.aaaaab, envn.i)
    r = saw(pitch) >> mul(envn)
    return(SubGraph(d,r))

def squaresynth(attack=0.01,decay=0.1):
    s = Settings()
    d = dup() 
    pitch = mul(261.626)
    s.g.connect(d.aaaaaa, pitch.i)
    envn = env(attack=attack,decay=decay)
    s.g.connect(d.aaaaab, envn.i)
    r=square(pitch) >> mul(envn)
    return(SubGraph(d,r))


def bd(decay):
    s = Settings()
    d = dup()

    envn = env(attack=0.003,decay=decay)
    s.g.connect(d.aaaaaa,envn.i)
    ep = env(attack=0.01,decay=0.1)
    s.g.connect(d.aaaaab,ep.i)
    p = ep >> mul(50)>>add(60)
    o =  sine(p) >> mul(envn)
    return(SubGraph(d,o))

def hh(decay):
    envn = env(attack=0.003,decay=decay)
    o = noise() >> mul(envn) >> hpf(15000.0,1.0) >> mul(0.8)
    return(SubGraph(envn,o))

def sn(decay):
    s = Settings()
    sntriggee = dup()
    snpitch = env(attack=0.001,decay=0.1) 
    s.g.connect(sntriggee.aaaaaa,snpitch.i)
    snpitch = snpitch >> mul(55.0)>>add(60.0)

    
    snenv = env(attack=0.001,decay=decay)
    s.g.connect(sntriggee.aaaaab,snenv.i)

    no = noise() >> mul(0.3)

    o1 = sine(snpitch)>>add(no)
    m = mul(snenv)
    s.g.connect(o1.o,m.i)
    o = m #>> hpf(5000,1)

    return(SubGraph(sntriggee,o))



