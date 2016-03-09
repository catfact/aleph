/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== libfixmath.cbp ==================
static const unsigned char temp_binary_data_0[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n"
"<CodeBlocks_project_file>\n"
"\t<FileVersion major=\"1\" minor=\"6\" />\n"
"\t<Project>\n"
"\t\t<Option title=\"libfixmath\" />\n"
"\t\t<Option pch_mode=\"2\" />\n"
"\t\t<Option compiler=\"gcc\" />\n"
"\t\t<Build>\n"
"\t\t\t<Target title=\"dbg\">\n"
"\t\t\t\t<Option output=\"libfixmath\" prefix_auto=\"1\" extension_auto=\"1\" />\n"
"\t\t\t\t<Option working_dir=\"\" />\n"
"\t\t\t\t<Option object_output=\"obj\\dbg\\\" />\n"
"\t\t\t\t<Option type=\"2\" />\n"
"\t\t\t\t<Option compiler=\"gcc\" />\n"
"\t\t\t\t<Option createDefFile=\"1\" />\n"
"\t\t\t\t<Compiler>\n"
"\t\t\t\t\t<Add option=\"-Wall\" />\n"
"\t\t\t\t\t<Add option=\"-g\" />\n"
"\t\t\t\t</Compiler>\n"
"\t\t\t</Target>\n"
"\t\t\t<Target title=\"rel\">\n"
"\t\t\t\t<Option output=\"libfixmath\" prefix_auto=\"1\" extension_auto=\"1\" />\n"
"\t\t\t\t<Option working_dir=\"\" />\n"
"\t\t\t\t<Option object_output=\"obj\\rel\\\" />\n"
"\t\t\t\t<Option type=\"2\" />\n"
"\t\t\t\t<Option compiler=\"gcc\" />\n"
"\t\t\t\t<Option createDefFile=\"1\" />\n"
"\t\t\t\t<Compiler>\n"
"\t\t\t\t\t<Add option=\"-fomit-frame-pointer\" />\n"
"\t\t\t\t\t<Add option=\"-fexpensive-optimizations\" />\n"
"\t\t\t\t\t<Add option=\"-O3\" />\n"
"\t\t\t\t\t<Add option=\"-Wall\" />\n"
"\t\t\t\t</Compiler>\n"
"\t\t\t\t<Linker>\n"
"\t\t\t\t\t<Add option=\"-s\" />\n"
"\t\t\t\t</Linker>\n"
"\t\t\t</Target>\n"
"\t\t</Build>\n"
"\t\t<Unit filename=\"Makefile\" />\n"
"\t\t<Unit filename=\"fix16.c\">\n"
"\t\t\t<Option compilerVar=\"CC\" />\n"
"\t\t</Unit>\n"
"\t\t<Unit filename=\"fix16.h\" />\n"
"\t\t<Unit filename=\"fix16.hpp\" />\n"
"\t\t<Unit filename=\"fix16_exp.c\">\n"
"\t\t\t<Option compilerVar=\"CC\" />\n"
"\t\t</Unit>\n"
"\t\t<Unit filename=\"fix16_sqrt.c\">\n"
"\t\t\t<Option compilerVar=\"CC\" />\n"
"\t\t</Unit>\n"
"\t\t<Unit filename=\"fix16_trig.c\">\n"
"\t\t\t<Option compilerVar=\"CC\" />\n"
"\t\t</Unit>\n"
"\t\t<Unit filename=\"fixmath.h\" />\n"
"\t\t<Unit filename=\"fract32.c\">\n"
"\t\t\t<Option compilerVar=\"CC\" />\n"
"\t\t</Unit>\n"
"\t\t<Unit filename=\"fract32.h\" />\n"
"\t\t<Unit filename=\"int64.h\" />\n"
"\t\t<Unit filename=\"uint32.c\">\n"
"\t\t\t<Option compilerVar=\"CC\" />\n"
"\t\t</Unit>\n"
"\t\t<Unit filename=\"uint32.h\" />\n"
"\t\t<Extensions>\n"
"\t\t\t<code_completion />\n"
"\t\t\t<envvars />\n"
"\t\t\t<debugger />\n"
"\t\t\t<lib_finder disable_auto=\"1\" />\n"
"\t\t</Extensions>\n"
"\t</Project>\n"
"</CodeBlocks_project_file>\n";

const char* libfixmath_cbp = (const char*) temp_binary_data_0;

//================== license.txt ==================
static const unsigned char temp_binary_data_1[] =
"libfixmath didnt come with a license file but website says MIT. so here is that:\n"
"\n"
"[OSI Approved License]\n"
"\n"
"The MIT License (MIT)\n"
"\n"
"Copyright (c) <year> <copyright holders>\n"
"\n"
"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
"of this software and associated documentation files (the \"Software\"), to deal\n"
"in the Software without restriction, including without limitation the rights\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
"copies of the Software, and to permit persons to whom the Software is\n"
"furnished to do so, subject to the following conditions:\n"
"\n"
"The above copyright notice and this permission notice shall be included in\n"
"all copies or substantial portions of the Software.\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\n"
"THE SOFTWARE.\n"
"\n"
"\n"
"libfixmath was found here:\n"
"https://code.google.com/p/libfixmath/\n";

const char* license_txt = (const char*) temp_binary_data_1;

//================== Makefile ==================
static const unsigned char temp_binary_data_2[] =
"#Project settings\r\n"
"PROJECT = libfixmath\r\n"
"LIB =\r\n"
"SRC = .\r\n"
"INC =\r\n"
"\r\n"
"#Compiler settings\r\n"
"CPP = gcc\r\n"
"CC = gcc\r\n"
"AS = gcc\r\n"
"LD = gcc\r\n"
"AR = ar\r\n"
"CPP_FLAGS = -O2 $(INC) -Wall -Wextra -c\r\n"
"CC_FLAGS  = -O2 $(INC) -Wall -Wextra -c\r\n"
"AS_FLAGS  = $(CC_FLAGS) -D_ASSEMBLER_\r\n"
"LD_FLAGS = -Wall\r\n"
"\r\n"
"# Find all source files\r\n"
"SRC_CPP = $(foreach dir, $(SRC), $(wildcard $(dir)/*.cpp))\r\n"
"SRC_C   = $(foreach dir, $(SRC), $(wildcard $(dir)/*.c))\r\n"
"SRC_S   = $(foreach dir, $(SRC), $(wildcard $(dir)/*.S))\r\n"
"OBJ_CPP = $(patsubst %.cpp, %.o, $(SRC_CPP))\r\n"
"OBJ_C   = $(patsubst %.c, %.o, $(SRC_C))\r\n"
"OBJ_S   = $(patsubst %.S, %.o, $(SRC_S))\r\n"
"OBJ     = $(OBJ_CPP) $(OBJ_C) $(OBJ_S)\r\n"
"\r\n"
"# Compile rules.\r\n"
".PHONY : all\r\n"
"all: $(PROJECT).a\r\n"
"\r\n"
"$(PROJECT).a: $(OBJ)\r\n"
"\t$(AR) rcs $(PROJECT).a $(OBJ)\r\n"
"\r\n"
"$(OBJ_CPP) : %.o : %.cpp\r\n"
"\t$(CPP) $(CPP_FLAGS) -o $@ $<\r\n"
"\r\n"
"$(OBJ_C) : %.o : %.c\r\n"
"\t$(CC) $(CC_FLAGS) -o $@ $<\r\n"
"\r\n"
"$(OBJ_S) : %.o : %.S\r\n"
"\t$(AS) $(AS_FLAGS) -o $@ $<\r\n"
"\r\n"
"\r\n"
"\r\n"
"# Clean rules\r\n"
".PHONY : clean\r\n"
"clean:\r\n"
"\trm -f $(PROJECT).a $(OBJ)\r\n";

const char* Makefile = (const char*) temp_binary_data_2;

//================== avr32_sim.mk ==================
static const unsigned char temp_binary_data_3[] =
"\n"
"src += \\\n"
"\t$(sim)/src/adc.c \\\n"
"\t$(sim)/src/app.c \\\n"
"\t$(sim)/src/bfin.c \\\n"
"\t$(sim)/src/control.c \\\n"
"\t$(sim)/src/delay.c \\\n"
"\t$(sim)/src/events.c \\\n"
"\t$(sim)/src/encoders.c \\\n"
"\t$(sim)/src/filesystem.c \\\n"
"\t$(sim)/src/flash.c \\\n"
"\t$(sim)/src/font.c \\\n"
"\t$(sim)/src/i2c.c \\\n"
"\t$(sim)/src/init.c\t\\\n"
"\t$(sim)/src/interrupts.c \\\n"
"\t$(sim)/src/main.c \\\n"
"\t$(sim)/src/memory.c \\\n"
"\t$(sim)/src/monome.c\\\n"
"\t$(sim)/src/print_funcs.c \\\n"
"\t$(sim)/src/region.c \\\n"
"\t$(sim)/src/screen.c \\\n"
"\t$(sim)/src/serial.c \\\n"
"\t$(sim)/src/simple_string.c \\\n"
"\t$(sim)/src/switches.c \\\n"
"\t$(sim)/src/timers.c \\\n"
"\t$(sim)/src/usb.c \\\n"
"\t$(sim)/src/usb/midi/midi.c \\\n"
"\t$(sim)/src/usb/ftdi/ftdi.c \\\n"
"\t$(sim)/src/fonts/ume_tgo5_18.c \\\n"
"\t$(sim)/src/fix.c \\\n"
"\t$(sim)/src/libfixmath/fix16.c";

const char* avr32_sim_mk = (const char*) temp_binary_data_3;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x2697a1aa:  numBytes = 1886; return libfixmath_cbp;
        case 0xd9cf6d72:  numBytes = 1261; return license_txt;
        case 0x064cb88a:  numBytes = 995; return Makefile;
        case 0x93b33da9:  numBytes = 708; return avr32_sim_mk;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "libfixmath_cbp",
    "license_txt",
    "Makefile",
    "avr32_sim_mk"
};

}
