#define USE_PORT_MODULE 1

#include <stdio.h>   
#include <string.h>

#if USE_PORT_MODULE
#include "port.h"
#else
#include <termios.h>
#include <unistd.h>  
#include <fcntl.h>   
#include <errno.h>  
#include <assert.h>
#endif

#if USE_PORT_MODULE
#else
// terminal attributes
static struct termios tty;
// serial port file descriptor
static int ser_fd;
// serial port file pointer
static FILE* ser_fp;
// received value
int rx;
#endif

int main (int argc, char** argv) {
  // return code
  int ret;
  // received value
  int rx;
  // print buffer
  char str[256];

  if(argc < 2) {
	fprintf(stderr, "a serial device path is required.");
	return -2;
  }

#if USE_PORT_MODULE
  port_init(argv[1]);
#else
  //----- port setup
  memset (&tty, 0, sizeof tty);
  
  ser_fd = open(argv[1], O_RDWR | O_NOCTTY);

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
  //------
  
#endif

  while(1) {
#if USE_PORT_MODULE
	port_read();
#else
	ret = read(ser_fd, &rx, 1);
	if(ret > 0) {
	  printf("%c", (char)rx);
	}
#endif
	
  }

  // cleanup
#if USE_PORT_MODULE
  port_cleanup();
#else 
  fflush(ser_fp);
  close(ser_fd);
#endif
  
  return 0;
  
}
