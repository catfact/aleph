#include <fract.h>
#include <fract_typedef.h>

#include "mix.h"
#include "osc.h"

static fract32 osc_out_amp[NUM_OSCS];

void mix_set_osc_out_amp(int idx, fract32 val) {
  osc_out_amp[idx] = val;
}

void mix_process_block(buffer_t *inChannels, buffer_t *outChannels) {

  // for now, just copy ins to outs, and all oscs to all outs.
  // TODO: use mix matrix

  int chan, frame, osc;
  fract32 val;
  
  for(chan=0; chan<AUDIO_CHANNELS; ++chan) { 
    for(frame=0; frame<MODULE_BLOCKSIZE; ++frame) {

      val = (*inChannels)[chan][frame];
      
      for(osc=0; osc<NUM_OSCS; ++osc) { 
	val = add_fr1x32(val, mult_fr1x32x32( osc_out[osc][frame],
					      osc_out_amp[osc] ) );
      }

      // shift down to 24b for output
      (*outChannels)[chan][frame] = val >> 8;
      
    }
    
  }
  
}
