// Copyright (c) 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
import FreeQueue from './free-queue.js'
import { QUEUE_SIZE } from './constants.js';


/*

Better to create it on webassembly side
We should wait for a message from the worker
then create a data structure to pass to the audio
worklet so that it can access the free-queue

*/
// Create 2 FreeQueue instances with 4096 buffer length and 1 channel.
//const inputQueue = new FreeQueue(QUEUE_SIZE, 1);
//const outputQueue = new FreeQueue(QUEUE_SIZE, 1);
// Create an atomic state for synchronization between worker and AudioWorklet.


/*const atomicState = new Int32Array(
    new SharedArrayBuffer(1 * Int32Array.BYTES_PER_ELEMENT)
);
*/


const name = "basic-processor";

/*
const startAudio = async (context) => {
  
  
  await context.audioWorklet.addModule(name+".js");
  window.cmsisstream = new AudioWorkletNode(context, name,
    { numberOfInputs:1,
      numberOfOutputs:1,
      outputChannelCounts: [1],
      channelCounts: [1],
      processorOptions: {
          inputQueue,
          outputQueue,
          atomicState
        }
    });
  
  window.oscillator = new OscillatorNode(context);

  window.analyser = context.createAnalyser();

  window.oscillator.connect(cmsisstream);
  window.cmsisstream.connect(window.analyser);
  window.analyser.connect(context.destination);
  audioContext.suspend();
  oscillator.start();
  
 
};
*/
const worker = new Worker('worker.js', { type: 'module'});

worker.postMessage({
  type: 'init'/*,
  data: {
    inputQueue,
    outputQueue,
    atomicState
  }*/
});

worker.onerror = (event) => {
  console.log("There is an error with your worker! " + event);
};

function errMessage(id)
{
     switch(id)
     {
       case 0: /**< No error */
          return("Success")
       case -1: /**< FIFO underflow */
          return("Buffer underflow")
       case -2: /**< FIFO overflow */
          return("Buffer overflow")
       case -3: /**< Memory allocation failure */
          return("Memory allocation failure")
       case -4: /**< Node initialization failure */
          return("Initialization failure")
       case -6: /**< Stop execution due to FIFO overflow or underflow (asynchronous mode for pure function) */
           return("Buffer error")
       case -7:  /**< RTOS API error */
           return("Os error")
       default:
           return("unknown error")
     }
}

worker.onmessage = (msg) => {
  //console.log(msg);
  if (msg.data.type === "workerstarted")
  {
      console.log("Worker started");
      //console.log(msg.data.data);
      var mem = new Uint32Array(msg.data.queuePointers.memory.buffer);
      var memi = new Int32Array(msg.data.queuePointers.memory.buffer);

      var atomic=msg.data.atomic;
      window.atomicState = memi.subarray(
        mem[atomic/4]/4,
        mem[atomic/4]/4 +1);

      //var flag = msg.data.flag;
      //window.flag = flag;

      //var debug =  Atomics.load(window.atomicState, 0);

      //console.log(debug);
      window.wasmMem = msg.data.queuePointers.memory.buffer;
      window.queue = FreeQueue.fromPointers(msg.data.queuePointers);
      /*
      console.log(msg.data.queuePointers);
      console.log("Test received")
      console.log(window.queue.channelData[0]);
      console.log(window.queue.channelData[1]);
      */

      //console.log(atomicState);
      //console.log(queue.states);

      //console.log(queue.getAvailableSamples());
      //var a = new Float32Array(4);
      //var res = queue.pull([a],4);
      //console.log(res);
      //console.log(a);

      worker.postMessage({type: 'runsched'});
  }
  else if (msg.data.type === "startaudio")
  {
    console.log("Start audio context");
    const buttonEl = document.getElementById('button-start');
    buttonEl.disabled = false;
      window.startAudio = async (context) => {
  
  
  await context.audioWorklet.addModule(name+".js");
  window.cmsisstream = new AudioWorkletNode(context, name,
    { numberOfInputs:1,
      numberOfOutputs:1,
      outputChannelCount: [2],
      channelCount: [1],
      processorOptions: {
          queue:window.queue,
          atomic:window.atomicState,
          flag:window.flag,
          mem:window.wasmMem
        }
    });

  window.cmsisstream.port.onmessage = (msg) => {
    if (msg.data.message="setParam")
    {
        /*console.log("Set param in main");
        worker.postMessage({
          type: 'setParam',
          param:msg.data.param,
          val:msg.data.val
        });*/
    };
  };

  window.gainParam = cmsisstream.parameters.get("customGain");

  window.oscillator = new OscillatorNode(context);

  window.splitter  = context.createChannelSplitter(2);
  window.analyserL = context.createAnalyser();
  window.analyserR = context.createAnalyser();
  window.merger    = context.createChannelMerger(2);


  window.oscillator.connect(window.cmsisstream);
  window.cmsisstream.connect(window.splitter);
  window.splitter.connect(window.analyserL, 0);
  window.splitter.connect(window.analyserR, 1);
  window.analyserL.connect(window.merger, 0, 0)
  window.analyserR.connect(window.merger, 0, 1)
  window.merger.connect(context.destination)
  //window.cmsisstream.connect(window.analyser);
  //window.analyser.connect(context.destination);
  //audioContext.suspend();
  oscillator.start();
  
 
};
  } else if (msg.data.type === "schedended")
  {
    const buttonEl = document.getElementById('button-start');
    /*
    const leadCheck = document.getElementById('lead');
    leadCheck.disabled=true;
    */

    audioContext.suspend();
    buttonEl.disabled = true;
    const para = document.getElementById('error');
    para.innerHTML=errMessage(msg.data.error)+" after nb " + 
      msg.data.nb + " iterations.\n\r"+"Reload the page if you want to try again !";
  }
}

window.visualColorLeft = '#51A3A3' //#FE5E41';
// window.visualizerBackground = "rgba(255, 255, 255, 0.5)"
window.visualizerBackground = "white"
window.visualColorRight = '#fc684e' //'#FE5E41' //'#75485E' //#D8F1A0'

window.visualizeTimeDomainData = ({canvas, analyserL}) => {
  let ctx = canvas.getContext("2d");
  let bufferLength = analyserL.fftSize;
  let dataArray = new Uint8Array(bufferLength);

  ctx.clearRect(0, 0, canvas.width, canvas.height);
  // const fpsInterval = 1000 / 60;
  // var then = Date.now();
  // var now, elapsed;

  function drawL() {

    requestAnimationFrame(drawL);

    // now = Date.now();
    // elapsed = now - then;
    // if (elapsed > fpsInterval) {

      // Get ready for next frame by setting then=now, but also adjust for your
      // specified fpsInterval not being a multiple of RAF's interval (16.7ms)
      // then = now - (elapsed % fpsInterval);

      // Put your drawing code here
      analyserL.getByteTimeDomainData(dataArray);
      ctx.fillStyle = window.visualizerBackground;
      ctx.fillRect(0, 0, canvas.width, canvas.height);
      ctx.lineWidth = 2;
      ctx.strokeStyle = window.visualColorLeft;
      let sliceWidth = canvas.width * 1.0 / bufferLength;
      let x = 0;
      ctx.beginPath();
      for(let i = 0; i < bufferLength; i++) {
        let v = dataArray[i] / 128.0;
        let y = canvas.height - v * canvas.height/2;
        
        if(i === 0) {
          ctx.moveTo(x, y);
        } else {
          ctx.lineTo(x, y);
        }
        x += sliceWidth;
        
      }
      // ctx.closePath();
      // ctx.beginPath();
      ctx.moveTo(canvas.width, canvas.height/2);
      ctx.lineTo(canvas.width, canvas.height/2);
      ctx.stroke();
      ctx.closePath();
      
    // };
  }
  drawL();
}

window.visualizeFrequencyData = ({canvas, analyserL}) => {
  let ctx = canvas.getContext("2d");
  let bufferLength = analyserL.frequencyBinCount;
  let dataArray = new Uint8Array(bufferLength);
  function drawFreq() {
    requestAnimationFrame(drawFreq);
        analyserL.getByteFrequencyData(dataArray);
        ctx.beginPath();
        ctx.fillStyle = window.visualizerBackground;
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        const barWidth = (canvas.width / bufferLength) * 2.5;
        ctx.fillStyle = window.visualColorRight;
        for(let i = 0; i < bufferLength; i++) {
          let fractionalVolume = dataArray[i]/255
          let barHeight = fractionalVolume*canvas.height;
          ctx.fillRect(
            (barWidth + 1)*i,
            canvas.height ,  
            barWidth,
            -barHeight
          );
        }
        ctx.closePath();
  }
  drawFreq();
}

var audioRunning = false;
var audioCreated = false;


// A simple onLoad handler. It also handles user gesture to unlock the audio
// playback.
window.addEventListener('load', async () => {
  window.audioContext = new AudioContext();
  const buttonEl = document.getElementById('button-start');
  /*const leadCheck = document.getElementById('lead');*/
  buttonEl.disabled = true;
  /*leadCheck.addEventListener('change',async(event) =>{
    if (event.currentTarget.checked) {
       window.gainParam.setValueAtTime(1.0, window.audioContext.currentTime + 1);
    } 
    else {
       window.gainParam.setValueAtTime(0.0, window.audioContext.currentTime + 1);
    }
  });
  */

  buttonEl.addEventListener('click', async () => {      

    if (!audioCreated) {
       audioCreated = true;

       await window.startAudio(window.audioContext);
    }
    if (!audioRunning)
    {

       window.audioContext.resume();
       buttonEl.textContent = 'stop';
       audioRunning = true;
       /*leadCheck.disabled=false;*/


       if ( document.getElementById("visualizerL")) {
          window.visualizeTimeDomainData({canvas: document.getElementById("visualizerL"), analyserL: window.analyserL});
       }
       if ( document.getElementById("freqVisualizerL")) {
         window.visualizeFrequencyData({canvas: document.getElementById("freqVisualizerL"), analyserL: window.analyserL});
       }

       if ( document.getElementById("visualizerR")) {
          window.visualizeTimeDomainData({canvas: document.getElementById("visualizerR"), analyserL: window.analyserR});
       }
       if ( document.getElementById("freqVisualizerR")) {
         window.visualizeFrequencyData({canvas: document.getElementById("freqVisualizerR"), analyserL: window.analyserR});
       }
    }
    else 
    {
      window.audioContext.suspend();
      buttonEl.textContent = 'start';
      audioRunning = false;
      /*leadCheck.disabled=true;*/

    }
  }, false);
});
