#include <fract.h>
#include <fract_typedef.h>

#include "mix.h"
#include "osc.h"

// output amp (before mix)
static fract32 osc_amp[NUM_OSCS];

// output mix
static fract32 adc_dac[AUDIO_CHANNELS][AUDIO_CHANNELS];
static fract32 osc_dac[NUM_OSCS][AUDIO_CHANNELS];
// modulation
static fract32 osc_adc[NUM_OSCS][AUDIO_CHANNELS];
static fract32 osc_osc[NUM_OSCS][NUM_OSCS];

// set osc output amp, before matrix
 void mix_set_osc_amp(int osc, fract32 val) {
   osc_amp[osc] = val;
}


void mix_set_adc_dac(int i, int o, fract32 val) {
  adc_dac[i][o] = val;
}

void mix_set_osc_dac(int i, int o, fract32 val) {
  osc_dac[i][o] = val;
}

void mix_set_osc_adc(int i, int o, fract32 val) {
  osc_adc[i][o] = val;
}

void mix_set_osc_osc(int i, int o, fract32 val) {
  osc_osc[i][o] = val;
}

void mix_process_block(buffer_t *inChannels, buffer_t *outChannels) {
  int chan, frame, voice;
  fract32 val, mul;

  for(chan=0; chan<AUDIO_CHANNELS; ++chan) { 
    for(frame=0; frame<MODULE_BLOCKSIZE; ++frame) {
      val = 0;
      
      //--- mix adc to outputs
      for(voice=0; voice<AUDIO_CHANNELS; ++voice) {
	// shift input up from 24b
	val = add_fr1x32(val, mult_fr1x32x32( (*inChannels)[chan][frame] << 8,
					      adc_dac[voice][chan] ));
      }

      // TODO: amplitude modulation here

      // mix oscs to outputs
      for(voice=0; voice<NUM_OSCS; ++voice) {
	mul = mult_fr1x32x32(osc_dac[voice][chan], osc_amp[voice]);
	val = add_fr1x32(val, mult_fr1x32x32( mul, osc_out[voice][frame] ) );
      }

      // shift output down to 24b
      (*outChannels)[chan][frame] = val >> 8;
      
    }
    
  }

  
}
