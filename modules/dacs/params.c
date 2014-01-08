// autogenerated from param_gen.scd 
 

#include <string.h>
#include "module.h"
#include "params.h" 

void fill_param_desc(void) {
  strcpy(gModuleData->paramDesc[eParam_dac0].label, "dac0");
  gModuleData->paramDesc[eParam_dac0].type = eParamTypeFix; 
  gModuleData->paramDesc[eParam_dac0].min = 0x00000000; 
  gModuleData->paramDesc[eParam_dac0].max = PARAM_DAC_MAX;
  gModuleData->paramDesc[eParam_dac0].radix = PARAM_DAC_RADIX;

  strcpy(gModuleData->paramDesc[eParam_dac1].label, "dac1");
  gModuleData->paramDesc[eParam_dac1].type = eParamTypeFix; 
  gModuleData->paramDesc[eParam_dac1].min = 0x00000000; 
  gModuleData->paramDesc[eParam_dac1].max = PARAM_DAC_MAX;
  gModuleData->paramDesc[eParam_dac1].radix = PARAM_DAC_RADIX;

  strcpy(gModuleData->paramDesc[eParam_dac2].label, "dac2");
  gModuleData->paramDesc[eParam_dac2].type = eParamTypeFix; 
  gModuleData->paramDesc[eParam_dac2].min = 0x00000000; 
  gModuleData->paramDesc[eParam_dac2].max = PARAM_DAC_MAX;
  gModuleData->paramDesc[eParam_dac2].radix = PARAM_DAC_RADIX;

  strcpy(gModuleData->paramDesc[eParam_dac3].label, "dac3");
  gModuleData->paramDesc[eParam_dac3].type = eParamTypeFix; 
  gModuleData->paramDesc[eParam_dac3].min = 0x00000000; 
  gModuleData->paramDesc[eParam_dac3].max = PARAM_DAC_MAX;
  gModuleData->paramDesc[eParam_dac3].radix = PARAM_DAC_RADIX;

  strcpy(gModuleData->paramDesc[eParam_slew0].label, "slew0");
  gModuleData->paramDesc[eParam_slew0].type = eParamTypeIntegrator; 
  gModuleData->paramDesc[eParam_slew0].min = 0x00000000; 
  gModuleData->paramDesc[eParam_slew0].max = 0x7fffffff;
  gModuleData->paramDesc[eParam_slew0].radix = 32;

  strcpy(gModuleData->paramDesc[eParam_slew1].label, "slew1");
  gModuleData->paramDesc[eParam_slew1].type = eParamTypeIntegrator; 
  gModuleData->paramDesc[eParam_slew1].min = 0x00000000; 
  gModuleData->paramDesc[eParam_slew1].max = 0x7fffffff;
  gModuleData->paramDesc[eParam_slew1].radix = 32;

  strcpy(gModuleData->paramDesc[eParam_slew2].label, "slew2");
  gModuleData->paramDesc[eParam_slew2].type = eParamTypeIntegrator; 
  gModuleData->paramDesc[eParam_slew2].min = 0x00000000; 
  gModuleData->paramDesc[eParam_slew2].max = 0x7fffffff; 
  gModuleData->paramDesc[eParam_slew2].radix = 32;

  strcpy(gModuleData->paramDesc[eParam_slew3].label, "slew3");
  gModuleData->paramDesc[eParam_slew3].type = eParamTypeIntegrator; 
  gModuleData->paramDesc[eParam_slew3].min = 0x00000000; 
  gModuleData->paramDesc[eParam_slew3].max = 0x7fffffff;
  gModuleData->paramDesc[eParam_slew3].radix = 32;
}

// EOF
