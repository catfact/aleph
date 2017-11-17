/// reverting


#include "bfin_core.h"
#include "cv.h"
#include "gpio.h"

// AD5686R 16-bit quad DAC
#define CV_DAC_COM_WRITE 0x3
#define CV_DAC_COM_LSHIFT 20
#define CV_DAC_ADDR_LSHIFT 16

//====================
//=== global variables , initialized here
volatile u32 cvTxBuf = 0x00000000;

//=============================
// extern functions

// intialize the cv dac
void init_cv(void) {
  u32 delay;
  // always keep LDAC low
  CV_DAC_LDAC_LO;
  // bring the DAC out of reset
  CV_DAC_RESET_LO;
  delay = 100000;
  while(delay > 0) { delay--; }
  CV_DAC_RESET_HI;
}


// update via DMA
void cv_update(u8 ch, fract32 val) {
  u32 buf;
  buf = 0;
  buf |= (CV_DAC_COM_WRITE << CV_DAC_COM_LSHIFT);

  buf = 0x300000;
  buf |= ((1 << ch) << CV_DAC_ADDR_LSHIFT);
	
  // shift from fract32 (positive)
  buf |= (val >> 15 ) & 0xffff;
  
  // extra bit for weird FS timing kludge (need 25 clocks)
  // cvTxBuf = buf << 1;
  //  cvTxBuf = buf;

  /// ok. try writing directly to SPORT1 FIFO and registers, no DMA
  // disable TX
  *pSPORT1_TCR1  &= ~TSPEN;
  //  LED4_HI;
  
  // fill the FIFO (secondary data side)
  /// primary data (dummy);
  //  *pSPORT1_TX32 = 0;
  /// secondary data (the real stuff)
  *pSPORT1_TX32 = buf;
  *pSPORT1_TX32 = buf;
  
  // enable TX
  *pSPORT1_TCR1 |= TSPEN;

  // show me a thing
  //  LED4_LO;
  
}
