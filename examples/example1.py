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
from nodes.effect import *

def create(args):
   s = Settings()
   basslow = speed(1.0) >> \
             seq("33 _33 36_33_ 36_33_ 28 _28 31_28_ 31")>> \
             sawsynth(attack=0.01,decay=0.2) >> \
             lpf(500, 1.0)
   
   bassmid = speed(1.0) >> \
             seq("45 _45 48_45_ 48_45_ 40 _40 43_40_ 43") >>  \
             mul(0.99) >>  \
             sawsynth(attack=0.01,decay=0.21) >>  \
             lpf(1000, 1.0)
   lead= speed(1.0) >>  \
         seq("64_60_ 57_60_ 64_60_ 64_65_ 64_59_ 55_59_ 64 62") >>  \
         squaresynth(attack=0.01,decay=0.2) >>  \
         lpf(800, 1.0) >> \
         mul(0.3) >> mul(param("flag",1.0))
   sno = speed(4.0) >> seq("_ 60") >> sn(0.05) >> mul(0.5)
   bdo = speed(4.0) >> seq("60") >> bd(0.03) >> mul(1.0)
   hho = speed(16.0) >> seq("60") >> hh(0.03) >> mul(1.0)
   r   = mixing([basslow,bassmid,lead,sno,bdo,hho]) >> \
         echo(ms=30,gain=1.0)
   si=sink(args)
   
   s.g.connect(r.o, si.l)
   s.g.connect(r.o, si.r)
   s.g.connect(null_src().o,si.s)

   return []

