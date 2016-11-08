/*
  c interface for serial remote control of aleph-bees.
  
  for sending commands, the bees-serial module maintains an internal byte buffer.
  the tx functions cause that buffer to be filled with approparite bytes.

  calling code should go something like, e.g.

  // our serial device
  FILE* serial = ...

  // build the tx buffer
  bees_serial_new_op(optype);
  
  // send the buffer
  const u8* buf = bees_serial_tx_buf();
  for(int i=0; i<bees_serial_tx_nb; i++) {
    putc(*buf++, serial);
  }

 */

#ifndef _BEES_SERIAL_H_
#define _BEES_SERIAL_H_

#include "types.h"

#include "serial_msg_types.h"

//------------------------------------
//----- buffer access
const u8* bees_serial_tx_buf(void);
const int bees_serial_tx_nb(void);

// any reason for user to access raw rx buffer?
//const u8* bees_serial_rx_buf(void);
//const int bees_serial_rx_nb(void);

//-------------------------------------
//----- receive
// get some new bytes
const char* bees_serial_rx(const u8* bytes, const int nb);

//-------------------------------------
//----- transmit
//-- modify network
// create new operator at end of list
extern void bees_serial_new_op(int opClass);
// delete operator from end of list
extern void bees_serial_delete_op(void);
// connect out to in
extern void bees_serial_connect(int out, int in);
// disconnect
extern void bees_serial_disconnect(int out);
// store current state to given preset
extern void bees_serial_preset_store(int idx);
// recall given preset
extern void bees_serial_preset_recall(int idx);

// TODO?
// void bees_op_insert(int opClass, int idx);
// void bees_op_remove(int idx);
// void bees_preset_set_name(const char* name);
// void bees_scene_set_name(const char* name);
// void bees_scene_save(void);
// void bees_scene_load(const char* name);

//-- bang network
extern void bees_serial_in_trigger(int idx, int val);
extern void bees_serial_param_trigger(int idx, int val);

//-- query values
extern void bees_serial_in_query(int idx);
extern void bees_serial_param_query(int idx);

//-- dump strings
extern void bees_serial_dump_ins(void);
extern void bees_serial_dump_outs(void);
extern void bees_serial_dump_connections(void);
extern void bees_serial_dump_ops(void);
extern void bees_serial_dump_op_descriptions(void);
extern void bees_serial_dump_params(void);

#endif


