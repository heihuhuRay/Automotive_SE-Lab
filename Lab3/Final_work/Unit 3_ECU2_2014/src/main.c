// header file for all registers
#include "jdp.h"

void can_send(int buffer, int std_id, int ide, char dataB0, char dataB1, int length);

#define LOWBITS(a) (0b0011111111) & a
#define HIGHBITS(a) (0b0000000011) & (a >> 8)
#define COMP_VALUE(a, b) ((b << 8) |  a)
#define DEBUG 0
#if DEBUG
	#define LOG(a) a
#else
	#define LOG(a)
#endif 

int ECU3_count = 0;
int count = 0;
int light_status[7] = {0};
int light_value = 0;
int flag = 0;

void can_send(int buffer, int std_id, int ide, char dataB0, char dataB1, int length)
{
	CAN_0.BUF[buffer].ID.B.STD_ID = std_id;
	CAN_0.BUF[buffer].CS.B.IDE = ide;
	CAN_0.BUF[buffer].CS.B.RTR = 0;
	CAN_0.BUF[buffer].DATA.B[0]= dataB0;
	CAN_0.BUF[buffer].DATA.B[1]= dataB1;
	CAN_0.BUF[buffer].DATA.B[2]=0;
	CAN_0.BUF[buffer].DATA.B[3]=0;
	CAN_0.BUF[buffer].DATA.B[4]=0;
	CAN_0.BUF[buffer].DATA.B[5]=0;
	CAN_0.BUF[buffer].DATA.B[6]=0;
	CAN_0.BUF[buffer].DATA.B[7]=0;
	CAN_0.BUF[buffer].CS.B.LENGTH = 8;
	CAN_0.BUF[buffer].CS.B.CODE = 0b1100;
}


void CANERR(void) {
    CAN_0.ESR.B.ERRINT = 1;
}

void CANBOFF(void) {
    CAN_0.ESR.B.BOFFINT = 1;
}

void CANWAK(void) {
    CAN_0.ESR.B.WAKINT = 1;
}

void CANSEND0(void) {
    CAN_0.IFRL.B.BUF08I = 1;
    CAN_0.IFRL.B.BUF09I = 1;
    CAN_0.IFRL.B.BUF10I = 1;
    CAN_0.IFRL.B.BUF11I = 1;
}

void CANSEND1(void) {
    CAN_0.IFRL.B.BUF12I = 1;
    CAN_0.IFRL.B.BUF13I = 1;
    CAN_0.IFRL.B.BUF14I = 1;
    CAN_0.IFRL.B.BUF15I = 1;
}

void CANRCV0(void)
{
	CAN_0.IFRL.B.BUF00I = 1;    
	CAN_0.IFRL.B.BUF01I = 1;    
	CAN_0.IFRL.B.BUF02I = 1;    
	CAN_0.IFRL.B.BUF03I = 1;

	switch(CAN_0.BUF[0].ID.B.STD_ID) {
		case 0x404 : 
			/* ECU3 is alive. Clear counter */
			ECU3_count=0;
			LOG(LED0 = ~LED0);
	}
	switch(CAN_0.BUF[1].ID.B.STD_ID) {
		case 0x402 :
			/* Light state recieved from ECU2 */

			light_status[0] = CAN_0.BUF[1].DATA.B[0] & 0x1;
			light_status[1] = CAN_0.BUF[1].DATA.B[0] & 0x2;
			light_status[2] = CAN_0.BUF[1].DATA.B[0] & 0x4;
			LOG(LED1 = ~LED1);
	}
        switch(CAN_0.BUF[2].ID.B.STD_ID) {
                case 0x503 :
                        /* Light state recieved from ECU2 */

                        light_status[3] = CAN_0.BUF[2].DATA.B[0] & 0x1;
                        light_status[4] = CAN_0.BUF[2].DATA.B[0] & 0x2;
                        light_status[5] = CAN_0.BUF[2].DATA.B[0] & 0x4;
                        LOG(LED1 = ~LED1);
        }

	switch(CAN_0.BUF[3].ID.B.STD_ID) {
                case 0x101 :
                        /* Light value recieved from ECU0 */
                        light_value = COMP_VALUE(CAN_0.BUF[3].DATA.B[0], CAN_0.BUF[3].DATA.B[1]);;
                        LOG(LED0 = ~LED0);
        }

	CAN_0.BUF[0].ID.B.STD_ID = CAN_0.BUF[1].ID.B.STD_ID = CAN_0.BUF[2].ID.B.STD_ID = CAN_0.BUF[3].ID.B.STD_ID = 0;
}

void CANRCV1(void)
{
    CAN_0.IFRL.B.BUF04I = 1;
    CAN_0.IFRL.B.BUF05I = 1;
    CAN_0.IFRL.B.BUF06I = 1;
    CAN_0.IFRL.B.BUF07I = 1;
}

void PITCHANNEL0() 
{
    // clear timer flag
    int present = 0, light_val = 0;
    char sw1, sw2;

    PIT.CH[0].TFLG.B.TIF = 1;
    count++;
    ECU3_count++;
    flag = 1;
}

void PITCHANNEL1() 
{
    // clear timer flag
    PIT.CH[1].TFLG.B.TIF = 1;
}


void main(void)
{
    int present = 0, light_val = 0;
    char mode;

    Init();
    PIT_ConfigureTimer(0, 100);
    PIT_StartTimer(0);
//    PIT_ConfigureTimer(1, 400);
//    PIT_StartTimer(1);

    CAN_0.BUF[0].ID.B.STD_ID= 0x404 ;
    CAN_0.BUF[1].ID.B.STD_ID= 0x402 ;
    CAN_0.BUF[2].ID.B.STD_ID= 0x503 ;
    CAN_0.BUF[3].ID.B.STD_ID= 0x101 ;

    CAN_0.RXIMR[0].R = 0b00011111111111111111111111111111;
    CAN_0.RXIMR[1].R = 0b00011111111111111111111111111111;
    CAN_0.RXIMR[2].R = 0b00011111111111111111111111111111;
    CAN_0.RXIMR[3].R = 0b00011111111111111111111111111111;

    for(;;)
    {
	if(flag) {
	    if(ECU3_count > 8)
		present = 1;

	    if(count % 2 == 0) {

	       can_send(8, 0x303, 0, 0, 0, 8);

	       /* present = 0 -> ECU 1 is present
	          present = 1 -> ECU 1 is not present */
	       if(present) {
		   LED7 = ~LED7; 
		    can_send(9, 0x304, 0, 0, 0, 8);
	        } else
		    LED7 = 1;
	    }
	    ADC_StartConversion();
	    can_send(10, 0x302, 0, (char) LOWBITS(POT), (char) HIGHBITS(POT), 8);
	
	    mode = SIU.GPDI[44].R; // SW1 used to toggle between automatic and manual mode

	    /* mode -1 -> Manual mode 
	       mode -0 -> Automatic mode */
	    if(mode) {
		LED0 = light_status[0];   // left indicator
		LED1 = light_status[1];   // right indicator
		LED2 = light_status[2];   // hazard light
		LED3 = light_status[3];   // high beam
		LED4 = light_status[4];   // low beam
		LED5 = light_status[5];   // parking light
	    } else {
		LED0 = LED1 = LED2 = LED3 = 1;
		if(light_value < 512) {
			LED4 = LED5 = 0;
		}
	    }
	    flag = 0;
	}
    }
}


#pragma interrupt Ext_Isr
#pragma section IrqSect RX address=0x040
#pragma use_section IrqSect Ext_Isr

void Ext_Isr() {
    switch(INTC.IACKR.B.INTVEC)
    {
        case 59:
            // Timer Interrupt
            PITCHANNEL0();
            break;
        case 60:
            // Timer Interrupt
            PITCHANNEL1();
            break;            
        case 65:
            // CAN Error Interrupt
            CANERR();
            break;
        case 66:
            // CAN Bus Off Interrupt
            CANBOFF();
            break;
        case 67:
            // CAN Wakeup Interrupt
            CANWAK();
        case 68:
            // CAN Interrupt for MBs 0-3
            CANRCV0();
            break;
        case 69:
            // CAN Interrupt for MBs 4-7
            CANRCV1();
            break;
        case 70:
            // CAN Interrupt for MBs 8-11
            CANSEND0();
            break;
        case 71:
            // CAN Interrupt for MBs 12-15
            CANSEND1();
            break;
        default:
            break;
    }
    // End of Interrupt Request
    INTC.EOIR.R = 0x00000000;
}