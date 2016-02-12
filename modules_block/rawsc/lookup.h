#ifndef _ALEPH_RAWSC_LOOKUP_H_
#define _ALEPH_RAWSC_LOOKUP_H_

//! shift amount to get index from phase
#define OSC_LOOKUP_IDX_RSHIFT 22

//! shift amount to get multiplier from remainer
#define OSC_LOOKUP_MUL_LSHIFT 9

#define OSC_TAB_SIZE 1024
#define OSC_TAB_MASK (OSC_TAB_SIZE) - 1


/** args:
 * - pointer to output value
 * - phase in [0, 0xffffffff]
 * - table address (array of fract32)
 * - idxA, mulB, temp variables
 */

#define OSC_LOOKUP_IDX_B(tab) (tab)[((idxA) + 1) & (OSC_TAB_MASK)]
			  
#define OSC_LOOKUP_MUL_A(mulB) sub_fr1x32(0x7fffffff, (mulB))

#define OSC_LOOKUP_WAVE_A(tab, idxA, mulB) mult_fr1x32x32(shr_fr1x32((tab)[(idxA)], 1), \
							  OSC_LOOKUP_MUL_A(mulB))

#define OSC_LOOKUP_WAVE_B(tab, mulB) mult_fr1x32x32( shr_fr1x32((tab)[OSC_LOOKUP_IDX_B(tab)], 1), mulB)

#define OSC_LOOKUP(dst, phase, tab, idxA, mulB)				\
  mulB = (fract32)((phase) & 0x3fffffff) << (OSC_LOOKUP_MUL_LSHIFT);	\
  idxA = (phase) >> (OSC_LOOKUP_IDX_RSHIFT);				\
  dst = add_fr1x32( (OSC_LOOKUP_WAVE_A(tab, idxA, mulB)), (OSC_LOOKUP_WAVE_B(tab, mulB)) )

#endif
