#include "init.h"

/* all modules are initialized here */
void Init(void)
{
    /* clear the soft lock bit of the SWT watchdog, just in case */
	SWT.SR.B.WSC = 0xc520;
	SWT.SR.B.WSC = 0xd928;	
    /* disable the SWT watchdog and configure it for not interfering with the debugger */
	SWT.CR.R = 0x8000010A;

    // initialize ME
    MEInit();
    // initialize IO
    SIUInit();
    // initialize CAN
    CANInit();
    // initialize INTC
    InterruptInit();
    // initiliaze PIT
    PITInit();
    // initiliaze ADC
    ADCInit();
    
    // enable external interrupts
    asm("wrteei 1");
}