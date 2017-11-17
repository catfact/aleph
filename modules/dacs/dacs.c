/* dacs.c
   aleph-bfin

   simplest CV output module.
*/

// std
#include <math.h>
// (testing)
#include <stdlib.h>
#include <string.h>

// aleph-common
#include "fix.h"
#include "types.h"

// aleph-bfin
#include "bfin_core.h"
#include "cv.h"
#include "gpio.h"
#include "fract_math.h"

// audio
#include "filter_1p.h"
#include "module.h"

/// custom
#include "params.h"

#define TEST_BYPASS_SLEW 1

// data structure of external memory
typedef struct _dacsData {
  ModuleData super;
  ParamData mParamData[eParamNumParams];
} dacsData;

//-------------------------
//----- extern vars (initialized here)
ModuleData* gModuleData;

//-----------------------
//------ static variables

// pointer to all external memory
dacsData* pDacsData;

// dac values (u16, but use fract32 and audio integrators)
static fract32 cvVal[4];
static filter_1p_lo cvSlew[4];
static u8 cvChan = 0;

//----------------------
//----- external functions

static inline void param_setup(u32 id, ParamValue v) ;
static inline void param_setup(u32 id, ParamValue v) {
  gModuleData->paramData[id].value = v;
  module_set_param(id, v);
}

void module_init(void) {
  // init module/param descriptor
  pDacsData = (dacsData*)SDRAM_ADDRESS;

  gModuleData = &(pDacsData->super);
  strcpy(gModuleData->name, "dacs");

  gModuleData->paramData = (ParamData*)pDacsData->mParamData;
  gModuleData->numParams = eParamNumParams;

  filter_1p_lo_init( &(cvSlew[0]), 0 );
  filter_1p_lo_init( &(cvSlew[1]), 0 );
  filter_1p_lo_init( &(cvSlew[2]), 0 );
  filter_1p_lo_init( &(cvSlew[3]), 0 );

  param_setup( eParam_cvSlew0, PARAM_CV_SLEW_DEFAULT );
  param_setup( eParam_cvSlew1, PARAM_CV_SLEW_DEFAULT );
  param_setup( eParam_cvSlew2, PARAM_CV_SLEW_DEFAULT );
  param_setup( eParam_cvSlew3, PARAM_CV_SLEW_DEFAULT );

  param_setup( eParam_cvVal0, PARAM_CV_VAL_DEFAULT );
  param_setup( eParam_cvVal1, PARAM_CV_VAL_DEFAULT );
  param_setup( eParam_cvVal2, PARAM_CV_VAL_DEFAULT );
  param_setup( eParam_cvVal3, PARAM_CV_VAL_DEFAULT );
}

// de-init
void module_deinit(void) {
}

// get number of parameters
u32 module_get_num_params(void) {
  return eParamNumParams;
}

//// FIXME:
/* for now, stagger DAC channels across consecutive audio frames
   better method might be:
   - enable DMA tx interrupt
   - each ISR calls the next channel to be loaded
   - last thing audio ISR does is call the first DAC channel to be loaded
   - dac_update writes to 4x16 volatile buffer
*/
static fract32 sawVal[4] = { 0, 0, 0, 0 };

void module_process_frame(void) {

#if TEST_BYPASS_SLEW
  // try skipping CV update altogether on alternate frames...
  //  static u8 skipCvFrame = 0;

  //  update_saw(2);
  
  //cv_update(cvChan, cvVal[cvChan]);
  cv_update(cvChan, (fract32)sawVal[cvChan]);
  sawVal[cvChan] += ((0xffffffff / 480000) * (cvChan + 11));
  
  if(++cvChan == 4) {
	  cvChan = 0;
  }
  
  //  if(++skipCvFrame == 4) { skipCvFrame = 0; }
  
  //  }
#else
  // Update one of the CV outputs with slew
  if(filter_1p_sync(&(cvSlew[cvChan]))) { ;; } else {
    cvVal[cvChan] = filter_1p_lo_next(&(cvSlew[cvChan]));
    cv_update(cvChan, cvVal[cvChan]);
  }
  if(++cvChan == 4) {
	cvChan = 0;
  }
#endif


}

// parameter set function
void module_set_param(u32 idx, ParamValue v) {
  switch(idx) {

#if TEST_BYPASS_SLEW
  case eParam_cvVal0 :
	cvVal[0] = v;
    break;
  case eParam_cvVal1 :
	cvVal[1] = v;
    break;
  case eParam_cvVal2 :
	cvVal[2] = v;
    break;
  case eParam_cvVal3 :
	cvVal[3] = v;
    break;
	#else
	
  case eParam_cvVal0 :
    filter_1p_lo_in(&(cvSlew[0]), v);
    break;
  case eParam_cvVal1 :
    filter_1p_lo_in(&(cvSlew[1]), v);
    break;
  case eParam_cvVal2 :
    filter_1p_lo_in(&(cvSlew[2]), v);
    break;
  case eParam_cvVal3 :
    filter_1p_lo_in(&(cvSlew[3]), v);
    break;
	#endif

  case eParam_cvSlew0 :
    filter_1p_lo_set_slew(&(cvSlew[0]), v);
    break;
  case eParam_cvSlew1 :
    filter_1p_lo_set_slew(&(cvSlew[1]), v);
    break;
  case eParam_cvSlew2 :
    filter_1p_lo_set_slew(&(cvSlew[2]), v);
    break;
  case eParam_cvSlew3 :
    filter_1p_lo_set_slew(&(cvSlew[3]), v);
    break;
  default:
    break;
  }
}
