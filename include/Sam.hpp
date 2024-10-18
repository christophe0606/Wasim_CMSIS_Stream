#pragma once 

#include <string>
#include <cstring>

extern "C" {
#include "reciter.h"
#include "sam.h"

int debug = 0;

}

template<typename OUT,int outputSize>
class Sam;

//Only works for 44100
//There is a duplication because original is
//at 22050 so we just double the sample
//which is not very nice upsampling
template<int outputSize>
class Sam<float,outputSize>: 
GenericSource<float,outputSize>
{
public:
    Sam(FIFOBase<float> &dst):
    GenericSource<float,outputSize>(dst)
    {
        mem.reserve(256);
        input=(unsigned char*)malloc(256);
        memset(input, 0, 256);
        strcpy((char*)input,"THIS IS A TEST[");
        err = TextToPhonemes(input);
        //printf("phonetic input: %0x\n", input[strlen((char*)input)-1]);
        //printf("Err=%d\n",err);
        if (err==1)
        {
            SetInput(input);
            err=SAMMain();
            //printf("Err=%d\n",err);
            pos=0;
            bufferLen = GetBufferLength()/50;
        }

    };

    ~Sam()
    {
        free(input);
    }

    int prepareForRunning() final
    {
        if (this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    int run() final 
    {
        #define NOISE_LEVEL 0.1f
        float *b=this->getWriteBuffer();
        char *buffer = GetBuffer();
        
        if (err == 1)
        {
            int remaining = bufferLen - pos; 
            //printf("%d\n",remaining);
            if (remaining == 0)
            {
                err=0;
            }
            else
            {
                if (2*remaining>outputSize)
                {
                    remaining=outputSize>>1;
                }
                int noise = outputSize-2*remaining;
                int i=0;
                for(i = 0;i<remaining;i++)
                {
                   b[2*i] = buffer[i+pos];
                   b[2*i+1] = buffer[i+pos];
                }
                pos += remaining;
                for(int i=2*remaining;i<2*remaining+noise;i++)
                {
                    b[i] = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * NOISE_LEVEL;
                }

            }
        }
        else if (err == 0)
        {
            for(int i=0;i<outputSize;i++)
            {
                b[i] = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * NOISE_LEVEL;
            }
        }


        return(CG_SUCCESS);
    };

protected:
    int err = 0;
    std::vector<unsigned char> mem;
    unsigned char* input;
    int bufferLen;
    int pos;

};