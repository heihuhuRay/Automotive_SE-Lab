#include "jdp.h"

void SIU_Init(void) {
  /***************************************************************************
   *                                  Task 1                                 *
   *    Please enter the PCR register numbers and initialitation code here   *
   ***************************************************************************/
  /* LEDs */
   SIU.PCR[9].R = 0x0200;    /* LED0 */
   SIU.PCR[42].R = 0x0200;    /* LED1 */
   SIU.PCR[13].R = 0x0200;    /* LED2 */
   SIU.PCR[12].R = 0x0200;    /* LED3 */
   SIU.PCR[62].R = 0x0200;    /* LED4 */
   SIU.PCR[61].R = 0x0200;    /* LED5 */
   SIU.PCR[59].R = 0x0200;    /* LED6 */
   SIU.PCR[11].R = 0x0200;    /* LED7 */
   SIU.PCR[11].R = 0x0200;    /* LED7 */
  /* ... */

  /***************************************************************************
   *                                  Task 2                                 *
   *                       Analog inputs configuration                       *
   ***************************************************************************/  
   //ANA IN1 PC1 External analog input
   SIU.PCR[33].R = 0x2500; // IN1 Analog input
   //POT PE1 Potentiometer analog input, min=0V, max=VDD
   SIU.PCR[65].R = 0x2500; // POT Analog input
  /* 
  The light sensor is connected to the “ANA IN1” input pin

  The value of the sensor, which is converted by the ADC module of the controller, is stored in the register
“ADC_0.CDR[2].B.CDATA”....
  The controller pin, which is mapped to the ADC module, has to be configured for analog input which
can be done by writing “0x2500” to the corresponding “PCR” register.
   */

  /***************************************************************************
   *                                  Task 3                                 *
   *                            Buttons & switches                           *
   ***************************************************************************/    
   // A button can be configured as input by writing “0x0100” 
   SIU.PCR[1].R = 0x0100;    /* BT5 */
   SIU.PCR[0].R = 0x0100;   /* BT6 */
   SIU.PCR[44].R = 0x0100;   /* SW1 */
  /* ... */
}