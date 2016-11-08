/*
  serial port interface
 */


#ifndef _PORT_H_
#define _PORT_H_

#include <pthread.h>
#include "types.h"

// intialize the port
extern int port_init(char* device);

// close the port
extern void port_cleanup(void);

// transmit contents of internal tx buffer
extern void port_write(const u8* data, int nb);

// read a single byte (blocking)
extern int port_read_byte(void);

// FIXME
/*
// read all available bytes to internal buffer, with mutex
extern void port_read_mutex(pthread_mutex_t* lock);

// access the read buffer
extern const u8* port_rx_buf(void);

// access number of bytes read
extern const int port_rx_nb(void);

// reset the read pointer and byte count
extern void port_rx_reset(void);
*/

#endif
