#include <stdio.h>
#include "bees-serial.h"

// max buffer size
#define RX_BUF_SIZE 2048 //??
#define TX_BUF_SIZE 256
#define RX_STRING_LEN 4096

// i/o buffers
static u8 tx_buf[TX_BUF_SIZE];
static u8 rx_buf[RX_BUF_SIZE];

// string buffer for returning dumps
static char rx_string_buf[RX_STRING_LEN];

// current buffer counts
static int rx_nb = 0;
static int tx_nb = 0;

//----FIXME: these should go in a header maybe?
// framing byte values
static const u8 START_FLAG = 0x12;
static const u8 END_FLAG = 0x13;
static const u8 DLE = 0x7D;
//----

// aleph expects big-endian values.
// utilities for serializing/deserializing
typedef struct bees_val {
  u8 hi;
  u8 lo;
} bees_val_t;

// this will of course break for val > 0x7fff
bees_val_t unpackSigned(int val) {
  bees_val_t ret = {
	.hi = (val & 0xff00) >> 8,
	.lo = val & 0xff
  };
  if(val > 0) { ret.hi &= 0x7fff; }
  else { ret.hi |= 0x8000; }
  return ret;
}

bees_val_t unpackUnsigned(unsigned int val) {
  bees_val_t ret = {
	.hi = (val & 0xff00) >> 8,
	.lo = val & 0xff
  };
  return ret;
}

//--- write to buffers with bounds checking
static int tx_put(u8 val) {
  if (tx_nb < TX_BUF_SIZE) {
	tx_buf[tx_nb++] = val;
	return 1;
  } else {
	printf("tx buffer is full! \r\n");
	return 0;
  }
}

static int rx_write(u8 val) {
  if (rx_nb < RX_BUF_SIZE) {
	rx_buf[rx_nb++] = val;
	return 1;
  } else {											  
	return 0;
  }
}

//--- write data to tx buffer with framing
static int tx_put_framed(u8 x) {
  int ret;
  if (x == DLE || x == START_FLAG || x == END_FLAG) {
    ret = tx_put(DLE);
	ret &= tx_put(x);
	return ret;
  }
  return tx_put(x);
}

//------------------------------------
//----- buffer access
const u8* bees_serial_rx_buf(void) {
  return (const u8*)rx_buf;
}

const u8* bees_serial_tx_buf(void) {
  return (const u8*)tx_buf;
}

const int bees_serial_rx_nb(void) {
  return rx_nb;
}

const int bees_serial_tx_nb(void) {
  return tx_nb;
}

//-------------------------------------
//----- receive

// process a single byte
static void process_rx_byte(u8 b) {
  if (rx_write(b)) {
	
  } else {
	// buffer is full
  }
  if(b == DLE) {
	
  }

  if(b == END_FLAG) {
	// TODO:
	// do something with the data we've received... 
  }
  
  //---- test
  /*
  printf("%2.2X", b);
  if(b == START_FLAG) { printf (" -- START "); }
  if(b == END_FLAG) { printf (" -- END "); }
  if(b == DLE) { printf (" -- ESCAPE "); }
  printf("\r\n");
  */
  //---- 
}


// get some new bytes
const char* bees_serial_rx(const u8* bytes, const int nb) {
  for(int i=0; i<nb; i++) {
	process_rx_byte(*bytes++);
  }
  /// FIXME: return something useful
  return 0;
}

//-------------------------------------
//----- transmit

static void tx_reset(void) { tx_nb = 0; }

//-- modify network
void bees_serial_new_op(int opClass) {
}

void bees_serial_delete_op(void) {
}

void bees_serial_connect(int out, int in) {
}

void bees_serial_disconnect(int out) {
}

void bees_serial_preset_store(int idx) {
}

void bees_serial_preset_recall(int idx) {
}

void bees_serial_in_trigger(int idx, int val) {
  bees_val_t idxArr = unpackUnsigned(idx);
  bees_val_t valArr = unpackSigned(val);
  tx_reset();
  tx_put(START_FLAG);
  tx_put_framed(eSerialMsg_triggerIn);
  tx_put_framed(idxArr.hi);
  tx_put_framed(idxArr.lo);
  tx_put_framed(valArr.hi);
  tx_put_framed(valArr.lo);
  tx_put(END_FLAG);
}

void bees_serial_param_trigger(int idx, int val) {
  bees_val_t idxArr = unpackUnsigned(idx);
  bees_val_t valArr = unpackSigned(val);
  tx_reset();
  tx_put(START_FLAG);
  tx_put_framed(eSerialMsg_triggerParam);
  tx_put_framed(idxArr.hi);
  tx_put_framed(idxArr.lo);
  tx_put_framed(valArr.hi);
  tx_put_framed(valArr.lo);
  tx_put(END_FLAG);
}


//-- query values
void bees_serial_in_query(int idx) {
  bees_val_t idxArr = unpackUnsigned(idx);
  tx_reset();
  tx_put(START_FLAG);
  tx_put_framed(eSerialMsg_queryIn);
  tx_put_framed(idxArr.hi);
  tx_put_framed(idxArr.lo);
  tx_put(END_FLAG);
}

void bees_serial_param_query(int idx) {
  bees_val_t idxArr = unpackUnsigned(idx);
  tx_reset();
  tx_put(START_FLAG);
  tx_put_framed(eSerialMsg_queryParam);
  tx_put_framed(idxArr.hi);
  tx_put_framed(idxArr.lo);
  tx_put(END_FLAG);  
}

//-- dump strings
void bees_serial_dump_ops(void) {
  tx_reset();
  tx_put(START_FLAG);
  tx_put_framed(eSerialMsg_dumpOps);
  tx_put(END_FLAG);
}

void bees_serial_dump_ins(void) {
}

void bees_serial_dump_outs(void) {
}

void bees_serial_dump_connections(void) {
}

void bees_serial_dump_op_descriptions(void) {
}

void bees_serial_dump_params(void) {
}

