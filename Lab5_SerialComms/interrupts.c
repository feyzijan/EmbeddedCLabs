#include <xc.h>
#include "interrupts.h"
#include "serial.h"

char temp;


/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
    PIE0bits.TMR0IE = 1; //enable Timer0 interrupt
    PIE4bits.RC4IE=1; // recieve interrupt
    INTCONbits.PEIE = 1; // Toggle peripheral interrupts  
    INTCONbits.GIE = 1; //Toggle interrupts Globally
    
}


/************************************
 * High priority interrupt service routine
 * Send out LDR readings when TMR0 overflows(1s)
 ************************************/

void __interrupt(high_priority) HighISR()
{
    // interrupt for reading data
    if(PIR4bits.RC4IF){
        putCharToRxBuf(getCharSerial4()); //read char and put in buffer
    }

    //interrupt for transmitting data
    if(PIR4bits.TX4IF){
        sendCharSerial4(getCharFromTxBuf()); // read buffer and send
        if(!isDataInTxBuf()) {
            PIE4bits.TX4IE = 0; //disable interrupt if buffer is empty
        }
    }
    
    if(PIR0bits.TMR0IF == 1) { //1 second has passed 
            timer_flag = 1;
            
            TMR0L = 0b00001000;
            PIR0bits.TMR0IF = 0; // clear interrupt flag
        }
    
    
}








//Timer 0 Low priority interrupt //
/*
void __interrupt(low_priority) LOWISR(){ 
    sendCharSerial4('j');
    
    if(PIR0bits.TMR0IF == 1) { // check interrupt flag
            TMR0H = 0;    
            TMR0L = 0;  
            PIR0bits.TMR0IF = 0; // clear interrupt flag
       }  
}
 */

