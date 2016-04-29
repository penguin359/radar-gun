/* ###################################################################
**     Filename    : main.c
**     Project     : blinky
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-04-16, 01:13, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LedRed.h"
#include "BitIoLdd1.h"
#include "LedGreen.h"
#include "BitIoLdd2.h"
#include "LedBlue.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "KSDK1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "CS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "DA1.h"
#include "DacLdd1.h"
#include "CLS2.h"
#include "TMOUT1.h"
#include "USB1.h"
#include "USB0.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "fft.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  WAIT1_Waitms(3000);
  CLS1_SendStr("Hello, Freedom!\r\n", CLS1_GetStdio()->stdOut);
  run_fft();
  CLS1_SendStr("FFTed.\r\n", CLS1_GetStdio()->stdOut);
#if 0
  CLS1_SendStr("fftDC = {\r\n", CLS1_GetStdio()->stdOut);
  for(size_t i = 0; i < 64; i++) {
	  CLS1_SendStr(" { ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(dinDC[2*i], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(", ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(dinDC[2*i+1], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(" },\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("};\r\n", CLS1_GetStdio()->stdOut);
  CLS1_SendStr("fft1Hz = {\r\n", CLS1_GetStdio()->stdOut);
  for(size_t i = 0; i < 64; i++) {
	  CLS1_SendStr(" { ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(din1Hz[2*i], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(", ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(din1Hz[2*i+1], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(" },\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("};\r\n", CLS1_GetStdio()->stdOut);
  CLS1_SendStr("fft1HzShort = {\r\n", CLS1_GetStdio()->stdOut);
  for(size_t i = 0; i < 4; i++) {
	  CLS1_SendStr(" { ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(din1HzShort[2*i], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(", ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(din1HzShort[2*i+1], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(" },\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("};\r\n", CLS1_GetStdio()->stdOut);
  CLS1_SendStr("fftMulti = {\r\n", CLS1_GetStdio()->stdOut);
  for(size_t i = 0; i < 64; i++) {
	  CLS1_SendStr(" { ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(dinMulti[2*i], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(", ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(dinMulti[2*i+1], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(" },\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("};\r\n", CLS1_GetStdio()->stdOut);
  CLS1_SendStr("fft50ms = {\r\n", CLS1_GetStdio()->stdOut);
  for(size_t i = 0; i < 1024; i++) {
	  CLS1_SendStr(" { ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(din50ms[2*i], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(", ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum32s(din50ms[2*i+1], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(" },\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("};\r\n", CLS1_GetStdio()->stdOut);
#endif
  CLS1_SendStr("fft20ms = {\r\n", CLS1_GetStdio()->stdOut);
  for(size_t i = 0; i < 1024; i++) {
	  CLS1_SendStr(" { ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum16s(din20ms[2*i], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(", ", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum16s(din20ms[2*i+1], CLS1_GetStdio()->stdOut);
	  CLS1_SendStr(" },\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("};\r\n", CLS1_GetStdio()->stdOut);
	int32_t freq = find_peak_frequency(din20ms, log2N20ms, 4);
	int32_t speed = convertToSpeed(freq);
	CLS1_SendStr("Frequency: ", CLS1_GetStdio()->stdOut);
	CLS1_SendNum32s(freq, CLS1_GetStdio()->stdOut);
	CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr("Speed: ", CLS1_GetStdio()->stdOut);
	CLS1_SendNum32s(speed, CLS1_GetStdio()->stdOut);
	CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
	for(;;) {
		extern uint32_t timeElapsed;
		uint32_t startCount = 0;
		LedRed_NegVal();
		CLS1_SendStr(".", CLS1_GetStdio()->stdOut);
		WAIT1_Waitms(500);
		//CDC1_SendString("Hello, USB!\r\n");
		startCount = timeElapsed;
		calculate_fft(din20ms, 1024);
		CLS1_SendStr("T:", CLS1_GetStdio()->stdOut);
		CLS1_SendNum32u(timeElapsed - startCount, CLS1_GetStdio()->stdOut);
		CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
	}

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
