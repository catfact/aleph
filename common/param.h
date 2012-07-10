
/* param.h
 * aleph-common
 * 
 * common parameter data types
 */

#ifndef _ALEPH_COMMON_PARAM_H_
#define _ALEPH_COMMON_PARAM_H_

#include "types.h"

////////
/////// WARNING:
// because of stupid hack reasons,
// any changes here must be reflected
// in the bytecount #defines in protocol.h

// max characters in param name
#define PARAM_LABEL_LEN 16
// max charactes in param unit
#define PARAM_UNIT_LEN 8
// TODO: define units?

//-------- param types
#define PARAM_TYPE_FLOAT 0
#define PARAM_TYPE_FRACT 1
#define PARAM_TYPE_UINT  2

// 4-byte union of value representations
typedef union {
  f32 asFloat;
  fract32 asFract;
  u32 asUint;
  u8 asByte[4];
  u16 asShort[2];
} ParamValue;

// parameter descriptor
typedef struct __attribute__((__packed__)) ParamDescStruct {
  // parameter name
  char name[PARAM_LABEL_LEN];
  // parameter unit name
  char unit[PARAM_UNIT_LEN];
  // type: fract, int, or float
  u8 type;
  // range
  f32 min;
  f32 max;
  // other stuff: range? curve?
} ParamDesc;
//#define PARAM_DESC_BYTES 33

// parameter data
typedef struct __attribute__((__packed__)) ParamDataStruct {
  volatile ParamValue value;
  volatile u8 changed;
} ParamData;

#endif // header guard
