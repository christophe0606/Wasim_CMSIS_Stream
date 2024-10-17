from cmsis_stream.cg.scheduler import *
from .generic import * 
from .params import * 
from .settings import * 


def mul(amp):
    s = Settings()
    if isinstance(amp, float) or isinstance(amp, int):
        m = Binary("arm_scale_f32",CType(F32),s.nb)
        c = Constant(f"{amp}")
        s.g.connect(c,m.ib)
        src = Virtual(m,{"i":m.ia})
        return(src)
    else:
       m = Binary("arm_mult_f32",CType(F32),s.nb)
       src = Virtual(m,{"i":m.ia,"a":m.ib})
       m.ib.arOnly=True
       connectGen(amp,src.a,name="amp")
       return(src)

def add(amp):
    s=Settings()
    if isinstance(amp, float) or isinstance(amp, int):
        m = Binary("arm_offset_f32",CType(F32),s.nb)
        c = Constant(f"{amp}")
        s.g.connect(c,m.ib)
        src = Virtual(m,{"i":m.ia})
        return(src)
    else:
        add=Binary("arm_add_f32",CType(F32),s.nb)
        src = Virtual(add,{"i":add.ia,"a":add.ib})
        add.ib.arOnly=True
        connectGen(amp,src.a)
        return(src)

# Mix a list of nodes using Mixing nodes that can
# only mix 2 inputs.
# It is creating a tree of mixing nodes
# MIXNB is the ID of the mixing node since all
# nodes must have a different name (valid C variable name)
def _mixing(nodes):
    s=Settings()
    # Recursive case
    if len(nodes)>=4:
        mix = Binary("arm_add_f32",floatType,s.nb)
        mid = int(len(nodes)/2)
        a = mixing(nodes[:mid])
        b = mixing(nodes[mid:])
        s.g.connect(a.o,mix.ia)
        s.g.connect(b.o,mix.ib)
        return(mix)
    # Final cases
    elif len(nodes)==2:
        mix = Binary("arm_add_f32",floatType,s.nb)
        s.g.connect(nodes[0]["o"],mix.ia)
        s.g.connect(nodes[1]["o"],mix.ib)
        return(mix)
    elif len(nodes)==3:
        mixa = Binary("arm_add_f32",floatType,s.nb)
        mixb = Binary("arm_add_f32",floatType,s.nb)
        s.g.connect(nodes[0]["o"],mixa.ia)
        s.g.connect(nodes[1]["o"],mixa.ib)
        s.g.connect(mixa.o,mixb.ia)
        s.g.connect(nodes[2]["o"],mixb.ib)
        return(mixb)

def mixing(nodes):
    m = _mixing(nodes)
    r = Virtual(m,{})
    return(r)

