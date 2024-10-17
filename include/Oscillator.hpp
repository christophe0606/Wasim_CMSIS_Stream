#pragma once

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class SineOscillator;

template<int inputSize,int outputSize>
class SineOscillator<float,inputSize,
                 float,outputSize>: 
GenericNode<float,inputSize,
              float,outputSize>
{
public:
    SineOscillator(FIFOBase<float> &src,
               FIFOBase<float> &dst):
    GenericNode<float,inputSize,
                  float,outputSize>(src,dst){
                    mPhase = 0.0f;
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
        float *f=this->getReadBuffer();
        float *b=this->getWriteBuffer();
        
        if (inputSize==1)
        {
               mPhase += f[0] /SAMPLINGFREQ;
        }

        for(int i=0;i<outputSize;i++)
        {
            //b[i] = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * 0.3f;
            if (inputSize>1)
            {
                mPhase += f[i] /SAMPLINGFREQ;
            }
            if (mPhase>1.0f)
            {
                mPhase -= 1.0f;
            }
            b[i] = sin(2.0f*M_PI*mPhase);
        }

        return(CG_SUCCESS);
    };
protected:
    float mPhase;

};

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class SawOscillator;

template<int inputSize,int outputSize>
class SawOscillator<float,inputSize,
                 float,outputSize>: 
GenericNode<float,inputSize,
              float,outputSize>
{
public:
    SawOscillator(FIFOBase<float> &src,
               FIFOBase<float> &dst):
    GenericNode<float,inputSize,
                  float,outputSize>(src,dst){
                    mPhase = 0.0f;
                    mInc=0.0f;
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
        float *f=this->getReadBuffer();
        float *b=this->getWriteBuffer();
        
        if (inputSize==1)
        {
            if (f[0]!=0.0f)
            {
                mInc = f[0];
            }
        }

        for(int i=0;i<outputSize;i++)
        {
            //b[i] = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * 0.3f;
            
            if (inputSize > 1) 
            {
              if (f[i]!=0.0f)
              {
                 mInc = f[i];
              }
            }
            mPhase += mInc /SAMPLINGFREQ;
            if (mPhase>1.0f)
            {
                mPhase -= 1.0f;
            }
            b[i] = (mPhase * 2.0f - 1.0f);
        }

        return(CG_SUCCESS);
    };
protected:
    float mPhase;
    float mInc;
};

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class SquareOscillator;

template<int inputSize,int outputSize>
class SquareOscillator<float,inputSize,
                 float,outputSize>: 
GenericNode<float,inputSize,
              float,outputSize>
{
public:
    SquareOscillator(FIFOBase<float> &src,
               FIFOBase<float> &dst):
    GenericNode<float,inputSize,
                  float,outputSize>(src,dst){
                    mPhase = 0.0f;
                    mInc=0.0f;
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
        float *f=this->getReadBuffer();
        float *b=this->getWriteBuffer();
        
        if (inputSize==1)
        {
            if (f[0]!=0)
            {
                mInc = f[0];
            }
        }

        for(int i=0;i<outputSize;i++)
        {
            //b[i] = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * 0.3f;
            if (inputSize>1)
            {
                if (f[i]!=0)
                {
                    mInc = f[i];
                }
            }
            mPhase += mInc /SAMPLINGFREQ;
            if (mPhase>1.0f)
            {
                mPhase -= 1.0f;
            }
            b[i] = mPhase <=0.5 ? 1.0f : -1.0f;
        }

        return(CG_SUCCESS);
    };
protected:
    float mPhase;
    float mInc;
};