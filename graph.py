from cmsis_stream.cg.scheduler import *
### Define new types of Nodes 
import argparse 

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

g = Graph()

s = Settings(g)

parser = argparse.ArgumentParser(
                    prog='Stream',
                    description='AudioFun')

parser.add_argument('-mac',
                    action='store_true')
parser.add_argument('-file',
                    action='store_true')

parser.add_argument('-duration', type=float, default=10, help='Duration')
args = parser.parse_args()


nbSched = int(1.0 * args.duration * s.sampling_freq / s.nb)



### Define nodes

#modAmp = amp(0.2)>>oscillator(freq=1.0) >> add(0.5)
#modFreq = amp(200)>>oscillator(freq=0.1) >> add(440.0)
#signal = oscillator(freq=modFreq,amp=modAmp)
#another = amp(0.1)>>oscillator(freq=450)
#
#signal >> mul(another) >> mul(4.5) >> sink()


#tri = imp(2)>>env(attack=0.001,decay=0.1)
#noise() >> mul(tri) >> mul(0.1) >> sink()
#m=speed(16.0)>>seq("60 60 60") >> env(attack=0.001,decay=0.1) >> mul(0.05)
#amp(1.0)>>sine(freq=440)>>mul(m)>>sink()

#~basslow: speed 1.0
#>> seq 33 _33 36_33_ 36_33_ 28 _28 31_28_ 31
#>> sawsynth 0.01 0.2 

import examples.example3 as ex 
#import examples.example4 as ex 
others=ex.create(args)


#noise() >> lpf(100.0, 1.0) >> sink()

print("Generate graphviz and code")

conf=Configuration()
#if args.file:
#    conf.debugLimit=nbSched
if args.mac:
    conf.cOptionalArgs=["dsp_context *context"] + others
else:
    conf.cOptionalArgs=["struct FreeQueue* output_queue",
                        "int32_t *atomic"] + others
conf.CAPI=False
conf.CMSISDSP=True
conf.memoryOptimization=True
conf.switchCase=False
#conf.nodeIdentification = True

sched = g.computeSchedule(config=conf)


print("Schedule length = %d" % sched.scheduleLength)
print("Memory usage %d bytes" % sched.memory)

sched.ccode(".",conf)

generateGenericNodes(".")
generateCGStatus(".")


with open("test.dot","w") as f:
    sched.graphviz(f)

