//------------------
//--- a basic oscillator
//--- no modulation

#ifndef _ALEPH_RAWSC_OSC_H_
#define _ALEPH_RAWSC_OSC_H_

#include "types.h"
#include "module_custom.h"

#define NUM_OSCS 4

typedef enum {
  // wavetables
  SHAPE_SINE,
  // non-AA basic shapes
  SHAPE_SAW,
  SHAPE_TRI,
  SHAPE_SQUARE
} osc_shape_t;

// output buffer for each osc
extern fract32 osc_out[NUM_OSCS][MODULE_BLOCKSIZE];

// set shape
extern void osc_set_shape(u16 idx, u32 val);

// set phase directly
extern void osc_set_phase(u16 idx, u32 val);

// set phase increment directly
extern void osc_set_phi(u16 idx, u32 phi);

// set upper 16 bits of phase increment from fract32
extern void osc_set_phi_upper(u16 idx, fract32 val);

// set loewr 16 bits of phase increment from fract32
extern void osc_set_phi_lower(u16 idx, fract32 val);

// set mix point amplitude
extern void osc_set_mix(u16 oscIdx, u16 outIdx, fract32 amp);

// process one block and mix to buffer 
//extern void osc_process_block(fract32* dst, u16 frameCount);
extern void osc_process_block( void );

#endif
