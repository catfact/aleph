#ifndef _ALEPH_RAWSC_MIX_H_
#define _ALEPH_RAWSC_MIX_H_

#include "audio.h"

// output amplitude

//! process mix matrix for audio block
extern void mix_process_block(buffer_t *inChannels, buffer_t *outChannels);

// set output amp for oscillator
extern void mix_set_osc_out_amp(int idx, fract32 val);

#endif
