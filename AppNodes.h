#ifndef _APPNODES_H_
#define _APPNODES_H_

#include <math.h>
#include "cg_status.h"

#ifndef OSX
#include <emscripten.h>
#include "emscripten/bind.h"
#include <emscripten/wasm_worker.h>
#include <emscripten/threading.h>
#include <stdatomic.h>
#else
#include "NullSink.h"
#endif


#include "Sink.hpp"
#include "Params.hpp"
#include "Enveloppe.hpp"
#include "Filter.hpp"
#include "Generator.hpp"
#include "Noise.hpp"
#include "Operator.hpp"
#include "Oscillator.hpp"
#include "MIDI/MIDISeq.hpp"
#include "MIDI/MIDIWav.hpp"
#include "MIDI/MIDIEnv.hpp"





#endif