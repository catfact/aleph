
#include "bfin_core.h"
#include "isr.h"
#include "init.h"

//------ global variables initialized here
// SPORT0 DMA transmit buffer
volatile s32 iTxBuf[4];
// SPORT0 DMA receive buffer
volatile s32 iRxBuf[4];

//----- function definitions
// initialize clocks
void init_clocks(void) {
  /// MSEL = 19
  //// VCO = 19 * CLKIN = 513
  *pPLL_CTL = 0x2600;
  ssync();
  
}

// initialize EBI
void init_EBIU(void) {
  //  straight from the self-test example project
  // Initalize EBIU control registers to enable all banks
  *pEBIU_AMBCTL1 = 0xFFFFFF02;
  ssync();
  
  *pEBIU_AMGCTL = 0x00FF;
  ssync();
  
  // Check if already enabled
  if( SDRS != ((*pEBIU_SDSTAT) & SDRS) ) {
    return;
  }
  
  //SDRAM Refresh Rate Control Register
  // for 108Mhz system clock:
  *pEBIU_SDRRC = 835;
  
  //SDRAM Memory Bank Control Register
  *pEBIU_SDBCTL = 0x0025; //1.7	64 MB bank size
  
  //SDRAM Memory Global Control Register
  *pEBIU_SDGCTL = 0x0091998d;
  ssync();
}

// setup SPI0 -> AD1939 config */
void init_1939(void) { 
  //  u8 i; 
  volatile u32 del;

  //// reset codec
  *pFIO_FLAG_D &= CODEC_RESET_MASK;
  del = 100; while(del--) { ;; } 
  *pFIO_FLAG_D |= (0xffff ^ CODEC_RESET_MASK);
  del = 10000; while(del--) { ;; } 
  /// using the codec in standalone now, dont need SPI config
  return;

} // init_1939


//--------------------------------------------------------------------//
// init_spi_slave()
// (re-)configure spi in slave mode to receive control data from avr32 
void init_spi_slave(void) {
  int j;
  // don't attempt to drive the clock
  *pSPI_BAUD = 0;
  // reset the flags register? to defaults?
  *pSPI_FLG = 0xff00;

  // try clearing the rx error bit? (sticky - W1C)
  *pSPI_STAT |= 0x10;  
  *pSPI_STAT |= 0x10;  
  // slave mode, 16 bit transfers, MSB first, non-dma rx mode, overwrite (interrupt when SPI_RDBR is full) 
  // actually need 8 bits to be compatible with SPI-boot
  *pSPI_CTL = CPHA | GM | SZ;
  // enable transmit on MISO
  *pSPI_CTL |= EMISO;
  // enable spi (now in slave mode)
  *pSPI_CTL = (*pSPI_CTL | SPE);
  // clear the spi rx register by reading from it
  j = *pSPI_RDBR;
  // clear the rx error bit (sticky - W1C)
  *pSPI_STAT |= 0x10;
}

// configure sport0 for i2s mode with external clock
void init_sport0(void)
{
  // Sport0 receive configuration
  // External CLK, External Frame sync, MSB first, Active Low
  // 24-bit data, Stereo frame sync enable
  *pSPORT0_RCR1 = RFSR | RCKFE;
  *pSPORT0_RCR2 = SLEN_24 | RXSE | RSFSE;
  
  // Sport0 transmit configuration
  // External CLK, External Frame sync, MSB first, Active Low
  // 24-bit data, Secondary side enable, Stereo frame sync enable
  *pSPORT0_TCR1 = TFSR | TCKFE;
  *pSPORT0_TCR2 = SLEN_24 | TXSE | TSFSE;
}

// CONFIGURE sport1  [ drive 1x AD5686 from DTSEC ]
void init_sport1(void) {
  
  //----- note: edge selection is for *driving* the pins, sampled opposite
  // TFS/clk driven w/ rising  edge : TCKFE
  // late frame sync              : LATFS  
  // TFS active low               : LTFS   
  // data-dependent TFS            : DITFS
  // internal clock                : ITCLK
  // internal TFS                  : ITFS 
  // frame sync required           : TFSR
  // no companding                 : TDTYPE xx
  // MSB first                     : TLSBIT

  // really seems like this should be correct...
  *pSPORT1_TCR1 =  ITCLK | ITFS | TFSR | LTFS | LATFS;
  
  // also tried this...
  //  *pSPORT1_TCR1 =  TCKFE | ITCLK | ITFS | TFSR | LTFS | LATFS;
  
  // but this totally wrong thing is the only one that produces results
  // *pSPORT1_TCR1 =  ITCLK | ITFS | TFSR;
  
  //// normal mode, not stereo : TSFSE = 0
  //// secondary data enabled  : TXSE  = 1
  ///// 24-bit word length
  *pSPORT1_TCR2 = 23 | TXSE ;
  
  //// 25-bit for some damn reason
  // *pSPORT1_TCR2 = 24 | TXSE ;
  
  // tclk = sclk / ( 2 x (div + 1)
  // we want < 25Mhz
  // sclk = 108M, so:
  // *pSPORT1_TCLKDIV = 1; // = 27 Mhz
   *pSPORT1_TCLKDIV = 2; // = 18 Mhz.. not ideal but o k
}


// initialize DMA in autobuffer mode
void init_DMA(void) {
  // Set up DMA1 to receive
  // Map DMA1 to Sport0 RX
  *pDMA1_PERIPHERAL_MAP = 0x1000;
  
  // Configure DMA1
  // 32-bit transfers, Interrupt on completion, Autobuffer mode
  *pDMA1_CONFIG = WNR | WDSIZE_32 | DI_EN | FLOW_1;
  // Start address of data buffer
  *pDMA1_START_ADDR = (void *)iRxBuf;
  // DMA inner loop count
  *pDMA1_X_COUNT = 4;
  // Inner loop address increment
  *pDMA1_X_MODIFY = 4;
  
  // Set up DMA2 to transmit
  // Map DMA2 to Sport0 TX2 
  *pDMA2_PERIPHERAL_MAP = 0x2000;
  
  // Configure DMA2
  // 32-bit transfers, Autobuffer mode
  *pDMA2_CONFIG = WDSIZE_32 | FLOW_1;
  // Start address of data buffer
  *pDMA2_START_ADDR = (void *)iTxBuf;
  // DMA inner loop count
  *pDMA2_X_COUNT = 4;
  // Inner loop address increment
  *pDMA2_X_MODIFY = 4;

#if 0
  /// map dma4 to sport1 tx
  *pDMA4_PERIPHERAL_MAP = 0x4000;
  // 32-bit transfers, autobuffer, no interrupt
  *pDMA4_CONFIG = WDSIZE_32 | FLOW_1;
  //*pDMA4_CONFIG = WDSIZE_32 | FLOW_1 | DI_EN;
  // Start address of data buffer
  *pDMA4_START_ADDR = (void *)(&cvTxBuf);
  // DMA inner loop count
  /// primary tx data is dummy!
  *pDMA4_X_COUNT = 1;
  // inner loop address increment
  *pDMA4_X_MODIFY = 4;
#endif

}

// enable sport0 DMA
void enable_DMA_sport0(void) {
  // enable DMAs
  *pDMA2_CONFIG	= (*pDMA2_CONFIG | DMAEN);
  *pDMA1_CONFIG	= (*pDMA1_CONFIG | DMAEN);
  
  // enable sport0 TX and RX
  *pSPORT0_TCR1 	= (*pSPORT0_TCR1 | TSPEN);
  *pSPORT0_RCR1 	= (*pSPORT0_RCR1 | RSPEN);
}

// begin transfers with sport1 and dma4
void enable_DMA_sport1(void) {
  #if 0
  // enable DMA4
  *pDMA4_CONFIG	= (*pDMA4_CONFIG | DMAEN);
  // enable sport1 tx
  *pSPORT1_TCR1 	= (*pSPORT1_TCR1 | TSPEN);
  #endif
}


// initialize programmable flags
void init_flags(void) {
  // outputs
  *pFIO_DIR = 0;
  *pFIO_DIR |= CODEC_RESET_UNMASK;
  *pFIO_DIR |= CODEC_RESET_UNMASK;
  *pFIO_DIR |= CV_DAC_RESET_UNMASK;
  *pFIO_DIR |= CV_DAC_LDAC_UNMASK;
  *pFIO_DIR |= READY_UNMASK;
  *pFIO_DIR |= LED3_UNMASK;
  *pFIO_DIR |= LED4_UNMASK;
}

// assign interrupts
void init_interrupts(void) {
  int i=0;

#if 0 // original
 
  // by default:
  // sport0 rx (dma1) -> ID2 = IVG9
  // sport1 tx        -> ID2 = IVG9
  // spi rx           -> ID3 = IVG10

  // assign ISRs to interrupt vectors:
  //// ok, this ISR will serve both sports if enabled..
  *pEVT9 = sport0_rx_isr;
  *pEVT10 = spi_rx_isr;

  //  *pEVT10 = sport1_tx_isr;

  // unmask in the core event processor
  asm volatile ("cli %0; bitset(%0, 9); bitset(%0, 10); sti %0; csync;": "+d"(i));

  // unmask peripheral interrupts
  *pSIC_IMASK = 0x00003200; 
#else
  // default interrupt assignments:
  // sport0 rx (dma1) -> ID2 = IVG9
  // spi rx           -> ID3 = IVG10
  // assign sport1 tx -> ID4 = IVG11
  *pSIC_IAR1 = 0x33342221;
  
  // assign ISRs to interrupt vectors:
  *pEVT9 = sport0_rx_isr;
  *pEVT10 = spi_rx_isr;
  *pEVT11 = sport1_tx_isr;

  // unmask in the core event processor
  asm volatile ("cli %0; "
				"bitset(%0, 9); "
				"bitset(%0, 10); "
				"bitset(%0, 11); "
				"sti %0; "
				"csync; " : "+d"(i));
  // unmask peripheral interrupts
  *pSIC_IMASK = 0x0000361f;
  //// BTW: i don't know why we need to unmask IVG12 and IVG13...
  /// if we leave the flags zeroed nothing ever happens!
#endif
}
