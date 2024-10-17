#ifndef _INSTRUMENTS_H_
#define _INSTRUMENTS_H_
extern const int16_t *getInstrumentWaveForm (int16_t instrumentID);
extern const int16_t *getDrumWaveForm (int16_t instrumentID);
extern const uint16_t getDrumWaveFormFrequency (int16_t instrumentID);
extern const uint16_t getDrumEndingSampleIndex (int16_t instrumentID);

#endif
