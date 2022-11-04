#include <xc.h>
#include "timers.h"

/************************************
 * Function to set up timer 0
************************************/
void Timer0_init()
{
    T0CON1bits.T0CS=0b100; // LFINTOSC = 31Khz
    T0CON1bits.T0ASYNC=1; 
    T0CON1bits.T0CKPS=0b0111 ; // Pre-scaler 1:128

    T0CON0bits.T016BIT=0; //16bit mode	  
    TMR0L = 0b00001000;
    IPR0bits.TMR0IP = 1; //priority low
    T0CON0bits.T0EN=1;	//start the timer
}
