#include <stdio.h>
#include <ctype.h>  
#include <string.h>  
#include <curses.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>  

#include "bees-serial.h"
#include "port.h"

// quit flag
int quit = 0;

// window for user input
static WINDOW* win_input;
// window for text from device
static WINDOW* win_display;

void show_input(const char* str) {
  mvwprintw(win_input, 0, 0, str);
  wclrtoeol(win_input);
  wrefresh(win_input);
}

// loop for grabbing UI input
void* ui_tx_loop(void* arg) {
  int tx;
  int ch;
  int rx_nb;
  const u8* rx_buf;
  char str[256];
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
	  show_input("param_trigger (0, 1)");
	  bees_serial_param_trigger(0, 1);
	  tx = 1;
	  break;
	case 111: // o
	  show_input("dump_ops");
	  bees_serial_dump_ops();
	  tx = 1;
	  break;	  
	case 112: // p
	  show_input("param_query (0)");
	  bees_serial_param_query(0);
	  tx = 1;
	  break;
	case 105: // i
	  show_input("in_query (0)");
	  bees_serial_in_query(0);
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
	if(quit) { break; }
	rx = port_read_byte();
	if(rx > 0) {
	  // TODO: pass this along to the bees serial format parser
	  #if 0
	  ch = (char)rx;
	  if(isprint(ch)) {
		waddch(win_display, ch);
		//		wrefresh(win_display);
	  }
	  #else
	  sprintf(str, "%2.2x ", rx);
	  waddstr(win_display, str);
	  wrefresh(win_display);
	  #endif
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
  cbreak();
  noecho();
  timeout(0);

  win_input = newwin(4, COLS, 0, 0);
  
  win_display = newwin(LINES-5, COLS, 5, 0);
  scrollok(win_display, TRUE);
  
  pthread_create(&ui_tx_thread, NULL, ui_tx_loop, NULL);
  pthread_create(&rx_thread, NULL, rx_loop, NULL);

  pthread_join(ui_tx_thread, NULL);
  pthread_join(rx_thread, NULL);

  printf("cleaning up... \r\n");
  port_cleanup();
  endwin();
  
  return 0;
  
}
