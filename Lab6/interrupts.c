#include <xc.h>
#include "interrupts.h"
#include "rc_servo.h"
#include "timers.h"
char temp;


/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
    PIE0bits.TMR0IE = 1; //enable interrupt for Timer0
    IPR0bits.TMR0IP = 1; //Interrupt priority for Timer0??
    
    PIE4bits.RC4IE=1; // receive interrupt ??
    
    INTCONbits.PEIE = 1; // Toggle peripheral interrupts  
    INTCONbits.IPEN=0;  //high priority only
    INTCONbits.GIE = 1; //Toggle interrupts Globally
}


/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{
    if (PIR0bits.TMR0IF)
    {
        if(LATCbits.LATC5){ //if output pin currently high
            write16bitTMR0val(65535-off_period); //set new off_period
            LATCbits.LATC5 = 0; //turn your output pin off here
        } else {
            write16bitTMR0val(65535-on_period);  //set new on_period
            LATCbits.LATC5 = 1; //turn your output pin on here
        }
    }
    PIR0bits.TMR0IF=0; 
}


