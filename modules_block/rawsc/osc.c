#include <fract.h>
#include <fract_typedef.h>

#include "audio.h"


#include "osc_lookup.h"
#include "osc.h"

//---------------
//--- const data
const fract32 sine_tab[1024] = {
#include "sine_table_inc.c"
};

//---------------
//--- state variables


// FIXME: can we speed access to state vars by restructuring in memory?
static osc_shape_t osc_shape[NUM_OSCS];

__attribute__((aligned(32)))
static u32 osc_phase[NUM_OSCS];

__attribute__((aligned(32)))
static u32 osc_phi[NUM_OSCS];

__attribute__((l1_data_A))
__attribute__((aligned(32)))
fract32 osc_out[NUM_OSCS][MODULE_BLOCKSIZE];


//---------------------
//---- setters
// set shape
void osc_set_shape(u16 idx, u32 val) {
  osc_shape[idx] = (osc_shape_t)val;
}


void osc_set_phase(u16 idx, u32 val) {
  osc_phase[idx] = val;
}

void osc_set_phi(u16 idx, u32 val) {
  osc_phi[idx] = val;
}

void osc_set_phi_upper(u16 idx, fract32 val) {
  u32 phi_ = (osc_phi[idx] & 0x0000ffff) | (val & 0x7fff0000);
  osc_phi[idx] = phi_;
}

void osc_set_phi_lower(u16 idx, fract32 val) {
  u32 phi_ = (osc_phi[idx] & 0x7fff0000) | ((val >> 15) & 0x0000ffff);
  osc_phi[idx] = phi_;
}

void osc_process_block(void) { 
  // tmp variables
  u16 frame;
  u16 osc;
  u32 idxA;
  
  fract32 mulB;
  u32 phase;
  
  for(frame=0; frame<MODULE_BLOCKSIZE; ++frame) {
    for(osc=0; osc<NUM_OSCS; ++osc) {
      
      // update phase, allowing overflow
      phase = osc_phase[osc] + osc_phi[osc];
      OSC_LOOKUP(osc_out[osc][frame], phase, sine_tab, idxA, mulB);
      osc_phase[osc] = phase;
      
    }
  }
}
