#pragma once 

template<typename OUT,int outputSize>
class Noise;

template<int outputSize>
class Noise<float,outputSize>: 
GenericSource<float,outputSize>
{
public:
    Noise(FIFOBase<float> &dst):
    GenericSource<float,outputSize>(dst){
    };

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
        float *b=this->getWriteBuffer();
        

        for(int i=0;i<outputSize;i++)
        {
            b[i] = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * 0.3f;
        }

        return(CG_SUCCESS);
    };

};