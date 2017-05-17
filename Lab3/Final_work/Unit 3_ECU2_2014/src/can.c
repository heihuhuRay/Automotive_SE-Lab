#include "jdp.h"

void CANInit(void)
{
    //int i;  

    // clock 16Mhz oszi
    CAN_0.CR.B.CLKSRC = 1;    
    
    // Enable CAN
    CAN_0.MCR.B.MDIS = 0;
    // Backwards Compatibility enabled
    CAN_0.MCR.B.BCC = 1;    
    // Warning Interrupt enabled
    CAN_0.MCR.B.WRNEN = 1;    
    // self reception disabled
    CAN_0.MCR.B.SRXDIS = 1; 
    // FIFO disabled
    CAN_0.MCR.B.FEN = 0;
    // Abort mechanism enabled
    CAN_0.MCR.B.AEN = 1; 
    // Local Priority enabled
    CAN_0.MCR.B.LPRIO_EN = 0;
    // maximale Anzahl von Messagebuffern (0+1)
    CAN_0.MCR.B.MAXMB = 16;

    // Propagation Segment
    CAN_0.CR.B.PROPSEG = 2;
    // PSEG1
    CAN_0.CR.B.PSEG1 = 1;    
    // PSEG2
    CAN_0.CR.B.PSEG2 = 1;
    // Resync Jump Width
    CAN_0.CR.B.RJW = 0;
    // Prescaler
    CAN_0.CR.B.PRESDIV = 15;
    // Der MB mit der geringsten Nummer wird zuerst versendet
    CAN_0.CR.B.LBUF = 1;

    // Loop Back disabled
    CAN_0.CR.B.LPB = 0;
/*
    // FIFO Buffer Standard Frame
    CAN_0.RXFIFO.CS.B.IDE = 0;
    // FIFO SRR
    CAN_0.RXFIFO.CS.B.SRR = 0;
    // FIFO Remote Frame
    CAN_0.RXFIFO.CS.B.RTR = 0;
    // FIFO Länge
    CAN_0.RXFIFO.CS.B.LENGTH = 8;
    // FIFO ID Table
    for(i=0; i<8; i++)
        CAN_0.RXFIFO.IDTABLE[i].R = 0;    
*/
    // Set Mask Register here
    // Global Mask Register for FIFO (except IDT 6 and 7) 
    // or for all MB (except 14 und 15)
    CAN_0.RXGMASK.R = 0x00000000;
    // Mask for FIFO ID Table 6 or MB 14
    CAN_0.RX14MASK.R = 0x00000000;
    // Mask for FIFO Id Table 7 or MB 15
    CAN_0.RX15MASK.R = 0x00000000;
    
    // Bus Off Interrupt
    CAN_0.CR.B.BOFFMSK = 1;    
    // Error Mask Interrupt
    CAN_0.CR.B.ERRMSK = 1;
    // Transmit Warning Interrupt
    CAN_0.CR.B.TWRNMSK = 1;
    // Receive Warning Interrupt
    CAN_0.CR.B.RWRNMSK = 1;

    // enable Wake Up interrupt
    CAN_0.MCR.B.WAKMSK = 1;

    // enable all mb interrupts
    CAN_0.IMRL.R = 0xFFFFFFFF;
    // clear all mb interrupts
    CAN_0.IFRL.R = 0xFFFFFFFF;

    // CAN leaves Freeze Mode
    CAN_0.MCR.B.HALT = 0;
    
    CAN_MessageBufferInit();
}