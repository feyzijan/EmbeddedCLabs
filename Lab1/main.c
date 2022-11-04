/************************************
 * #pragma directives...
************************************/
#pragma config FEXTOSC = HS
#pragma config RSTOSC = EXTOSC_4PLL 
#pragma config WDTE = OFF        

/************************************
 * #include directives...
 ************************************/
#include <xc.h>

/************************************
 * #define directives...
 ************************************/
#define _XTAL_FREQ 64000000 

/************************************
/ main function
 * ...
************************************/
void main(void) {    
    // setup pin for output (connected to RD7 LED)
    LATDbits.LATD7=0;   //set initial output state
    TRISDbits.TRISD7=0; //set TRIS value for pin (output)
    
    // setup pin for output (connected to RH3 LED)
    LATHbits.LATH3=0;   //set initial output state
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    
    // setup pin for input (connected to button RF2)
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin  
    
    // setup pin for input (connected to button RF3)
    TRISFbits.TRISF3=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF3=0; //turn off analogue input on pin  
    
    
    while (1) { //infinite while loop - repeat forever
        
        //empty while loop (wait for either button to be pressed)
        while (PORTFbits.RF2 && PORTFbits.RF3); 
        
        // Change state of LED RD7 if button RF2 is pressed
        if (!PORTFbits.RF2) {
            LATDbits.LATD7 = !LATDbits.LATD7; //toggle LED
        } 
        
        // Change state of LED RH3 if button RF3 is pressed
        if (!PORTFbits.RF3) {
            LATHbits.LATH3 = !LATHbits.LATH3; //toggle LED
        } 
        
 
        __delay_ms(200); // call built in delay function 
    }
}