#include "net_protected.h"
#include "print_funcs.h"

#include "pickle.h"
#include "op_route.h"

//-------------------------------------------------
//----- descriptor
static const char* op_route8_instring =  "VAL\0    TO\0     ";
static const char* op_route8_outstring = "O0\0     O1\0     O2\0     O3\0     O4\0     O5\0     O6\0     O7\0     ";
static const char* op_route8_opstring = "ROUTE8";

//-------------------------------------------------
//----- static function declaration


// set inputs
static void op_route8_in_val(op_route8_t* route, const io_t v);
static void op_route8_in_to(op_route8_t* route, const io_t v);
// pickle / unpickle
static u8* op_route8_pickle(op_route8_t* route, u8* dst);
const static u8* op_route8_unpickle(op_route8_t* route, const u8* src);

// array of input functions 
static op_in_fn op_route8_in[2] = {
  (op_in_fn)&op_route8_in_val,
  (op_in_fn)&op_route8_in_to
};

//----- external function definition

/// initialize
void op_route8_init(void* op) {
  op_route8_t* route = (op_route8_t*)op;

  // superclass functions
  route->super.in_fn = op_route8_in;
  route->super.pickle = (op_pickle_fn) (&op_route8_pickle);
  route->super.unpickle = (op_unpickle_fn) (&op_route8_unpickle);
  
  // superclass state
  route->super.numInputs = 2;
  route->super.numOutputs = 8;
  route->outs[0] = -1;
  route->outs[1] = -1;
  route->outs[2] = -1;
  route->outs[3] = -1;
  route->outs[4] = -1;
  route->outs[5] = -1;
  route->outs[6] = -1;
  route->outs[7] = -1;
 
  route->super.in_val = route->in_val;
  route->in_val[0] = &(route->val);
  route->in_val[1] = &(route->to);

  route->super.out = route->outs;
  route->super.opString = op_route8_opstring;
  route->super.inString = op_route8_instring;
  route->super.outString = op_route8_outstring;
  route->super.type = eOpRoute8;

  // class state
  route->val = 0;
  route->to = 0;
}

//-------------------------------------------------
//----- static function definition

//===== operator input

// input state
static void op_route8_in_val(op_route8_t* route, const io_t v) {
  route->val = v;
  net_activate(route->outs[route->to], route->val, route);
}

// to where
static void op_route8_in_to(op_route8_t* route, const io_t v) {
  io_t val = v;
  if(val<0) val = 0;
  else if(val>7) val = 7;
  route->to = val;
}


// serialization
u8* op_route8_pickle(op_route8_t* route, u8* dst) {
  dst = pickle_io(route->to, dst);
  return dst;
}

const u8* op_route8_unpickle(op_route8_t* route, const u8* src) {
  src = unpickle_io(src, &(route->to));
  return src;
}
