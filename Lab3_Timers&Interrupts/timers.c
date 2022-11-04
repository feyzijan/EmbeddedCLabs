#include <xc.h>
#include "timers.h"

/************************************
 * Function to set up timer 0
************************************/
void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Fosc/4 ( Our base oscillation frequency(Fosc) is 64 Mhz)
    T0CON1bits.T0ASYNC=1; // needed to ensure correct operation when Fosc/4 used as clock source
    T0CON1bits.T0CKPS=0b1100 ; // Prescaler = 0b1000 = 1:256 - To ensure Overflow in 1s we need exactly 1:244
    T0CON0bits.T016BIT=1;	//16bit mode	
    
    PIE0bits.TMR0IE = 1; //enable interrupt
    IPR0bits.TMR0IP = 1; //priority
    
    // Initialise the timer registers at 0 - write High-Reg first as it updates when Low-Reg is written
    TMR0H = 0;
    TMR0L = 0;
    
    T0CON0bits.T0EN=1;	//start the timer
}

/************************************
 * Function to return the full 16bit timer value
 * Note TMR0L and TMR0H must be read in the correct order, or TMR0H will not contain the correct value
************************************/
unsigned int get8MSB_TMR0(void)
{
    TMR0L;
    return TMR0H;
}

unsigned int get8LSB_TMR0(void)
{
    return TMR0L;
}
