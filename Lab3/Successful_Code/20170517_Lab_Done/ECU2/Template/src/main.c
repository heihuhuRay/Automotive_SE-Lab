#include "init.h"
/********************************************************************
*                          global variables                         *
********************************************************************/

/********************************************************************
*                    _____  ___  ___   ___                          *
*                   |_   _|/ _ \|   \ / _ \                         *
*                     | | | (_) | |) | (_) |                        *
*                     |_|  \___/|___/ \___/                         *
*                                                                   *
* If you need global variables define them here!                    *
********************************************************************/  
//	global variables
//	3 intervals: 400ms, 100ms, 200ms
//Message ID:	0x301, Interval:	400ms, Light States, 0 is on, 1 is off	
//Message ID:	0x302, Interval:	100ms, Non Driven Wheels Speed - 10 Bits	
//Message ID:	0x303, Interval:	200ms, Alive Signal	
//Message ID:	0x304, Interval:	200ms, Error Signal	

int int_100_arrived = 0;
int int_200_arrived = 0;
int int_400_arrived = 0;

//light_status
int light_status[7] = {0};

int second_int = 0; 

// light_mode simulated by the switch
int light_mode;

// initial value 111111, 6 bits represent 64 states: 0~63
// In manual mode the ECU receives 6 signals which represent different light states.
unsigned char light_states = 64;

// light_value: The message with ID 0x101 holds the light value.
int light_value; // 10 bits

// Check ECU3 for door_control
// initial value = 1 just for testing
int door_control_is_alive = 1;

// non_driven_wheels_speed: value between 0 and 300
int non_driven_wheels_speed;

/********************************************************************
 *                              main                                *
 ********************************************************************/
void main(void)
{
    /* board initialization */
    Init();

    /* turn off leds */
    LED0 = 1;
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED6 = 1;
    LED7 = 1; 
    
    LED0 = CAN_0.BUF[1].DATA.B[0] & 0x1;   // left indicator
    LED1 = CAN_0.BUF[1].DATA.B[0] & 0x2;   // right indicator
    LED2 = CAN_0.BUF[1].DATA.B[0] & 0x4;   // hazard light
    LED3 = CAN_0.BUF[2].DATA.B[0] & 0x1;   // high beam
    LED4 = CAN_0.BUF[2].DATA.B[0] & 0x2;   // low beam
    LED5 = CAN_0.BUF[2].DATA.B[0] & 0x4;   // parking light


/********************************************************************
*                    _____  ___  ___   ___                          *
*                   |_   _|/ _ \|   \ / _ \                         *
*                     | | | (_) | |) | (_) |                        *
*                     |_|  \___/|___/ \___/                         *
*                                                                   *
* Some configuration/initialisation must                            *
* be done outside of the for-loop....(!)                            *
********************************************************************/  

/* channel 0 and 1 of PIT timer are configured to interrupt every 100ms and 200ms respectively */
	PIT_ConfigureTimer(0, 100);
	PIT_ConfigureTimer(1, 200);
	
/* start PIT timer for channel 0 and 1 */
	PIT_StartTimer(0);
	PIT_StartTimer(1);

    /* forever */
    for(;;)
    {
    	/*
		CAN_0.BUF[0]: Light mode, 0 is on, 1 is off	
		CAN_0.BUF[1]: non_driven_wheels_speed
		CAN_0.BUF[2]: alive message
		CAN_0.BUF[3]: error message
    	*/
        light_mode = SIU.GPDI[44].R;
    
    	if(int_400_arrived) 
		{
			// when switch 1 is on - automatic mode
			if(light_mode  == 0) 
			{
				if(light_value < 512)
					LED4 = 0;   // low beam
                    LED5 = 0;   // parking light
			}
			// send light states message
			CAN_0.BUF[0].DATA.B[0] = light_states;
			CAN_0.BUF[0].CS.B.CODE = 12;
			
			int_400_arrived = 0;
		}

		/* send non driven wheels speed */
		/*Lab1_Subtask 2:
		potentiometer ---------> "ADC_0.CDR[4].B.CDATA"
		This subtask concerns with the usage of the potentiometer provided on the board. The converted
		value from the potentiometer is being stored in the register “ADC_0.CDR[4].B.CDATA”. Use this data
		register, instead of light sensor data register, with the same function (“showData( value )”).*/
        if(int_100_arrived) 
        {
        	//????????????????????????????how to map to 0-300???????????????????
			non_driven_wheels_speed = ADC_0.CDR[4].B.CDATA * 301/1024; // mapping 0-300
			CAN_0.BUF[1].DATA.B[0] = non_driven_wheels_speed;
			CAN_0.BUF[1].DATA.B[1] =  non_driven_wheels_speed >> 8;		
			CAN_0.BUF[1].CS.B.CODE = 12;// set as 12 for sending,  4 for receiving
			
			int_100_arrived = 0;
		} 
		
		if(int_200_arrived)
		{
			// send alive message
			CAN_0.BUF[2].CS.B.CODE = 12;
			
			// send error message
			if(door_control_is_alive == 0) 
			{
				CAN_0.BUF[3].CS.B.CODE = 12;
				LED7 = ~LED7;//light LED7 for warning
			} 
			else 
			{
				door_control_is_alive = 0;
				LED7 = 1;
			}
			
			int_200_arrived = 0;
		}
    }
}

/********************************************************************
 *                      Interrupt Functions                         *
 ********************************************************************/  

void PITCHANNEL0(void)
{
    int_100_arrived = 1;
	
    PIT.CH[0].TFLG.B.TIF = 1;
}

void PITCHANNEL1(void)
{
    int_200_arrived = 1;
	
	if(second_int == 1) {
		int_400_arrived = 1;
		second_int = 0;
	} else
		second_int = 1;
	
    PIT.CH[1].TFLG.B.TIF = 1;
}


void CANMB0407(void)
{
	 /********************************************************************
    *                    _____  ___  ___   ___                          *
    *                   |_   _|/ _ \|   \ / _ \                         *
    *                     | | | (_) | |) | (_) |                        *
    *                     |_|  \___/|___/ \___/                         *
    *                                                                   *
    * CAN reception is handled here                                     *
    * The following buffers are important:                              *
    * CAN_0.RXFIFO.ID.B.STD_ID: ID of received message                  *
    * CAN_0.RXFIFO.DATA.B[i]: value of data byte 'i'                    *
    * IMPORTANT: check for the flag in CAN_0.IFRL.B.BUF05I first!       *
    ********************************************************************/  
	if(CAN_0.IFRL.B.BUF05I) {
		switch(CAN_0.RXFIFO.ID.B.STD_ID) {
			case 0x101:
				light_value = (CAN_0.RXFIFO.DATA.B[1] << 8) | CAN_0.RXFIFO.DATA.B[0];
				LED0 = ~LED0;
				break;
			case 0x402:
				light_states = (light_states & 248) | CAN_0.RXFIFO.DATA.B[0];
				LED1 = ~LED1;
				break;
			case 0x503:
				light_states = (light_states & 7) | (CAN_0.RXFIFO.DATA.B[0] << 3);
				LED2 = ~LED2;
				break;
			case 0x404:
				door_control_is_alive = 1;
				LED3 = ~LED3;
				break;
		}
	}  
   
    /* clear flags as last step here! */
    /* don't change anything below! */
    CAN_0.IFRL.B.BUF04I = 1;
    CAN_0.IFRL.B.BUF05I = 1;
    CAN_0.IFRL.B.BUF06I = 1;
    CAN_0.IFRL.B.BUF07I = 1;
}



//////////////////////////////////////////////////////////////////////////////////////////////////
/* No modifications needed  below */
void CANMB0003(void)
{
/* No modifications needed here */
/* Receive interrupts are being cleared here */
    CAN_0.IFRL.B.BUF00I = 1;
    CAN_0.IFRL.B.BUF01I = 1;
    CAN_0.IFRL.B.BUF02I = 1;
    CAN_0.IFRL.B.BUF03I = 1;
}

void CANMB0811(void)
{
/* No modifications needed here */
/* transmit interrupts are being cleared here */

    CAN_0.IFRL.B.BUF08I = 1;
    CAN_0.IFRL.B.BUF09I = 1;
    CAN_0.IFRL.B.BUF10I = 1;
    CAN_0.IFRL.B.BUF11I = 1;
}

void CANMB1215(void)
{
/* No modifications needed here */
/* transmit interrupts are being cleared here */
    CAN_0.IFRL.B.BUF12I = 1;
    CAN_0.IFRL.B.BUF13I = 1;
    CAN_0.IFRL.B.BUF14I = 1;
    CAN_0.IFRL.B.BUF15I = 1;
}



/********************************************************************
 *                   Interrupt Vector Table                         *
 ********************************************************************/
#pragma interrupt Ext_Isr
#pragma section IrqSect RX address=0x040
#pragma use_section IrqSect Ext_Isr

void Ext_Isr() {
    switch(INTC.IACKR.B.INTVEC)
    {
        case 59:
            PITCHANNEL0();
            break;
        case 60:
            PITCHANNEL1();
        case 68:
            CANMB0003();
            break;
        case 69:
            CANMB0407();
            break;
        case 70:
            CANMB0811();
            break;
        case 71:
            CANMB1215();
            break;        
        default:
            break;
    }
    /* End of Interrupt Request */
    INTC.EOIR.R = 0x00000000;
}
