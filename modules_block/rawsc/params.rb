fset = "param_set.c"
fdsc = "params.c"
fh = "params.h"

IO.write(fset, "// this file was autogenerated by params.rb \n\n " +
               "void module_set_param(u32 idx, ParamValue val) { \n"+
               "  switch(idx) { \n" )

IO.write(fdsc, "// this file was autogenerated by params.rb \n\n " +
               "#include <string.h> \n" + 
               "#include \"param_common.h\" \n" + 
               "#include \"params.h\" \n\n" +
               "void fill_param_desc(ParamDesc* desc) {")

IO.write(fh, "// this file was autogenerated by params.rb 
#ifndef _ALEPH_RAWSC_PARAMS_H_
#define _ALEPH_RAWSC_PARAMS_H_

#include \"param_common.h\"

enum params {
")
             

File.foreach("params.txt") { |str|
  print str

  if str == "\n" then
    print "ignoring empty line... \n"
    next
  end

  if str[0] == "#" then
    print "ignoring comment... \n"
    next
  end


  # strip newlines
  str["\n"] = "";

  # determine the category of param
  type = case str
         when /OSC_ADC/ then :osc_adc
         when /OSC_OSC/ then :osc_osc 
         when /ADC_DAC/ then :adc_dac
         when /OSC_DAC/ then :osc_dac
         when /PHASE/ then :phase
         when /SHAPE/ then :shape
         when /FREQ_COARSE/ then :freq_coarse
         when /FREQ_FINE/ then :freq_coarse
         end

  m = str.match(/([0-3])_([0-3])/)
  if m == nil
    m = str.match(/([0-3])/)
  end

  open(fh, 'a') { |f|
    f << "  " + str + ",\n"
  }
  
  open(fset, 'a') { |f|
    f << "  case " + str + " : \n"

    f << case type
         when :adc_dac then
           "    mix_set_adc_dac("+m[1]+", "+m[2]+", val );\n"
         when :osc_dac then
           "    mix_set_osc_dac("+m[1]+", "+m[2]+", val );\n"
         when :osc_adc then
           "    mix_set_osc_adc("+m[1]+", "+m[2]+", val );\n"
         when :osc_osc then
           "    mix_set_osc_osc("+m[1]+", "+m[2]+", val );\n"
         when :freq_coarse then
           "    osc_set_phi_upper("+m[1]+", val);\n"
         when :freq_fine then
           "    osc_set_phi_lower("+m[1]+", val);\n"
         when :phase then
           "    osc_set_phase("+m[1]+", val);\n"
         when :shape then
           "    osc_set_shape("+m[1]+", val);\n"
      end
    
    f << "  break;\n\n"
  }


  label = str.dup
  label[/PARAM_/] = ""
  label = label.downcase

  
  open(fdsc, 'a') { |f|
    f << "strcpy(desc[" + str + "].label, \"" + label + "\");\n"

    case type
    when :adc_dac, :osc_dac, :osc_osc, :osc_adc then
    
      f << "desc[" + str + "].type = eParamTypeAmp;\n"
      f << "desc[" + str + "].min = 0;\n"
      f << "desc[" + str + "].max = 0x7fffffff;\n"
      f << "desc[" + str + "].radix = 16;\n"
      f << "\n\n"

    when :freq_fine, :freq_coarse, :phase then
      f << "desc[" + str + "].type = eParamTypeFix;\n"
      f << "desc[" + str + "].min = 0;\n"
      f << "desc[" + str + "].max = 0x7fffffff;\n"
      f << "desc[" + str + "].radix = 16;\n"
      f << "\n\n"

    # FIXME: not sure what this range should be yet
    when :shape then
      f << "desc[" + str + "].type = eParamTypeFix;\n"
      f << "desc[" + str + "].min = 0;\n"
      f << "desc[" + str + "].max = 0x30000;\n"
      f << "desc[" + str + "].radix = 3;\n"
      f << "\n\n"
    end
  }
  
}

# and don't forget...

open(fset, 'a') { |f|
  f << "  } \n}";
}

open(fdsc, 'a') { |f|
  f << "  }";
}

open(fh, 'a') { |f|
  f << "\n  eParamNumParams \n}; \n \n #endif"
}
