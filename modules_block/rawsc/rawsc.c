#include <string.h>

#include "module.h"
#include "osc.h"
#include "mix.h"
#include "mod.h"
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
  int param;
  fract32 v;

  gModuleData = &super;
  strcpy(gModuleData->name, "rawsc");
  gModuleData->paramData = mParamData;
  gModuleData->numParams = eParamNumParams;

  param = PARAM_FREQ_FINE_0;
  v = 0;
  while(param <= PARAM_FREQ_FINE_3) {
    param_setup( param++, v);
    v += 0xf000;
  }

  param = PARAM_FREQ_COARSE_0;
  while(param <= PARAM_FREQ_COARSE_3) {
    param_setup( param++, 0x00962fc9); // ~220hz
  }

  param = PARAM_OSC_DAC_0_0;
  while(param <= PARAM_OSC_DAC_3_3) {  
    param_setup( param++, 0x3fffffff / NUM_OSCS);
  }

  param = PARAM_PHASE_0;
  while(param <= PARAM_PHASE_3) {
    param_setup( param++, 0);
  }

  mod_init();
  
}

void module_process_block(buffer_t *inChannels, buffer_t *outChannels) { 
  osc_process_block();
  mod_process_block();
  mix_process_block(inChannels, outChannels);
}

#include "param_set.c"
