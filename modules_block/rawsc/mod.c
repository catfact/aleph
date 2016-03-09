#include "fract_math.h"
#include "interpolate.h"

#include "osc.h"
#include "mod.h"

// dummy modulation target block
static fract32 mod_dum[MODULE_BLOCKSIZE];

// pointers to amp modulation targets 
static fract32* adc_mod_dst[NUM_OSCS];
static fract32* osc_mod_dst[NUM_OSCS];

// amp modulation amounts
static fract32 adc_mod_amt[NUM_OSCS];
static fract32 osc_mod_amt[NUM_OSCS];

// carrier suppression coefficients
static fract32 adc_mod_sub[NUM_OSCS];
static fract32 osc_mod_sub[NUM_OSCS];


static inline void perform_mod(fract32 src, fract32* dst,
			       fract32 amt, fract32 sub) {
  *dst = sub_fr1x32( dsp_lerp32(*dst, mult_fr1x32x32(*dst, src), amt),
		     mult_fr1x32x32(*dst, sub) );
}

void mod_init(void) {
  int i;
  for(i=0; i<NUM_OSCS; i++) {
    adc_mod_dst[i] = &(mod_dum[0]);
    osc_mod_dst[i] = &(mod_dum[0]);
  }
}


void mod_process_block(void) {
  int voice, frame;
  
  fract32* adc_dst;
  fract32* osc_dst;
  
  // process AM targets for each voice
  for(voice=0; voice<NUM_OSCS; ++voice) {
    adc_dst = adc_mod_dst[voice];
    osc_dst = osc_mod_dst[voice];
    
    for(frame=0; frame<MODULE_BLOCKSIZE; ++frame) {
      
      perform_mod(osc_out[voice][frame],
		  adc_dst++,
		  adc_mod_amt[voice],
		  adc_mod_sub[voice] );
      
      perform_mod(osc_out[voice][frame],
		  osc_dst++,
		  osc_mod_amt[voice],
		  osc_mod_sub[voice] );
      
    }
  }

  
}


