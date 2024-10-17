#include <map>
#include <string>

using namespace arm_cmsis_stream;

/* Global parameters hash table */
static std::map<std::string,float> gParams;

void writeParam(std::string a, float v)
{
    gParams[a]=v;
};

template<typename OUT,int outputSize>
class Const;

template<int outputSize>
class Const<float,outputSize>: 
GenericSource<float,outputSize>
{
public:
    Const(FIFOBase<float> &dst,float v=0.0f):
    GenericSource<float,outputSize>(dst),mVal(v){};

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
            b[i] = mVal;
        }

        return(CG_SUCCESS);
    };

protected:
    float mVal;
};

template<typename OUT,int outputSize>
class Param;

template<int outputSize>
class Param<float,outputSize>: 
GenericSource<float,outputSize>
{
public:
    Param(FIFOBase<float> &dst,const std::string s,const float v):
    GenericSource<float,outputSize>(dst),mKey(s){
        writeParam(s,v);
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
           b[i] = gParams[mKey];
        }

        return(CG_SUCCESS);
    };

protected:
    const std::string mKey;
};