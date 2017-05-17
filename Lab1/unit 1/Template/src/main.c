#include "init.h"

void showData(int value);

/********************************************************************
 *                              main                                *
 ********************************************************************/
void main(void)
{
    /* board initialization */
    Init();
	
	bool timerIsStarted = 0;
	PIT_ConfigureTimer( 0, 1000 ); /*milliseconds*/
	/*PIT_ConfigureTimer( int timerChannel, unsigned int time)*/

    /* forever */
    for(;;)
    {
/********************************************************************
 *                           Main Loop                              *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                  Write down your logic here.                     *
 ********************************************************************/  
	/* Show the data of the light sensor*/
	showData(ADC_0.CDR[2].B.CDATA); 
	
	/* Show the data of the potentiometer*/
	//showData(showData(ADC_0.CDR[4].B.CDATA));
	
	/*
		/*
	BT6 PA0 No pull-up/down, off=float, on=low/high jumper
	BT5 PA1 No pull-up/down, off=float, on=low
		*/
	// LED5 is on when BT5 is pressed
	if(SIU.GPDI[1].R == 0)
		SIU.GPDO[61].R = 0;
	else
		SIU.GPDO[61].R = 1;
	// LED6 is on when BT6 is pressed
	if(SIU.GPDI[0].R == 0)
		SIU.GPDO[59].R = 0;
	else
		SIU.GPDO[59].R = 1;
	*/
	
/*	
	// when SW1 is activated activate the timer
	if(SIU.GPDI[44].R = 0)
	{
		if(timerIsStarted == 0)
		{
			PIT_StartTimer( 0 );
			timerIsStarted = 1;
		}

	}
	else
	{
		PIT_StopTimer( 0 );
		timerIsStarted = 0;
	}
*/		
		
		
    }
}

void showData(int value)
{
/********************************************************************
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 ********************************************************************/  
  if(value <= 256)
  {   
    /* LED0 - on, LED1 - off, LED2 - off, LED3 - off */
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 1;
	SIU.GPDO[13].R = 1;
	SIU.GPDO[12].R = 1;
	SIU.GPDO[62].R = 1;
	SIU.GPDO[61].R = 1;
	SIU.GPDO[59].R = 1;
	SIU.GPDO[11].R = 1;
  }
  else if(value > 256 && value <= 512)
  {  
    /* LED0 - on, LED1 - on, LED2 - off, LED3 - off */
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 0;
	SIU.GPDO[13].R = 1;
	SIU.GPDO[12].R = 1;
	SIU.GPDO[62].R = 1;
	SIU.GPDO[61].R = 1;
	SIU.GPDO[59].R = 1;
	SIU.GPDO[11].R = 1;
  }
  else if(value > 512 && value <= 768)
  {  
    /* LED0 - on, LED1 - on, LED2 - on, LED3 - off */
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 0;
	SIU.GPDO[13].R = 0;
	SIU.GPDO[12].R = 1;
	SIU.GPDO[62].R = 1;
	SIU.GPDO[61].R = 1;
	SIU.GPDO[59].R = 1;
	SIU.GPDO[11].R = 1;
  }    
  else
  {  
    /* LED0 - on, LED1 - on, LED2 - on, LED3 - on */
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 0;
	SIU.GPDO[13].R = 0;
	SIU.GPDO[12].R = 0;
	SIU.GPDO[62].R = 0;
	SIU.GPDO[61].R = 0;
	SIU.GPDO[59].R = 0;
	SIU.GPDO[11].R = 0;
  }   

///////////////////////////
/**
  if(value <= 205)
  {   
    // LED0 - on, LED1 - off, LED2 - off, LED3 - off, LED4 - off 
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 1;
	SIU.GPDO[13].R = 1;
	SIU.GPDO[12].R = 1;
	SIU.GPDO[62].R = 1;
	SIU.GPDO[61].R = 1;
	SIU.GPDO[59].R = 1;
	SIU.GPDO[11].R = 1;
  }
  else if(value > 205 && value <= 410)
  {  
    // LED0 - on, LED1 - on, LED2 - off, LED3 - off, LED4 - off 
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 0;
	SIU.GPDO[13].R = 1;
	SIU.GPDO[12].R = 1;
	SIU.GPDO[62].R = 1;
	SIU.GPDO[61].R = 1;
	SIU.GPDO[59].R = 1;
	SIU.GPDO[11].R = 1;
  }
  else if(value > 410 && value <= 615)
  {  
    // LED0 - on, LED1 - on, LED2 - on, LED3 - off, LED4 - off 
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 0;
	SIU.GPDO[13].R = 0;
	SIU.GPDO[12].R = 1;
	SIU.GPDO[62].R = 1;
	SIU.GPDO[61].R = 1;
	SIU.GPDO[59].R = 1;
	SIU.GPDO[11].R = 1;
  }    
  else if(value > 615 && value <= 820)
  {  
    // LED0 - on, LED1 - on, LED2 - on, LED3 - on, LED4 - off 
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 0;
	SIU.GPDO[13].R = 0;
	SIU.GPDO[12].R = 0;
	SIU.GPDO[62].R = 1;
	SIU.GPDO[61].R = 1;
	SIU.GPDO[59].R = 1;
	SIU.GPDO[11].R = 1;
  }   
  else 
  {
	// all LEDs are on
	SIU.GPDO[9].R = 0;
	SIU.GPDO[42].R = 0;
	SIU.GPDO[13].R = 0;
	SIU.GPDO[12].R = 0;
	SIU.GPDO[62].R = 0;
	SIU.GPDO[61].R = 0;
	SIU.GPDO[59].R = 0;
	SIU.GPDO[11].R = 0;	  
  }
  */
}

/********************************************************************
 *                      Interrupt Functions                         *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                Interrupts can be handled below.                  *
 ********************************************************************/  
void PITCHANNEL0() {
    /* clear flag */
    PIT.CH[0].TFLG.B.TIF = 1;
	
	// toggle LED7
	SIU.GPDO[11].R = ~SIU.GPDO[11].R;
/*	
	static int LED_TO_TOGGLE  = 0;
	switch(LED_TO_TOGGLE)
	{
		case 0: SIU.GPDO[9].R = ~SIU.GPDO[9].R;
				LED_TO_TOGGLE = 1;
				break;
		case 1: SIU.GPDO[42].R = ~SIU.GPDO[42].R;
				LED_TO_TOGGLE = 2;
				break;
		case 2: SIU.GPDO[13].R = ~SIU.GPDO[13].R;
				LED_TO_TOGGLE = 3;
				break;
		case 3: SIU.GPDO[12].R = ~SIU.GPDO[12].R;
				LED_TO_TOGGLE = 4;
				break;
		case 4: SIU.GPDO[62].R = ~SIU.GPDO[62].R;
				LED_TO_TOGGLE = 5;
				break;
		case 5: SIU.GPDO[61].R = ~SIU.GPDO[61].R;
				LED_TO_TOGGLE = 6;
				break;
		case 6: SIU.GPDO[59].R = ~SIU.GPDO[59].R;
				LED_TO_TOGGLE = 7;
				break;
		case 7: SIU.GPDO[11].R = ~SIU.GPDO[11].R;
				LED_TO_TOGGLE = 0;
				break;
	}
	*/
}

void PITCHANNEL1() {
    /* clear flag */
    PIT.CH[1].TFLG.B.TIF = 1;
}

/********************************************************************
 *                   Interrupt Vector Table                         *
 *                                                                  *
 *                 Don't touch anything below!                      *
 ********************************************************************/
#pragma interrupt Ext_Isr
#pragma section IrqSect RX address=0x040
#pragma use_section IrqSect Ext_Isr

void Ext_Isr() {
    switch(INTC.IACKR.B.INTVEC)
    {
        case 59:
            /* Timer Interrupt */
            PITCHANNEL0();
            break;
        case 60:
            /* Timer Interrupt */
            PITCHANNEL1();
            break;            
        default:
            break;
    }
    /* End of Interrupt Request */
    INTC.EOIR.R = 0x00000000;
}
