#pragma once 

#include "MIDI/instruments.hpp"

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class MIDIWav;

template<int outputSize>
class MIDIWav<midi_cmd_t,1,
           float,outputSize>: 
GenericNode<midi_cmd_t,1,
              float,outputSize>
{
public:
    MIDIWav(FIFOBase<midi_cmd_t> &src,
            FIFOBase<float> &dst):
    GenericNode<midi_cmd_t,1,
                float,outputSize>(src,dst){
      
             on = false;
             magnitude = 0;
             phase=0;
             waveform = getInstrumentWaveForm(0);
             mPhaseIncrement=0;
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
        midi_cmd_t *c=this->getReadBuffer();
        float *b=this->getWriteBuffer();

        //memset(b,0,sizeof(float)*outputSize);
        //return(CG_SUCCESS);

        if (c->cmd == NOTE_OFF)
        {
        	on = false;
             magnitude = 0;
             phase=0;
             waveform = getInstrumentWaveForm(0);
             mPhaseIncrement=0;
        }
        if (c->cmd == NOTE_ON)
        {
        	on = true;
        	if (c->amp==0)
        	{
        		on = false;
        	}

        	magnitude = (int32_t)(32767*c->amp);

        	

        	if (c->inst>=129)
            {
               isDrum = true;
               instrumentID = c->inst - 129;
               waveform = getDrumWaveForm(instrumentID);
  
               mPhaseIncrement = uint32_t(1.0* getDrumWaveFormFrequency(instrumentID) / SAMPLINGFREQ  / SAMPLINGFREQ * 0xFFFFFFFF);
               phase = 0; // start at the beginning
               drum_ending_sample_index = getDrumEndingSampleIndex(instrumentID); // remember the end of the waveform
            }
            else
            {
               isDrum = false;
               instrumentID = c->inst;
               waveform = getInstrumentWaveForm(instrumentID);
            }

            if (!isDrum)
            {
              //printf("%f\r\n",c->tune);
              mPhaseIncrement = uint32_t(1.0*c->tune / SAMPLINGFREQ * 0xFFFFFFFF);
            }
        }

        // With memory sharing the buffer may
        // contain garbage. So we need to write
        // something to it.
        if (!on)
        {
        	memset(b,0,sizeof(float)*outputSize);
        	return(CG_SUCCESS);

        }

        if ((c->cmd == NO_MIDI_CMD) || (c->cmd == NOTE_ON))
        {
            //printf("%d %d\r\n",mPhaseIncrement,magnitude);
                if (isDrum)
                {
                    int16_t d,val1,val2;
                    int32_t frac;
                    int16_t index1,index2;
            
                    for(int i=0;i<outputSize;i++)
                    {
                        index1 = phase >> 18;
                        index2 = index1 + 1;
                        if (index2 >= drum_ending_sample_index)
                        {
                           b[i] = 0;
                        }
                        else
                        {
                           val1 = waveform[index1];
                           val2 = waveform[index2];
                           frac = (phase & 0x3FFF) << 14;
                           #if defined (ARM_MATH_DSP)
                             d = (q15_t) __QSUB16(val2, val1);
                           #else
                             d = (q15_t) __SSAT(((q31_t) val2 - val1), 16);
                           #endif
                           d = (frac * d) >> 24;
                           d = val1 + d;
                           b[i] = __SSAT((val1 * magnitude) >> 15,16)/32767.0;
                        }
                        phase = (phase + mPhaseIncrement);
            
                    }
                }
                else
                {
                    int16_t d,val1,val2;
                    int32_t frac;
            
                    for(int i=0;i<outputSize;i++)
                    {
                        val1 = waveform[phase>>24];
                        val2 = waveform[1 + (phase>>24)];
                        frac = (phase & 0xFFFFF) << 8;
                        #if defined (ARM_MATH_DSP)
                          d = (q15_t) __QSUB16(val2, val1);
                        #else
                          d = (q15_t) __SSAT(((q31_t) val2 - val1), 16);
                        #endif
                        d = __SSAT((frac * d) >> 24,16);
                        d = val1 + d;
                        b[i] = __SSAT(((q31_t)val1 * magnitude) >> 15,16)/32767.0;
            
                        phase = (phase + mPhaseIncrement);
            
                    }
                }
        }

        
        return(CG_SUCCESS);
    };
protected:
	bool on;
	uint32_t mPhaseIncrement;
    uint32_t phase;
    int16_t magnitude;
    const int16_t* waveform;
    uint16_t drum_ending_sample_index;
    bool isDrum;
    int instrumentID;
};