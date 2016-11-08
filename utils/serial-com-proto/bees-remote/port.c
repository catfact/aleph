#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>  
#include <fcntl.h>   
#include <errno.h>  
#include <assert.h>
#include "port.h"

// terminal attributes
static struct termios tty;
// serial port file descriptor
static int ser_fd;
// serial port file pointer
static FILE* ser_fp;

// last return code
static int ret;
// last received value
static int rx;

// buffer
#define RX_BUF_SIZE 4096
u8 rx_buf[RX_BUF_SIZE];
int rx_nb = 0;

int port_init(char* device) {
  printf("port_init(%s) \r\n", device);
  memset (&tty, 0, sizeof tty);
  
  ser_fd = open(device, O_RDWR | O_NOCTTY);

  if ( tcgetattr ( ser_fd, &tty ) != 0 ) {
	fprintf(stderr, "error getting tty attributes \r\n");
  }

  cfsetspeed (&tty, (speed_t)B115200);
  cfmakeraw(&tty);
  
  tcflush( ser_fd, TCIFLUSH );
  if ( tcsetattr ( ser_fd, TCSANOW, &tty ) != 0) {
	fprintf(stderr, "error setting tty attributes \r\n");
  }
  
  ser_fp = fdopen(ser_fd, "w");
}

void port_cleanup(void) { 
  fflush(ser_fp);
  close(ser_fd);
}


void port_write(const u8* data, int nb) {
  for(int i=0; i<nb; i++) {
	assert(putc(*(data+i), ser_fp) != EOF);
  }
  fflush(ser_fp);
}

int port_read_byte(void) {
  ret = read(ser_fd, &rx, 1);
  if(ret > 0) {
	return rx & 0xff;
  } else {
	return -1;
  }
}

// FIXME
/*
void port_read_buf_lock(pthread_mutex_t* lock) {
  do {
	ret = read(ser_fd, &rx, 1);
	if(ret > 0) {
	  pthread_mutex_lock(lock);
	  rx_buf[rx_nb] = (u8)rx;
	  rx_nb = (rx_nb + 1) & (RX_BUF_SIZE-1);
	  pthread_mutex_unlock(lock);
	}
  } while (ret > 0);
}

const u8* port_rx_buf(void) {
  return (const u8*)rx_buf;
}

const int port_rx_nb(void) {
  return rx_nb;
}

// reset the read pointer and byte count
void port_rx_reset(void) {
   rx_nb = 0;
}
*/
