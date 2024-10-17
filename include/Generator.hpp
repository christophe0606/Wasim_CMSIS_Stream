#pragma once 

template<typename OUT,int outputSize>
class NullSource;

template<>
class NullSource<float,1>: 
GenericSource<float,1>
{
public:
    NullSource(FIFOBase<float> &dst):
    GenericSource<float,1>(dst){
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
        
        
        return(CG_SUCCESS);
    };


};

template<typename OUT,int outputSize>
class Imp;

template<int outputSize>
class Imp<float,outputSize>: 
GenericSource<float,outputSize>
{
public:
    Imp(FIFOBase<float> &dst,float freq=1.0f):
    GenericSource<float,outputSize>(dst),mPeriod(uint32_t(SAMPLINGFREQ/freq)){
        mClock=0;
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
            float out = (mClock % mPeriod) == 0;
            if (mClock == mPeriod)
            {
                mClock=0;
            }
            b[i] = out;
            mClock += 1;
        }

        return(CG_SUCCESS);
    };

protected:
    uint32_t mPeriod;
    uint32_t mClock;
};

template<typename OUT,int outputSize>
class Choose;

template<int outputSize>
class Choose<float,outputSize>: 
GenericSource<float,outputSize>
{
public:
    Choose(FIFOBase<float> &dst,std::vector<float> elems):
    GenericSource<float,outputSize>(dst),mElems(elems){
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
        
        uint32_t s = (uint32_t)(1.0 * rand() / (float)RAND_MAX * (mElems.size()-1));
        float v = mElems[s];

        for(int i=0;i<outputSize;i++)
        {
            b[i] = v;
        }

        return(CG_SUCCESS);
    };

protected:
    std::vector<float> mElems;
};

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class Seq;

template<int outputSize>
class Seq<float,1,float,outputSize>: 
GenericNode<float,1,float,outputSize>
{
public:
    Seq(FIFOBase<float> &src,
        FIFOBase<float> &dst,std::vector<std::tuple<float,float>> elems):
    GenericNode<float,1,
                float,outputSize>(src,dst),mElems(elems){
                    step=0;
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
        float *s=this->getReadBuffer();

        float *b=this->getWriteBuffer();
        uint32_t bar_length = (uint32_t)(240.0 / BPM * SAMPLINGFREQ/s[0]);
        for(int i=0;i<outputSize;i++)
        {
            b[i] = 0.0f;
            for (auto event : mElems)
            {
               float time = std::get<0>(event);
               float midi = std::get<1>(event);
               if ((step % bar_length) == ((uint32_t)(time * bar_length)))
               {
                   if (midi != 0)
                   {
                    b[i] = powf(2.0f,(midi - 60.0f)/12.0f);
                   }
               }
            }
            step += 1;
        }

        return(CG_SUCCESS);
    };

protected:
    std::vector<std::tuple<float,float>>  mElems;
    uint32_t step;
};

