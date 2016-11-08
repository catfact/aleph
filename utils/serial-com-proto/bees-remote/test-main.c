#include <stdio.h>
#include <ctype.h>
#include <string.h>  
#include <curses.h>
#include <pthread.h>
#include <unistd.h>  

#include "bees-serial.h"
#include "port.h"

// loop for grabbing UI input
void* ui_tx_loop(void* arg) {
  int tx;
  int ch;
  int rx_nb;
  const u8* rx_buf;
  char str[256];
  int quit = 0;
  
  while(1) {
	if(quit) { break; }

	tx = 0;
	ch = getch();
	
	switch(ch) {
	case 27:    // esc
	  quit = 1;	
	case 113:   // q
	  quit = 1;
	  break;
	case 116: // t
	  mvprintw(0, 0, "param_trigger (0, 1)"); clrtoeol();
	  bees_serial_param_trigger(0, 1);
	  tx = 1;
	  break;
	case 111: // o
	  mvprintw(0, 0, "dump_ops"); clrtoeol();
	  bees_serial_dump_ops();
	  tx = 1;
	  break;	  
	case 112: // p
	  mvprintw(0, 0, "param_query (1)"); clrtoeol();
	  bees_serial_param_query(1);
	  tx = 1;
	  break;
	case 105: // i
	  mvprintw(0, 0, "in_query (1)"); clrtoeol();
	  bees_serial_in_query(1);
	  tx = 1;
	  break;
	default:
	  ;;
	}

	if(tx) {
	  port_write(bees_serial_tx_buf(), bees_serial_tx_nb());
	}
  } // while(1)
  pthread_exit(NULL);

}

// loop for reading from the serial port
void* rx_loop(void* arg) {
  int rx, ch;
  char str[32];
  while(1) {
	// doesn't work... 
	// if(quit) { break; }
	rx = port_read_byte();
	if(rx > 0) {
	  ch = (char)rx;
	  if(isprint(ch)) { addch(ch); }
	}
  }
  // never gets here
  pthread_exit(NULL);
}

int main (int argc, char** argv) {
  pthread_t rx_thread;
  pthread_t ui_tx_thread;
  
  if(argc < 2) {
	fprintf(stderr, "a serial device path is required; exiting. \r\n");
	return -2;
  }
  port_init(argv[1]);

  // init ncurses
  initscr();
  clear();
  noecho();
  cbreak();  

  pthread_create(&ui_tx_thread, NULL, ui_tx_loop, NULL);
  pthread_create(&rx_thread, NULL, rx_loop, NULL);

  pthread_join(ui_tx_thread, NULL);
  
  // FIXME: would be nice to do a clean exit
  // but rx_thread still blocks on read()...
  //  pthread_join(rx_thread, NULL);
  pthread_cancel(rx_thread);

  printf("cleaning up... \r\n");
  port_cleanup();
  endwin();
  
  return 0;
  
}
