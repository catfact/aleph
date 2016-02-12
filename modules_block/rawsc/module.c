#include <string.h>

#include "module.h"
#include "osc.h"
#include "params.h"

ModuleData* gModuleData;
volatile u8 isModuleInit = 0;

static ModuleData super;
static ParamData mParamData[eParamNumParams];

static inline void param_setup(u32 id, ParamValue v) {
  gModuleData->paramData[id].value = v;
  module_set_param(id, v);
}

void module_init(void) {
  u16 i;

  gModuleData = &super;
  strcpy(gModuleData->name, "rawsc");
  gModuleData->paramData = mParamData;
  gModuleData->numParams = eParamNumParams;

  // detune!
  param_setup( eParamFreqFine0, 0x00000000);
  param_setup( eParamFreqFine1, 0x000f0000);
  param_setup( eParamFreqFine2, 0x00ff0000);
  param_setup( eParamFreqFine3, 0x7fff0000);

  // ~220hz
  param_setup( eParamFreqCoarse0, 0x00962fc9); 
  param_setup( eParamFreqCoarse1, 0x00962fc9); 
  param_setup( eParamFreqCoarse2, 0x00962fc9); 
  param_setup( eParamFreqCoarse3, 0x00962fc9); 
  
  param_setup( eParamAmp0, 0x3fffffff / NUM_OSCS);
  param_setup( eParamAmp1, 0x3fffffff / NUM_OSCS);
  param_setup( eParamAmp2, 0x3fffffff / NUM_OSCS);
  param_setup( eParamAmp3, 0x3fffffff / NUM_OSCS);

  for(i=0; i<NUM_OSCS; i++) { 
    osc_set_phase(i, 0);
  }
}

void module_process_block(buffer_t *inChannels, buffer_t *outChannels) { 
  u16 i, j;
  
  for(i=0; i<AUDIO_CHANNELS; i++) {
    for(j=0; j<MODULE_BLOCKSIZE; j++) {
      (*outChannels)[i][j] = (*inChannels)[i][j];
    }
  }

  for(i=0; i<NUM_OSCS; i++) { 
    osc_process_block(i);
  }

}

#include "param_set.c"
