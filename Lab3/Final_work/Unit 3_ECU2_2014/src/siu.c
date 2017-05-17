#include "jdp.h"

void SIUInit(void) {
    // CAN TX Pin
    SIU.PCR[16].B.PA = 1;
    // Output Buffer
    SIU.PCR[16].B.OBE = 0;

    // CAN RX Pin
    SIU.PCR[17].B.PA = 1;    
    // Input Buffer
    SIU.PCR[17].B.IBE = 1;

    // set potentiometer as analog input
    SIU.PCR[65].B.APC = 1;
    SIU.PCR[65].B.IBE = 1;
    // temperature sensor
    SIU.PCR[66].B.APC = 1;
    SIU.PCR[66].B.IBE = 1;
    // ANA IN1
    SIU.PCR[33].B.APC = 1;
    SIU.PCR[33].B.IBE = 1;

    // set buttons and switches as  digital input
    SIU.PCR[0].R = 0x100;       // BT6
    SIU.PCR[1].R = 0x100;       // BT5
    SIU.PCR[2].R = 0x100;       // SW4
    SIU.PCR[3].R = 0x100;       // SW3
    SIU.PCR[4].R = 0x100;       // SW2
    SIU.PCR[44].R = 0x100;      // SW1
    
    // set LEDs as digital output
    SIU.PCR[9].R  = 0x200;      // D0
    SIU.PCR[42].R = 0x200;      // D1
    SIU.PCR[13].R = 0x200;      // D2
    SIU.PCR[12].R = 0x200;      // D3
    SIU.PCR[62].R = 0x200;      // D4
    SIU.PCR[61].R = 0x200;      // D5
    SIU.PCR[59].R = 0x200;      // D6
    SIU.PCR[11].R = 0x200;      // D7

    // switch off LEDs (low active)
    SIU.GPDO[9].R  = 0x1;
    SIU.GPDO[42].R = 0x1;
    SIU.GPDO[13].R = 0x1;
    SIU.GPDO[12].R = 0x1;
    SIU.GPDO[62].R = 0x1;
    SIU.GPDO[61].R = 0x1;   
    SIU.GPDO[59].R = 0x1;
    SIU.GPDO[11].R = 0x1;
}