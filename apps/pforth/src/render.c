/*
  render.c
  
  aleph-mix

  definitions for rendering graphics.

*/

//--- std headers
#include <string.h>

//--- asf headers
#include "print_funcs.h"

//--- avr32-lib headers
#include "app.h"
// font-rendering functions
#include "font.h"
// region class
#include "region.h"
// screen refresh function
#include "screen.h"

//--- application headers
//#include "ctl.h"
#include "render.h"

//-------------------------------------------------
//----- -static variables

/* 
   the screen-drawing routines in avr32_lib provide the "region" object
   a simple 16-bit pixel buffer with width, height, x/y offset, and dirty flag.
   there are also methods for basic fill and text rendering into regions.
*/

// one drawing region for each channel
static region regChan[] = { 
  { .w=62, .h=30, .x=0,  .y=0  },
  { .w=62, .h=30, .x=64, .y=0  },
  { .w=62, .h=30, .x=0,  .y=32 },
  { .w=62, .h=30, .x=64, .y=32 },
};

//-------------------------
//---- static funcs

//... nothing here.

//-------------------------------------------------
//----- external functions

// initialze renderer
void render_init(void) {
  // allocate memory for each region
  region_alloc(&regChan[0]);
  region_alloc(&regChan[1]);
  region_alloc(&regChan[2]);
  region_alloc(&regChan[3]);
}

// fill with initial graphics
void render_startup(void) {
  u32 i;
  for(i=0; i<4; i++) { 
    // fill the graphics buffer (with black)
    region_fill(&(regChan[i]), 0x0);
    // physically render the region data to the screen
    region_draw(&(regChan[i]));
  }
}

// update dirty regions
// (this will be called from an application timer)
void render_update(void) {
  app_pause();

  // physically update the screen with each region's data (if changed)
  region_draw( &(regChan[0]) );
  region_draw( &(regChan[1]) );
  region_draw( &(regChan[2]) );
  region_draw( &(regChan[3]) );

  app_resume();
}

/*

... do other stuff with the regions
 */
