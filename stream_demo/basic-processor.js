import FreeQueue from "./free-queue.js";
import { FRAME_SIZE, RENDER_QUANTUM } from "./constants.js";

/**
 * A simple AudioWorkletProcessor node.
 *
 * @class BasicProcessor
 * @extends AudioWorkletProcessor
 */
class BasicProcessor extends AudioWorkletProcessor {
  static get parameterDescriptors() {
    return [
      {
        name: "customGain",
        defaultValue: 1,
        minValue: 0,
        maxValue: 1,
        automationRate: "k-rate",
      },
    ];
  }

  /**
   * Constructor to initialize, input and output FreeQueue instances
   * and atomicState to synchronise Worker with AudioWorklet
   * @param {Object} options AudioWorkletProcessor options
   *    to initialize inputQueue, outputQueue and atomicState
   */
  constructor(options) {
    super();

    this.oldG=1;

    this.queue = options.processorOptions.queue;
    this.atomicState = options.processorOptions.atomic;
    //this.flag = options.processorOptions.flag;
    this.HEAPF32 = new Float32Array(options.processorOptions.mem);
    this.HEAPU32 = new Uint32Array(options.processorOptions.mem);

    
    Object.setPrototypeOf(this.queue, FreeQueue.prototype);
    
    //Atomics.store(this.atomicState, 0, 0);

    //Atomics.notify(this.atomicState, 0);
  }

  process(inputs, outputs,parameters) {

    //const input = inputs[0];
    const output = outputs[0];
    
    // Push data from input into inputQueue.
    //this.inputQueue.push(input, RENDER_QUANTUM);
    
    //console.log(output.length);
    // Try to pull data out of outputQueue and store it in output.
    var didPull = this.queue.pull(output, RENDER_QUANTUM);
    if (!didPull) 
    {
        console.log("failed to pull.");
    }

    var g = parameters["customGain"].length > 1
            ? parameters["customGain"][i]
            : parameters["customGain"][0];
    if (g!=this.oldG)
    {
      this.oldG=g;
      this.port.postMessage({
        message: 'setParam',
        param:'flag',
        val:g
      });
    }
    
    
    
    
    // Wake up worker to generate new frame
    Atomics.store(this.atomicState, 0, 0);
    Atomics.notify(this.atomicState, 0,1);
    
    return true;
  }
}

registerProcessor('basic-processor', BasicProcessor);
