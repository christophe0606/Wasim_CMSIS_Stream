#pragma once

enum envState {
  kIdle,
  kDelay,
  kAttack,
  kHold,
  kDecay,
  kSustain,
  kRelease,
  kForced
};

template<typename IN1,int inputSize1,
         typename IN2,int inputSize2,
         typename OUT,int outputSize>
class MIDIEnv;

template<int outputSize>
class MIDIEnv<midi_cmd_t,1,
              float,outputSize,
              float,outputSize>: 
GenericNode21<midi_cmd_t,1,
              float,outputSize,
              float,outputSize>
{
public:
    MIDIEnv(FIFOBase<midi_cmd_t> &src1,
    	    FIFOBase<float> &src2,
            FIFOBase<float> &dst):
    GenericNode21<midi_cmd_t,1,
                float,outputSize,
                float,outputSize>(src1,src2,dst){
      
        on = false;
        mNbSamplesPerMs = (int32_t)(SAMPLINGFREQ / 1000);
        state = kIdle;

        delay(0.0f);  // default values...
        attack(10.5f);
        hold(2.5f);
        decay(35.0f);
        sustain(0.68f);
        release(30.0f);
        releaseNoteOn(30.0f);

        nb = 0;
        drum = false;
                };

    void setDrum(bool r)
    {
        drum = r;
    }

    void noteOn(void)
    {
        //printf("Note on %d\n",nb);
        if (state == kIdle || state == kDelay || release_forced_count == 0) {
            count = delay_count;
            attenuation = 0;
            if (count > 0) {
                state = kDelay;
                attenuationInc = 0;
            } else {
                state = kAttack;
                count = attack_count;
                attenuationInc = 0x40000000 / (int32_t)count;
            }
        } else if (state != kForced) {
            state = kForced;
            count = release_forced_count;
            attenuationInc = (-attenuation) / (int32_t)count;
        }
    }

    void noteOff(void)
    {
        //printf("Note off %d\n",nb);
        if (state != kIdle && state != kForced) {
            state = kRelease;
            count = release_count;
            attenuationInc = (-attenuation) / (int32_t)count;
        }
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
        midi_cmd_t *src1=this->getReadBuffer1();
        float *a=this->getReadBuffer2();
        float *b=this->getWriteBuffer();
        q31_t v,out;

        
        if (src1->cmd == NOTE_OFF)
        {
        	noteOff();
        }
        if (src1->cmd == NOTE_ON)
        {
        	noteOn();
        }
        
        if (drum)
        {
            memcpy(b,a,sizeof(float32_t)*outputSize);
            nb += outputSize;
            return(CG_SUCCESS);
        }

        if (state == kIdle)
        {
            memset(b,0,sizeof(float32_t)*outputSize);
            nb += outputSize;
            return(CG_SUCCESS);
        }

        for(int i=0;i<outputSize;i++)
        {
            if (count == 0)
            {
               //printf("End state %d at %d\n",state,nb);

               switch(state)
               {
                 case kAttack:
                   count = hold_count;
                   if (count > 0)
                   {
                    state = kHold;
                    attenuation = 0x40000000;
                    attenuationInc = 0;
                   }
                   else
                   {
                     state = kDecay;
                     count = decay_count;
                     attenuationInc = (sustain_mult - 0x40000000) / (int32_t)count;
                   }
                 break;

                 case kHold:
                     state = kDecay;
                     count = decay_count;
                     attenuationInc = (sustain_mult - 0x40000000) / (int32_t)count;
                 break;

                 case kDecay:
                   state = kSustain;
                   count = 0xFFFF;
                   attenuation = sustain_mult;
                   attenuationInc = 0;
                 break;

                 case kSustain:
                    count = 0xFFFF;
                 break;

                 case kRelease:
                    state = kIdle;
                 break;

                 case kForced:
                   attenuation = 0;
                   count = delay_count;
                   if (count > 0)
                   {
                    state = kDelay;
                    attenuationInc = 0;
                   }
                   else
                   {
                    state = kAttack;
                    count = attack_count;
                    attenuationInc = 0x40000000 / (int32_t)count;
                   }
                 break;

                 case kDelay:
                    state = kAttack;
                    count = attack_count;
                    attenuationInc = 0x40000000 / count;
                 break;

                 case kIdle:
                       count = 0xFFFF;
                 break;
               }
            }
            if (state == kIdle)
            {
               b[i] = 0;
            }
            else
            {
               v = __SSAT(int(a[i]*32767),16);
               out = ((q63_t) v * attenuation) >> 31;
               b[i] = __SSAT(out, 16)/32767.0;
            }
            attenuation += attenuationInc;
            count--;
            nb++;
        }

        return(CG_SUCCESS);
    };

    void delay(float milliseconds) {
        delay_count = milliseconds2count(milliseconds);
    }
    void attack(float milliseconds) {
        attack_count = milliseconds2count(milliseconds);
        if (attack_count == 0) attack_count = 1;
    }
    void hold(float milliseconds) {
        hold_count = milliseconds2count(milliseconds);
    }
    void decay(float milliseconds) {
        decay_count = milliseconds2count(milliseconds);
        if (decay_count == 0) decay_count = 1;
    }
    void sustain(float level) {
        if (level < 0.0f) level = 0;
        else if (level > 1.0f) level = 1.0f;
        sustain_mult = level * 1073741824.0f;
    }
    void release(float milliseconds) {
        release_count = milliseconds2count(milliseconds);
        if (release_count == 0) release_count = 1;
    }
    void releaseNoteOn(float milliseconds) {
        release_forced_count = milliseconds2count(milliseconds);
        if (release_count == 0) release_count = 1;
    }

    uint16_t milliseconds2count(float milliseconds) {
        if (milliseconds < 0.0f) milliseconds = 0.0f;
        uint32_t c = (uint32_t)(milliseconds*mNbSamplesPerMs);
        if (c > 65535) c = 65535; // allow up to 11.88 seconds
        return c;
    }

protected:
	bool on;
	int32_t mNbSamplesPerMs;
    enum envState state;
    uint16_t count;      // how much time remains in this state, in 8 sample units


    uint16_t delay_count;
    uint16_t attack_count;
    uint16_t hold_count;
    uint16_t decay_count;
    int32_t  sustain_mult;
    uint16_t release_count;
    uint16_t release_forced_count;

    q31_t  attenuation;
    q31_t  attenuationInc;

    int nb;
    bool drum;
};