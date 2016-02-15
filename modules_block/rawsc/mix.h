#ifndef _ALEPH_RAWSC_MIX_H_
#define _ALEPH_RAWSC_MIX_H_

#include "audio.h"

//! process mix matrix for audio block
extern void mix_process_block(buffer_t *inChannels, buffer_t *outChannels);

// set osc output amp, before matrix
extern void mix_set_osc_amp(int osc, fract32 val);

// set adc->dac amp
extern void mix_set_adc_dac(int adc, int dac, fract32 val);

// set osc->dac amp
extern void mix_set_osc_dac(int osc, int dac, fract32 val);

// set osc->osc modulation amp
extern void mix_set_osc_osc(int a, int b, fract32 val);

// set osc->adc modulation amp
extern void mix_set_osc_adc(int osc, int adc, fract32 val);

#endif
