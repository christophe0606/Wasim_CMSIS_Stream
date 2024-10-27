#include <CoreServices/CoreServices.h>
#include <CoreAudio/CoreAudioTypes.h>
#include <CoreAudio/AudioHardware.h>
#include <AudioUnit/AudioUnit.h>
#include <signal.h>
#include <custom.h>
#include "scheduler.h"
#include "cg_status.h"
#include "GenericNodes.h"

using namespace arm_cmsis_stream;

//#define TOFILE
#define OK 0 
#define FAILED -1 

bool audio_started=false;
bool error = false;
float flag = 1;


dsp_context context;

static float outputLeft[2048];
static float outputRight[2048];

FIFO<float,2048,0,1> outputFifoLeft(outputLeft);
FIFO<float,2048,0,1> outputFifoRight(outputRight);

#define ERR_FAIL_COND_V(A,R) \
  if (A) \
  {\
  	return(R);\
  }

AudioUnit audio_unit;

float t=0;
float phase=0;
bool first=true;

OSStatus core_audio_callback(void *data,
                                   AudioUnitRenderActionFlags *ioActionFlags,
                                   const AudioTimeStamp *inTimeStamp,
                                   UInt32 inBusNumber,
                                   UInt32 inNumberFrames,
                                   AudioBufferList *ioData)
{
	dsp_context *c=(dsp_context*)data;
    int len = inNumberFrames;
    UInt32 i, nBuffers = ioData->mNumberBuffers;

    pthread_mutex_lock( &c->mutex1 );
    for(i = 0; i < ioData->mNumberBuffers; i++)
    {
        int d = ioData->mBuffers[i].mDataByteSize/sizeof(float);
        float *out=(float*)ioData->mBuffers[i].mData;
        if (c->outputFifo[i]->willUnderflowWith(d))
        {
            memset(out,0,sizeof(float)*d);
        }
        else
        {
           float *in = c->outputFifo[i]->getReadBuffer(d);
           memcpy(out,in,sizeof(float)*d);
        }
        
    }
    pthread_mutex_unlock( &c->mutex1 );
    //pthread_cond_signal( &c->condition_cond );

 return(noErr);
}

void* audiogen(void *g)
{
	/*while(!error)
	{

		pthread_mutex_lock( &context.mutex1 );
		for(int i =0;i<512;i++)
		{
			context.output[i] = sin(2*M_PI*phase);
			phase += 600.0 / 44100;
			if (phase > 1.0)
			{
				phase = -1.0;
			}
		}
		pthread_mutex_unlock( &context.mutex1 );
		pthread_cond_wait( &context.condition_cond, &context.condition_mutex );
	}*/

    int32_t err;
    printf("Start sched\r\n");
	uint32_t nb=scheduler(&err,&context);
  
    printf("End with err = %d and nb =%d\r\n",err,nb);
    pthread_exit(NULL);
	return(NULL);
}


int init_audio()
{
	AudioStreamBasicDescription strdesc={0};
	strdesc.mFormatID = kAudioFormatLinearPCM;
	strdesc.mFormatFlags = kLinearPCMFormatFlagIsFloat | kAudioFormatFlagIsNonInterleaved;
	
	strdesc.mChannelsPerFrame = 2;
	strdesc.mBytesPerFrame = sizeof(float);
	strdesc.mBytesPerPacket = sizeof(float);

	strdesc.mSampleRate = 44100;
	strdesc.mFramesPerPacket = 1;
	strdesc.mBitsPerChannel = 8*sizeof(float);

	OSStatus result = noErr;
	AURenderCallbackStruct callback;
	AudioComponentDescription desc;
	AudioComponent comp = NULL;
	const AudioUnitElement output_bus = 0;
	const AudioUnitElement bus = output_bus;
	const AudioUnitScope scope = kAudioUnitScope_Input;

	memset(&desc, 0,sizeof(desc));
	desc.componentType = kAudioUnitType_Output;
	desc.componentSubType = kAudioUnitSubType_HALOutput;  /* !!! FIXME: ? */
	comp = AudioComponentFindNext(NULL, &desc);
	desc.componentManufacturer = kAudioUnitManufacturer_Apple;

	result = AudioComponentInstanceNew(comp, &audio_unit);
	ERR_FAIL_COND_V(result != noErr, FAILED);
	ERR_FAIL_COND_V(comp == NULL, FAILED);

	result = AudioUnitSetProperty(audio_unit,
								  kAudioUnitProperty_StreamFormat,
								  scope, bus, &strdesc, sizeof(strdesc));
	ERR_FAIL_COND_V(result != noErr, FAILED);

	memset(&callback, 0,sizeof(AURenderCallbackStruct));
	callback.inputProc = core_audio_callback;
	callback.inputProcRefCon = &context;
	result = AudioUnitSetProperty(audio_unit,
								  kAudioUnitProperty_SetRenderCallback,
								  scope, bus, &callback, sizeof(callback));
	ERR_FAIL_COND_V(result != noErr, FAILED);

	result = AudioUnitInitialize(audio_unit);
	ERR_FAIL_COND_V(result != noErr, FAILED);

	result = AudioOutputUnitStart(audio_unit);
	ERR_FAIL_COND_V(result != noErr, FAILED);

	audio_started = true;
	return OK;
}

void stopaudio()
{
	audio_started = false;
	error = true;
	  AudioComponentInstanceDispose(audio_unit);

}

static void catch_function(int signo) {
    stopaudio();
    error = true;
    printf("Audio stopped. Ctrl-c\r\n");
}

int main(int argc, char const *argv[])
{
	context.mutex1 = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&context.mutex1,NULL);
    context.condition_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&context.condition_mutex,NULL);
    context.condition_cond  = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&context.condition_cond,NULL);
    context.outputFifo[0] = &outputFifoLeft;
    context.outputFifo[1] = &outputFifoRight;


	if (signal(SIGINT, catch_function) == SIG_ERR) {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        return(EXIT_FAILURE);
    }

    pthread_t thread1;

    pthread_create( &thread1, NULL, &audiogen, NULL);

    #ifndef TOFILE
	if (init_audio()!=OK)
	{
		printf("Error\r\n");
		stopaudio();
	}
	printf("Audio started\r\n");
	while(audio_started)
	{
		sleep(1);
	}
	printf("End\r\n");
	pthread_cancel(thread1);
	#else 
	pthread_join(thread1,NULL);
	#endif
	
	return 0;
}