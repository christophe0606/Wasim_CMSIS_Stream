#pragma once 

#include <string>
#include <cstring>

extern "C" {
#include "reciter.h"
#include "sam.h"
#include "dsp/filtering_functions.h"

int debug = 0;

#define NBCOEFS 6
static arm_fir_instance_f32 S;
const float coefs[8]={ 0.01974548, 0.13238929, 0.34784997, 0.34784997, 0.13238929,
       0.01974548, 0.        , 0.};
 


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
    Sam(FIFOBase<float> &dst,char*txt):
    GenericSource<float,outputSize>(dst),mytxt(txt)
    {
        input=(char*)malloc(256);
        memset(input, 0, 256);
        //printf("phonetic input: %0x\n", input[strlen((char*)input)-1]);
        //printf("Err=%d\n",err);

        arm_fir_init_f32(&S,NBCOEFS,coefs,state,outputSize);
        
        SAMInit();
        

         err = 0;

    };

    void processText(const char*mytxt)
    {

        memset(input, 0, 256);
        for(int i=0; mytxt[i] != 0; i++)
        {
           input[i] = toupper((int)mytxt[i]);
        }

        strcat(input, "[");
        TextToPhonemes((unsigned char*)input);

        SetInput((unsigned char*)input);

        int e = SAMMain();
        
        pos=0;
        bufferLen = GetBufferLength()/50;

        err = 0;

    }

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
        #define NOISE_LEVEL 0.0f
        float *b=this->getWriteBuffer();
        unsigned char *buffer = (unsigned char *)GetBuffer();
        
        if (strlen(mytxt)!=0)
        {
            processText(mytxt);
            mytxt[0]=0;
            err = 0;
        }

        if (err == 0)
        {

            int remaining = bufferLen - pos; 
            //printf("%d\n",remaining);
            if (remaining == 0)
            {
                err=1;
            }
            
            {
                if (2*remaining>outputSize)
                {
                    remaining=outputSize>>1;
                }
                int noise = outputSize-2*remaining;
                int i=0;
                uint8_t v;
                for(i = 0;i<remaining;i++)
                {
                   tmp[2*i] = 1.0f*buffer[i+pos]/256.0f;
                   tmp[2*i+1] = 0.0f;
                }
                pos += remaining;
                for(int i=2*remaining;i<2*remaining+noise;i++)
                {
                    tmp[i] = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * NOISE_LEVEL;
                }
                arm_fir_f32(&S,tmp,b,outputSize);

            }
        }
        else if (err == 1)
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
    char* input;
    int bufferLen;
    int pos;

    float state[NBCOEFS+outputSize]={0};
    float tmp[outputSize];
    char* mytxt;

};