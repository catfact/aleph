// std
#include <string.h>
// asf
#include "delay.h"
#include "print_funcs.h"
// aleph-avr32
#include "app.h"
#include "bfin.h"
#include "control.h"
#include "interrupts.h"
// common
#include "fix.h"
#include "param_common.h"
// lppr
#include "ctl.h"
#include "inputs.h"
#include "render.h"
#include "util.h"

// blah
#define DSP_STRING "aleph-drumsyn"



/*
  FIXME: should use dsyn/inputs.c for conversion
  but for now, use hardcoded initial values only.
  
  formula for slew coefficients: 
  e ^ (-2pi * (hz / sr))

  slew coefficients are stored in fract32
  
  

*/

/* const s32 kParamInitGate0 = 	0x00000000;		 */
/* const s32 kParamInitTrig0 = 	0x00000000;		 */
/* const s32 kParamInitAmp0 = 		0x5a999eb2;		 */
/* const s32 kParamInitAmpAtkSlew0 = 	0x00000000;	 */
/* const s32 kParamInitAmpRelSlew0 = 	0x00000000;	 */
/* const s32 kParamInitFreqAtkSlew0 = 	0x7f14ef3c;	 */
/* const s32 kParamInitFreqRelSlew0 = 	0x00000000;	 */
/* const s32 kParamInitFreqStart0 = 	0x00000000;	 */
/* const s32 kParamInitFreqEnd0 = 	0x00000000;	 */
/* const s32 kParamInitRqAtkSlew0 = 	0x00000000;	 */
/* const s32 kParamInitRqRelSlew0 = 	0x00000000;	 */
/* const s32 kParamInitRqStart0 = 	0x00000000;	 */
/* const s32 kParamInitRqEnd0 = 	0x00000000;	 */
/* const s32 kParamInitLow0 = 		0x00000000;		 */
/* const s32 kParamInitHigh0 = 	0x00000000;		 */
/* const s32 kParamInitBand0 = 	0x00000000;		 */
/* const s32 kParamInitNotch0 = 	0x00000000;	 */

/* //	2640 hz	~= 0.707813107994074	~= 0x5a999eb2 */
/* #define SLEW_ATK_SHORT 	0x5a999eb2 */

/* //	55 hz 	~= 0.9928263710316179	~= 0x7f14ef3c */
/* #define SLEW_ATK_LONG 	0x7f14ef3c */

/* //	2 hz	~= 0.9997382348786702	~= 0x7ff76c26 */
/* #define SLEW_REL_SHORT 	0x7ff76c26 */

/* //	1/2 hz 	~= 0.9999345522948447	~= 0x7ffddafb */
/* //#define SLEW_REL_LONG	0x7ffddafb */
/* #define SLEW_REL_LONG	0x7fffaaaa */



//----------------------------------------
//---- static variables

//-- parameter values
// inputs. use s32 type but unsigned range (accumulators)
s32 dac[4];

/// help!
/* static inline s32 fr32_from_float(float x) { */
/*   if(x > 0.f) { */
/*     return (s32)((double)x * (double)0x7fffffff); */
/*   } else { */
/*     return (s32)((double)(x * -1.f) * (double)0x80000000); */
/*   } */
/* } */


//-------------------------------------
//------ extern functions

// get parameter report from DSP
u8 ctl_report_params(void) {
  volatile char buf[64];
  volatile ParamDesc pdesc;
  u32 numParams;
  u8 i;
 
  bfin_get_num_params(&numParams);
  print_dbg("\r\nnumparams: ");
  print_dbg_ulong(numParams);

  if(numParams == 255) {
    print_dbg("\r\n report_params fail (too many)");
    return 0;
  }

  if(numParams > 0) {
    for(i=0; i<numParams; i++) {
      bfin_get_param_desc(i, &pdesc);
      
      print_dbg("\r\n got pdesc : ");
      print_dbg((const char* )pdesc.label);
    }
  } else {
    print_dbg("\r\n report_params fail (none)");
    return 0;
  }
  
  delay_ms(100);

  print_dbg("\r\n checking module label ");
  // check module label
  bfin_get_module_name(buf);

  delay_ms(10);

  print_dbg("\r\n bfin module name: ");
  print_dbg((const char*)buf);
  if(strcmp((const char*)buf, DSP_STRING)) {
    print_dbg( "\r\n report_params fail (module name mismatch)" );
    return 0;
  } else {
    return 1;
  }
}

// set initial parameters
void ctl_init_params(void) {

  //---- voice 0
  ctl_param_change( eParamVoice, 	0 );
  ctl_param_change( eParamGate,	0	);
  ctl_param_change( eParamTrig,	0	);

  ctl_param_change( eParamAmp,		FR32_MAX >> 1	);
  ctl_param_change( eParamAmpSus,     	FR32_MAX >> 1	);
  ctl_param_change( eParamAmpAtkSlew,	sec_to_slew(0.001)	);
  ctl_param_change( eParamAmpDecSlew,	sec_to_slew(2.0)	);
  ctl_param_change( eParamAmpRelSlew,	sec_to_slew(4.0)	);

  ctl_param_change( eParamFreqAtkSlew,	sec_to_slew(0.004)	);
  ctl_param_change( eParamFreqDecSlew,	sec_to_slew(1.0)	);
  ctl_param_change( eParamFreqRelSlew,	sec_to_slew(1.0)	);
  ctl_param_change( eParamFreqOff,	hz_to_svf(27.5)	);
  ctl_param_change( eParamFreqOn,	hz_to_svf(220.0)	);
  ctl_param_change( eParamFreqSus,	hz_to_svf(110.0)	);
    
  ctl_param_change( eParamRqAtkSlew,	sec_to_slew(0.0002)	);
  ctl_param_change( eParamRqDecSlew,	sec_to_slew(0.5)	);
  ctl_param_change( eParamRqRelSlew,	sec_to_slew(0.1)	);
  ctl_param_change( eParamRqOff,	float_to_fr32(0.08)	);
  ctl_param_change( eParamRqOn,	float_to_fr32(0.3)	);
  ctl_param_change( eParamRqSus,	float_to_fr32(0.1)	);

  ctl_param_change( eParamLow,		float_to_fr32(0.9)	);
  ctl_param_change( eParamHigh,	0	);
  ctl_param_change( eParamBand,	0	);
  ctl_param_change( eParamNotch,	0	);

  //---- voice 1
  ctl_param_change( eParamVoice, 	1 );
  ctl_param_change( eParamGate,	0	);
  ctl_param_change( eParamTrig,	0	);

  ctl_param_change( eParamAmp,		FR32_MAX >> 1	);
  ctl_param_change( eParamAmpSus,     	FR32_MAX >> 1	);
  ctl_param_change( eParamAmpAtkSlew,	sec_to_slew(0.001)	);
  ctl_param_change( eParamAmpDecSlew,	sec_to_slew(2.0)	);
  ctl_param_change( eParamAmpRelSlew,	sec_to_slew(4.0)	);

  ctl_param_change( eParamFreqAtkSlew,	sec_to_slew(0.004)	);
  ctl_param_change( eParamFreqDecSlew,	sec_to_slew(1.0)	);
  ctl_param_change( eParamFreqRelSlew,	sec_to_slew(1.0)	);
  ctl_param_change( eParamFreqOff,	hz_to_svf(27.5)	);
  ctl_param_change( eParamFreqOn,	hz_to_svf(220.0)	);
  ctl_param_change( eParamFreqSus,	hz_to_svf(110.0)	);
    
  ctl_param_change( eParamRqAtkSlew,	sec_to_slew(0.0002)	);
  ctl_param_change( eParamRqDecSlew,	sec_to_slew(0.5)	);
  ctl_param_change( eParamRqRelSlew,	sec_to_slew(0.1)	);
  ctl_param_change( eParamRqOff,	float_to_fr32(0.08)	);
  ctl_param_change( eParamRqOn,	float_to_fr32(0.3)	);
  ctl_param_change( eParamRqSus,	float_to_fr32(0.1)	);

  ctl_param_change( eParamLow,		float_to_fr32(0.9)	);
  ctl_param_change( eParamHigh,	0	);
  ctl_param_change( eParamBand,	0	);
  ctl_param_change( eParamNotch,	0	);

  //---- voice 2
  ctl_param_change( eParamVoice, 	2 );
  ctl_param_change( eParamGate,	0	);
  ctl_param_change( eParamTrig,	0	);

  ctl_param_change( eParamAmp,		FR32_MAX >> 1	);
  ctl_param_change( eParamAmpSus,     	FR32_MAX >> 1	);
  ctl_param_change( eParamAmpAtkSlew,	sec_to_slew(0.001)	);
  ctl_param_change( eParamAmpDecSlew,	sec_to_slew(2.0)	);
  ctl_param_change( eParamAmpRelSlew,	sec_to_slew(4.0)	);

  ctl_param_change( eParamFreqAtkSlew,	sec_to_slew(0.004)	);
  ctl_param_change( eParamFreqDecSlew,	sec_to_slew(1.0)	);
  ctl_param_change( eParamFreqRelSlew,	sec_to_slew(1.0)	);
  ctl_param_change( eParamFreqOff,	hz_to_svf(27.5)	);
  ctl_param_change( eParamFreqOn,	hz_to_svf(220.0)	);
  ctl_param_change( eParamFreqSus,	hz_to_svf(110.0)	);
    
  ctl_param_change( eParamRqAtkSlew,	sec_to_slew(0.0002)	);
  ctl_param_change( eParamRqDecSlew,	sec_to_slew(0.5)	);
  ctl_param_change( eParamRqRelSlew,	sec_to_slew(0.1)	);
  ctl_param_change( eParamRqOff,	float_to_fr32(0.08)	);
  ctl_param_change( eParamRqOn,	float_to_fr32(0.3)	);
  ctl_param_change( eParamRqSus,	float_to_fr32(0.1)	);

  ctl_param_change( eParamLow,		float_to_fr32(0.9)	);
  ctl_param_change( eParamHigh,	0	);
  ctl_param_change( eParamBand,	0	);
  ctl_param_change( eParamNotch,	0	);

  //---- voice 3
  ctl_param_change( eParamVoice, 	3 );
  ctl_param_change( eParamGate,	0	);
  ctl_param_change( eParamTrig,	0	);

  ctl_param_change( eParamAmp,		FR32_MAX >> 1	);
  ctl_param_change( eParamAmpSus,     	FR32_MAX >> 1	);
  ctl_param_change( eParamAmpAtkSlew,	sec_to_slew(0.001)	);
  ctl_param_change( eParamAmpDecSlew,	sec_to_slew(2.0)	);
  ctl_param_change( eParamAmpRelSlew,	sec_to_slew(4.0)	);

  ctl_param_change( eParamFreqAtkSlew,	sec_to_slew(0.004)	);
  ctl_param_change( eParamFreqDecSlew,	sec_to_slew(1.0)	);
  ctl_param_change( eParamFreqRelSlew,	sec_to_slew(1.0)	);
  ctl_param_change( eParamFreqOff,	hz_to_svf(27.5)	);
  ctl_param_change( eParamFreqOn,	hz_to_svf(220.0)	);
  ctl_param_change( eParamFreqSus,	hz_to_svf(110.0)	);
    
  ctl_param_change( eParamRqAtkSlew,	sec_to_slew(0.0002)	);
  ctl_param_change( eParamRqDecSlew,	sec_to_slew(0.5)	);
  ctl_param_change( eParamRqRelSlew,	sec_to_slew(0.1)	);
  ctl_param_change( eParamRqOff,	float_to_fr32(0.08)	);
  ctl_param_change( eParamRqOn,	float_to_fr32(0.3)	);
  ctl_param_change( eParamRqSus,	float_to_fr32(0.1)	);

  ctl_param_change( eParamLow,		float_to_fr32(0.9)	);
  ctl_param_change( eParamHigh,	0	);
  ctl_param_change( eParamBand,	0	);
  ctl_param_change( eParamNotch,	0	);
		
}

// set gate
void  ctl_set_gate(u8 ch, u8 val) {
  //  static const eParam gateParams[4] = { eParamGate0 , eParamGate1, eParamGate2, eParamGate3  };
  //  static const eParam gateParams[4] = { eParamGate0 , eParamGate0, eParamGate0, eParamGate0  };
  //  eParam p = gateParams[ch];
  //  ctl_param_change(p, (s32)val );
  ctl_param_change(eParamVoice, ch );
  ctl_param_change(eParamGate, (s32)val );
}
