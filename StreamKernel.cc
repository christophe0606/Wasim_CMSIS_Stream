/**
 * Copyright 2018 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */



#include <stdio.h>
#include <emscripten.h>
#include "emscripten/bind.h"
#include <emscripten/wasm_worker.h>
#include <emscripten/threading.h>
#include <stdatomic.h>
#include <string>

// Include free_queue.h according to its location in the project.
#include "free_queue.h" 

#include "custom.h"
#include "scheduler.h"

extern void writeParam(std::string a, float v);
using namespace emscripten;

struct FreeQueue *output;
atomic_uint* atomic;

float *test;

#define NBBUFS 16

/*
const float left[4]={1.0,2.0,3.0,4.0};
const float right[4]={11.0,12.0,13.0,14.0};

const float *debug[2]={left,right};
*/

EMSCRIPTEN_KEEPALIVE void init_sched()
{
  output = CreateFreeQueue(NBBUFS*128,2);
  /*
  PrintQueueAddresses(output);

  printf("Check content %zu : %f %f\r\n",output->channel_count,debug[0][0],debug[0][1]);

  
  bool res=FreeQueuePush(output, (float**)debug, 4);
  res=FreeQueuePush(output, (float**)debug, 4);

  if (!res)
  {
    printf("Error first push\r\n");
  }
  
  */
  atomic = (atomic_uint*)malloc(sizeof(atomic_uint));
  /*
  test = (float*)malloc(sizeof(float)*128);
  test[0] = 1.0f;
  test[1] = 2.0f;
  test[2] = 3.0f;
  test[3] = 4.0f;
  */

  atomic_store(atomic, 1);

  //bool res=FreeQueuePush(output, (float **)&test, 4);
  
  EM_ASM(
    postMessage({type:'workerstarted',
        atomic:$0,
        queuePointers:{
           memory:wasmMemory,
           bufferLengthPointer:$1,
           channelCountPointer:$2,
           statePointer:$3,
           channelDataPointer:$4
        }
    });,&atomic,&(output->buffer_length),
&(output->channel_count),&(output->state),
&(output->channel_data)
    );

  
//ATOMICS_WAIT_RESULT_T ret = emscripten_wasm_wait_i32((int32_t*)atomic, 1, /*timeout=*/-1);
    //printf("Waiting done\r\n");


}

EMSCRIPTEN_KEEPALIVE void setParam(const char* s,float v)
{
   writeParam(s,v);
}

EMSCRIPTEN_KEEPALIVE void runsched()
{
      
  uint32_t nb;
  int err;

  struct FreeQueue* output_queue=reinterpret_cast<struct FreeQueue*>(output);
  int32_t* atomicval=reinterpret_cast<int32_t*>(atomic);

  nb=scheduler(&err,output_queue,atomicval);
  if (err!=0)
  {
     EM_ASM(
    postMessage({type:'schedended',
      error:$0,
      nb:$1
     });,err,nb);
  }

}

EMSCRIPTEN_BINDINGS(StreamModule) {
  function("runsched", &runsched,allow_raw_pointers());
  function("init_sched", &init_sched);
  function("setParam", &setParam,allow_raw_pointers());
}
