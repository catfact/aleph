
void module_set_param(u32 idx, ParamValue val) {
    switch(idx) {

    case eParamAmp0:
      osc_set_amp(0, val );
      break;

    case eParamFreqCoarse0:
      osc_set_phi_upper(0, val );
      break;

    case eParamFreqFine0:
      osc_set_phi_lower(0, val );
      break;
      
    case eParamAmp1:
      osc_set_amp(1, val );
      break;

    case eParamFreqCoarse1:
      osc_set_phi_upper(1, val );
      break;

    case eParamFreqFine1:
      osc_set_phi_lower(1, val );
      break;
      
    case eParamAmp2:
      osc_set_amp(2, val );
      break;

    case eParamFreqCoarse2:
      osc_set_phi_upper(2, val );
      break;

    case eParamFreqFine2:
      osc_set_phi_lower(2, val );
      break;

    case eParamAmp3:
      osc_set_amp(3, val );
      break;

    case eParamFreqCoarse3:
      osc_set_phi_upper(3, val );
      break;

    case eParamFreqFine3:
      osc_set_phi_lower(3, val );
      break;

    }

}
