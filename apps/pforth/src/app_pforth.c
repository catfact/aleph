/*
  app_pforth.c
*/

// asf
#include "delay.h"
#include "gpio.h"
#include "print_funcs.h"
#include "sd_mmc_spi.h"

// avr32_lib
#include "app.h"
#include "bfin.h"
#include "encoders.h"

//--- app-specific
#include "app_timers.h"
#include "handler.h"
#include "render.h"

// this is called during hardware initialization.
// allocate memory here.
void app_init(void) {
  print_dbg("\r\n mix; app_init...");  
  // render_init();
}

// this is called from the event queue to start the app 
// return >0 if there is an error doing firstrun init
u8 app_launch(eLaunchState firstrun) {
  print_dbg("\r\n pforth app_launch, firstrun: ");
  print_dbg_ulong(firstrun);

  // enable timers
  init_app_timers();

  // render initial screen
  render_startup();
  render_update();

  if(firstrun) { 
    // first run since module was flashed.
  } else {
    // this wasn't the first run, so try and load last saved settings
  }

  // set app event handlers
  assign_event_handlers();

  // tell the main loop that we launched successfully.
  // if this was the first run, 
  // main() should now write the firstrun pattern to flash and reboot.
  return 1;
}
