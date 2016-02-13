#ifndef _ALEPH_RAWSC_OSC_LOOKUP_H_
#define _ALEPH_RAWSC_OSC_LOOKUP_H_


/** args:
 * - pointer to output value
 * - phase in [0, 0xffffffff]
 * - table address (array of fract32)
 * - idxA, mulB, temp variables
 */

#define OSC_LOOKUP_IDX_B(tab) ((idxA) + 1) & 1023
			  
#define OSC_LOOKUP_MUL_A(mulB) sub_fr1x32(0x7fffffff, (mulB))

#define OSC_LOOKUP_WAVE_A(tab, idxA, mulB) mult_fr1x32x32(shr_fr1x32((tab)[(idxA)], 1), \
							  OSC_LOOKUP_MUL_A(mulB))

#define OSC_LOOKUP_WAVE_B(tab, mulB) mult_fr1x32x32( shr_fr1x32((tab)[OSC_LOOKUP_IDX_B(tab)], 1), mulB)

#define OSC_LOOKUP(dst, phase, tab, idxA, mulB)				\
  mulB = (fract32)((phase) & 0x3fffff) << 9;	\
  idxA = (phase) >> 22;				\
  dst = add_fr1x32( (OSC_LOOKUP_WAVE_A(tab, idxA, mulB)), (OSC_LOOKUP_WAVE_B(tab, mulB)) )

#endif
