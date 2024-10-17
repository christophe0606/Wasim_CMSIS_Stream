import FreeQueue from "./free-queue.js";
import Module from './stream_kernel.js';
import {FRAME_SIZE} from "./constants.js";

/**
 * Worker message event handler.
 * This will initialize worker with FreeQueue instance and set loop for audio
 * processing. 
 */
self.onmessage = (msg) => {
  if (msg.data.type === "init") {
    console.log("init");
    //postMessage({type:'workerstarted'});
    Module.init_sched();
    
  }
  else if (msg.data.type === "runsched") {
    console.log("runsched");
    postMessage({type:'startaudio'});
    Module.runsched();
  }
  
  //if (msg.data.type === "init") {
  /*

Here we should get data from wasm to create the pointer data structure
required by free-queue.js
Then we should send an event do audio worker basic-processor
so that it can access the free queue

  */
    //let { inputQueue, outputQueue, atomicState } = msg.data.data;
    //Object.setPrototypeOf(inputQueue, FreeQueue.prototype);
    //Object.setPrototypeOf(outputQueue, FreeQueue.prototype);
    
    // buffer for storing data pulled out from queue.
    //const input = new Float32Array(FRAME_SIZE);
    // loop for processing data.
    /*while (Atomics.wait(atomicState, 0, 0) === 'ok') {
      
      // pull data out from inputQueue.
      const didPull = inputQueue.pull([input], FRAME_SIZE);
      
      if (didPull) {
        // If pulling data out was successfull, process it and push it to
        // outputQueue
        const output = input.map(sample => 0.1 * sample);
        outputQueue.push([output], FRAME_SIZE);
      } 

      Atomics.store(atomicState, 0, 0);
    }*/

    //Module.runsched(inputQueue,outputQueue,atomicState);
  //}
};
