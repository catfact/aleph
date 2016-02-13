#include <fract.h>
#include <fract_typedef.h>

#include "mix.h"
#include "osc.h"

static fract32 adc_dac[AUDIO_CHANNELS][AUDIO_CHANNELS];
static fract32 osc_dac[NUM_OSCS][AUDIO_CHANNELS];
static fract32 osc_adc[NUM_OSCS][AUDIO_CHANNELS];
static fract32 osc_osc[NUM_OSCS][NUM_OSCS];

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
  int chan, frame, osc;
  fract32 val;


  for(chan=0; chan<AUDIO_CHANNELS; ++chan) { 
    for(frame=0; frame<MODULE_BLOCKSIZE; ++frame) {

      //--- mix adc to outputs
      // yes, its confusing to use the osc variable, whatever
      for(osc=0; osc<AUDIO_CHANNELS; ++osc) {
	// shift input up from 24b
	val = mult_fr1x32x32( (*inChannels)[chan][frame] << 8,
			      adc_dac[osc][chan] );
      }

      // TODO: amplitude modulation here

      // mix oscs to outputs
      for(osc=0; osc<NUM_OSCS; ++osc) { 
	val = add_fr1x32(val, mult_fr1x32x32( osc_out[osc][frame],
					      osc_dac[osc][chan] ) );
      }

      // shift output down to 24b
      (*outChannels)[chan][frame] = val >> 8;
      
    }
    
  }

  
}
