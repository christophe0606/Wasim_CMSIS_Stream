#pragma once 

template<typename IN1,int inputSize1,
         typename IN2,int inputSize2,
         typename OUT,int outputSize>
class Mult;

template<int outputSize>
class Mult<float,outputSize,
           float,outputSize,
           float,outputSize>: 
GenericNode21<float,outputSize,
              float,outputSize,
              float,outputSize>
{
public:
    Mult(FIFOBase<float> &src1,
         FIFOBase<float> &src2,
         FIFOBase<float> &dst,float *f):
    GenericNode21<float,outputSize,
                float,outputSize,
                float,outputSize>(src1,src2,dst),mG(f){};

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
        float *a=this->getReadBuffer1();
        float *s=this->getReadBuffer2();
        float *dst=this->getWriteBuffer();
        if ((mG==nullptr) || (*mG!=0.0f))
        {
           arm_mult_f32(a,s,dst,outputSize);
        }
        else 
        {
            memset(dst,0,sizeof(float)*outputSize);
        }
        
        return(CG_SUCCESS);
    };

protected:
    float *mG;
};

