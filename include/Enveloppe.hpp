#pragma once 

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class Enveloppe;

template<int outputSize>
class Enveloppe<float,outputSize,
           float,outputSize>: 
GenericNode<float,outputSize,
              float,outputSize>
{
public:
    Enveloppe(FIFOBase<float> &src,
         FIFOBase<float> &dst,float attack=0.01,float decay=0.1):
    GenericNode<float,outputSize,
                float,outputSize>(src,dst),
                mAttack(attack),mDecay(decay){
                    mPos=0.0f;
                    mScale=1.0f;
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
        float *src=this->getReadBuffer();
        float *dst=this->getWriteBuffer();

        float attack_len = mAttack * SAMPLINGFREQ;
        float decay_len = mDecay * SAMPLINGFREQ;
        float duration = attack_len + decay_len;
        for(int i=0;i<outputSize;i++)
        {
             if (src[i]>0.0f)
             {
                 mPos=0.0;
                 mScale=src[i];
             }
             if (mPos <= attack_len)
             {
                if (attack_len==0)
                {
                    dst[i] = 0.0f;
                }
                else 
                {
                    dst[i] = mPos / attack_len;
                }
             } 
             else if ((mPos > attack_len) && (mPos < duration))
             {
                 if (decay_len==0)
                 {
                    dst[i] = 0.0f;
                 }
                 else 
                 {
                    dst[i] = (duration-mPos)/decay_len;
                 }
             }
             else
             {
                dst[i] = 0;
             }
             dst[i] = dst[i] * mScale; 
             mPos += 1;

        }

        
        return(CG_SUCCESS);
    };

protected:
    float mAttack,mDecay;
    float mPos,mScale;
};