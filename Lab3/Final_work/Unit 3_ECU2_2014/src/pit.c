#include "jdp.h" 

void PIT_ConfigureTimer(char timerChannel, unsigned int loadValue)
{
    PIT.CH[timerChannel].LDVAL.B.TSV = loadValue*16000;
}

void PIT_StartTimer(char timerChannel)
{
    // Timer einschalten
    PIT.CH[timerChannel].TCTRL.B.TEN = 1;    
}

void PIT_StopTimer(char timerChannel)
{
    // Timer ausschalten
    PIT.CH[timerChannel].TCTRL.B.TEN = 0;
    //PIT.CH[timerChannel].LDVAL.B.TSV = 0x00000000;
}

void PITInit()
{
    // Takt für PIT einschalten
    PIT.PITMCR.B.MDIS = 0;
    // Timer laufen im Debugmode weiter
    PIT.PITMCR.B.FRZ = 0;
    // Wert von dem gezählt wird
    PIT.CH[0].LDVAL.B.TSV = 0;
    // Interruptflag zurücksetzen
    PIT.CH[0].TFLG.B.TIF = 1;
    // enable interrupts
    PIT.CH[0].TCTRL.B.TIE = 1;
    // Timer einschalten
    PIT.CH[0].TCTRL.B.TEN = 0;

    // Wert von dem gezählt wird
    PIT.CH[1].LDVAL.B.TSV = 0;
    // Interruptflag zurücksetzen
    PIT.CH[1].TFLG.B.TIF = 1;
    // enable interrupts
    PIT.CH[1].TCTRL.B.TIE = 1;
    // Timer einschalten
    PIT.CH[1].TCTRL.B.TEN = 0;
}