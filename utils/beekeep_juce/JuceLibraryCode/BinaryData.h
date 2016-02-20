/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_113910788_INCLUDED
#define BINARYDATA_H_113910788_INCLUDED

namespace BinaryData
{
    extern const char*   libfixmath_cbp;
    const int            libfixmath_cbpSize = 1886;

    extern const char*   license_txt;
    const int            license_txtSize = 1261;

    extern const char*   Makefile;
    const int            MakefileSize = 995;

    extern const char*   avr32_sim_mk;
    const int            avr32_sim_mkSize = 708;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 4;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
