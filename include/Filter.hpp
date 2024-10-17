template<typename IN,int inputSize,
         typename OUT,int outputSize>
class LowPassFilter;

template<int outputSize>
class LowPassFilter<float,outputSize,
           float,outputSize>: 
GenericNode<float,outputSize,
              float,outputSize>
{
public:
    LowPassFilter(FIFOBase<float> &src,
         FIFOBase<float> &dst,float cutoff=20.0,float q=1.0):
    GenericNode<float,outputSize,
                float,outputSize>(src,dst){
      

      float theta_c = 2.0f * M_PI * cutoff / SAMPLINGFREQ;
      float d = 1.0 / q;
      float beta = 0.5 * (1.0-d*sin(theta_c)/2.0) / (1.0+d*sin(theta_c)/2.0);
      float gama = (0.5 + beta) * cos(theta_c);
      float b0 = (0.5 + beta - gama) / 2.0;
      float b1 = 0.5 + beta - gama;
      float b2 = (0.5 + beta - gama) / 2.0;
      float a1 = 2.0 * gama;
      float a2 = -2.0 * beta;
      coef[0]=b0;
      coef[1]=b1;
      coef[2]=b2;
      coef[3]=a1;
      coef[4]=a2;

      arm_biquad_cascade_df1_init_f32(&S,1,coef,state);
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
        
        arm_biquad_cascade_df1_f32(&S,src,dst,outputSize);
        
        return(CG_SUCCESS);
    };

protected:
    float coef[5];
    float state[4];
    arm_biquad_casd_df1_inst_f32 S;
};

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class HighPassFilter;

template<int outputSize>
class HighPassFilter<float,outputSize,
           float,outputSize>: 
GenericNode<float,outputSize,
              float,outputSize>
{
public:
    HighPassFilter(FIFOBase<float> &src,
         FIFOBase<float> &dst,float cutoff=20.0,float q=1.0):
    GenericNode<float,outputSize,
                float,outputSize>(src,dst){
      

      float theta_c = 2.0f * M_PI * cutoff / SAMPLINGFREQ;
      float d = 1.0 / q;
      float beta = 0.5 * (1.0-d*sin(theta_c)/2.0) / (1.0+d*sin(theta_c)/2.0);
      float gama = (0.5 + beta) * cos(theta_c);
      float b0 = (0.5 + beta + gama) / 2.0;
      float b1 = -0.5 - beta - gama;
      float b2 = (0.5 + beta + gama) / 2.0;
      float a1 = 2.0 * gama;
      float a2 = -2.0 * beta;
      coef[0]=b0;
      coef[1]=b1;
      coef[2]=b2;
      coef[3]=a1;
      coef[4]=a2;

      arm_biquad_cascade_df1_init_f32(&S,1,coef,state);
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
        
        arm_biquad_cascade_df1_f32(&S,src,dst,outputSize);
        
        return(CG_SUCCESS);
    };

protected:
    float coef[5];
    float state[4];
    arm_biquad_casd_df1_inst_f32 S;
};