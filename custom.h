#ifndef _CUSTOM_H_

#include <stdint.h>
extern const uint8_t empire[];
extern const uint8_t bohemian[];
extern const uint8_t ghost[];
extern const uint8_t overture[];
extern const uint8_t pink[];
extern const uint8_t toccata[];
extern const uint8_t champion[];

#define SAMPLINGFREQ 44100.0f
#define BPM 65

#ifndef OSX
#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/threading.h>
#define FREE_QUEUE_IMPL 
// Include free_queue.h according to its location in the project.
#include "free_queue.h" 
#else
#include <pthread.h>
#include "cg_status.h"
#include "GenericNodes.h"

using namespace arm_cmsis_stream;

typedef struct {
  pthread_mutex_t mutex1;
  pthread_mutex_t condition_mutex;
  pthread_cond_t condition_cond;
  FIFO<float,2048,0,1> *outputFifo[2];
} dsp_context;
#endif

#define CG_BEFORE_BUFFER __attribute__((aligned(8)))
#endif 