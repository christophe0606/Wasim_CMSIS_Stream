#pragma once


static double gTime = 0;

#ifndef OSX

using namespace arm_cmsis_stream;

template<typename IN1, int inputSize1,
         typename IN2, int inputSize2,
         typename IN3, int inputSize3>
class WebAudioSink;

template<int inputSize,typename IN3>
class WebAudioSink<float,inputSize,
                   float,inputSize,
                   IN3, 1>: public NodeBase
{
public:
    WebAudioSink(FIFOBase<float> &srcLeft,
                 FIFOBase<float> &srcRight,
                 FIFOBase<IN3> &nullSeq,
                 struct FreeQueue* output,
                 int32_t *atomic):
    mSrcLeft(srcLeft),
    mSrcRight(srcRight),
    mOut(output),
    mNullSeq(nullSeq),
    mAtomic(atomic){
        outStereo=(float**)malloc(sizeof(float*)*2);
    };

    ~WebAudioSink()
    {
        free(outStereo);
    }



    int prepareForRunning() final
    {
        if (this->willUnderflowLeft() || this->willUnderflowRight())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    int run() final
    {
        float *left=this->getReadBufferLeft();
        float *right=this->getReadBufferRight();
        IN3 *n=this->getReadBufferSeq();

        if (!canPush(mOut,inputSize))
        {
       
           ATOMICS_WAIT_RESULT_T ret = emscripten_wasm_wait_i32(mAtomic, 1, /*timeout=*/-1);
           atomic_store((atomic_uint*)mAtomic, 1);
        }

        /* This is not really great but it looks like the
        atomic is not working on some browser :-( */
        while(!canPush(mOut,inputSize))
            ;

        outStereo[0] = left;
        outStereo[1] = right;
        
        bool res=FreeQueuePush(mOut, (float**)outStereo, inputSize);
        if (!res)
        {
            return(CG_BUFFER_OVERFLOW);
        }

        gTime += 1.0*inputSize/SAMPLINGFREQ;


        return(CG_SUCCESS);
    };

protected:
    float **outStereo;

    struct FreeQueue* mOut;
    int32_t *mAtomic;

    float * getReadBufferLeft(int nb=inputSize){return mSrcLeft.getReadBuffer(nb);};

    bool willUnderflowLeft(int nb = inputSize){return mSrcLeft.willUnderflowWith(nb);};

    float * getReadBufferRight(int nb=inputSize){return mSrcRight.getReadBuffer(nb);};

    bool willUnderflowRight(int nb = inputSize){return mSrcRight.willUnderflowWith(nb);};

    IN3 * getReadBufferSeq(){return mNullSeq.getReadBuffer(1);};

private:
    FIFOBase<float> &mSrcLeft;
    FIFOBase<float> &mSrcRight;
    FIFOBase<IN3> &mNullSeq;

};
#else
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#include <unistd.h>

template<typename IN1, int inputSize1,
         typename IN2, int inputSize2,
         typename IN3, int inputSize3>
class AUSink;

template<int inputSize,typename IN3>
class AUSink<float,inputSize,
             float,inputSize,
             IN3, 1>:public NodeBase
{
public:
    AUSink(FIFOBase<float> &srcLeft,
           FIFOBase<float> &srcRight,
           FIFOBase<IN3> &nullSeq,
           dsp_context *context):
    mSrcLeft(srcLeft),
    mSrcRight(srcRight),
    mNullSeq(nullSeq),
    mContext(context){};

    int prepareForRunning() final
    {
        if (this->willUnderflowLeft() || this->willUnderflowRight())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    #define MAXNB 1000
    int run() final
    {
        float *left=this->getReadBufferLeft();
        float *right=this->getReadBufferRight();
        IN3 *n=this->getReadBufferSeq();

        bool overflowLeft=true;
        bool overflowRight=true;
        int nb = 0;

        while((overflowLeft || overflowRight) && (nb < MAXNB))
        {
           pthread_mutex_lock( &mContext->mutex1 );
           overflowLeft = mContext->outputFifo[0]->willOverflowWith(inputSize);
           overflowRight = mContext->outputFifo[1]->willOverflowWith(inputSize);
           pthread_mutex_unlock( &mContext->mutex1 );
           //pthread_cond_wait( &mContext->condition_cond, &mContext->condition_mutex );
           usleep(1000); // 1ms
           nb++;
        }
        if (nb==MAXNB)
        {
            return(CG_BUFFER_OVERFLOW);
        }
        pthread_mutex_lock( &mContext->mutex1 );
        float *out = mContext->outputFifo[0]->getWriteBuffer(inputSize);
        memcpy(out,left,sizeof(float)*inputSize);

        out = mContext->outputFifo[1]->getWriteBuffer(inputSize);
        memcpy(out,right,sizeof(float)*inputSize);
        pthread_mutex_unlock( &mContext->mutex1 );

        gTime += 1.0*inputSize/SAMPLINGFREQ;

        return(CG_SUCCESS);
    };

protected:
    dsp_context *mContext;

    float * getReadBufferLeft(int nb=inputSize){return mSrcLeft.getReadBuffer(nb);};

    bool willUnderflowLeft(int nb = inputSize){return mSrcLeft.willUnderflowWith(nb);};

    float * getReadBufferRight(int nb=inputSize){return mSrcRight.getReadBuffer(nb);};

    bool willUnderflowRight(int nb = inputSize){return mSrcRight.willUnderflowWith(nb);};

    IN3 * getReadBufferSeq(){return mNullSeq.getReadBuffer(1);};

private:
    FIFOBase<float> &mSrcLeft;
    FIFOBase<float> &mSrcRight;
    FIFOBase<IN3> &mNullSeq;

};



template<typename IN1, int inputSize1,
         typename IN2, int inputSize2,
         typename IN3, int inputSize3>
class WavSink;

template<int inputSize,typename IN3>
class WavSink<float,inputSize,
              float,inputSize,
              IN3, 1>: 
public NodeBase
{
public:
    WavSink(FIFOBase<float> &srcLeft,
            FIFOBase<float> &srcRight,
            FIFOBase<IN3> &nullSeq,
            const char *filename):
    mSrcLeft(srcLeft),
    mSrcRight(srcRight),
    mNullSeq(nullSeq){
    drwav_data_format format;
    format.container = drwav_container_riff;     // <-- drwav_container_riff = normal WAV files, drwav_container_w64 = Sony Wave64.
    format.format = DR_WAVE_FORMAT_IEEE_FLOAT;          // <-- Any of the DR_WAVE_FORMAT_* codes.
    format.channels = 2;
    format.sampleRate = 44100;
    format.bitsPerSample = sizeof(float)*8;
    drwav_init_file_write(&wav, filename, &format, NULL);

    };

    ~WavSink()
    {
        drwav_uninit(&wav);
    }

    int prepareForRunning() final
    {
        if (this->willUnderflowLeft() || this->willUnderflowRight())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    int run() final
    {
        float *left=this->getReadBufferLeft();
        float *right=this->getReadBufferRight();
        IN3 *n=this->getReadBufferSeq();

        for(int i=0;i<inputSize;i++)
        {
            interleaved[2*i] = left[i];
            interleaved[2*i+1] = right[i];
        }

        drwav_uint64 nb = drwav_write_pcm_frames(&wav, 
            inputSize, interleaved);

        gTime += 1.0*inputSize/SAMPLINGFREQ;

        return(CG_SUCCESS);
    };

protected:
    drwav wav;

    float * getReadBufferLeft(int nb=inputSize){return mSrcLeft.getReadBuffer(nb);};

    bool willUnderflowLeft(int nb = inputSize){return mSrcLeft.willUnderflowWith(nb);};

    float * getReadBufferRight(int nb=inputSize){return mSrcRight.getReadBuffer(nb);};

    bool willUnderflowRight(int nb = inputSize){return mSrcRight.willUnderflowWith(nb);};

    IN3 * getReadBufferSeq(){return mNullSeq.getReadBuffer(1);};

private:
    FIFOBase<float> &mSrcLeft;
    FIFOBase<float> &mSrcRight;
    FIFOBase<IN3> &mNullSeq;

    float interleaved[inputSize*2];
};
#endif 