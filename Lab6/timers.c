#include <xc.h>
#include "timers.h"

/************************************
 * Function to set up timer 0
************************************/
void Timer0_init()
{
    T0CON1bits.T0CS=0b010; // Fosc/4 = 16Mhz
    T0CON1bits.T0ASYNC=1; 
    T0CON1bits.T0CKPS=0b0011 ; // Pre-scaler 1:8 - Must be 5<PS<142 a

    T0CON0bits.T016BIT=1; //16bit mode
    
    // Initialise timer so it overflows after 20 ms
    TMR0H = 0b01100011;            
    TMR0L = 0b10111111;
    
    IPR0bits.TMR0IP = 1; //priority low
    T0CON0bits.T0EN=1;	//start the timer

}

/************************************
 * Function to write a full 16bit timer value
 * Note TMR0L and TMR0H must be written in the correct order, or TMR0H will not contain the correct value
************************************/
void write16bitTMR0val(unsigned int tmp)
{
    TMR0H=tmp>>8; //MSB written
    TMR0L=tmp; //LSB written and timer updated
}


unsigned char get8MSB_TMR0(void)
{
    TMR0L;
    return TMR0H;
}

unsigned char get8LSB_TMR0(void)
{
    return TMR0L;
}