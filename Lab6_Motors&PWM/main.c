// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "dc_motor.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

// own branch test

void main(void){

    //Initialise Motor structs
    struct DC_motor motorL, motorR; // declare two DC_motor structures 
    motorL.power=0; 				
    motorL.direction=1; // forward
    motorL.dutyHighByte=(unsigned char *)(&PWM6DCH); // store address of PWM duty high byte
    motorL.dir_LAT=(unsigned char *)(&LATE); 	// store address of LAT
    motorL.dir_pin=4; 	// pin RE4 controls direction
    motorL.PWMperiod=199; // store PWMperiod for motor

    //same for motorR but different PWM register, LAT and direction pin
    motorR.power=0; 						
    motorR.direction=1; 					
    motorR.dutyHighByte=(unsigned char *)(&PWM7DCH);	
    motorR.dir_LAT=(unsigned char *)(&LATG); 		
    motorR.dir_pin=6; 						//pin RG6 controls direction
    motorR.PWMperiod=199; 		

    
    initDCmotorsPWM(199); 
    
    /*LEDs for debugging:
    When both LEDs flash it means the loop is just beginning
    When only one LED flashes it means it will commence the return journey */
    LATDbits.LATD7 = LATHbits.LATH3 = 0; // set initial value as off(0)
    TRISDbits.TRISD7 = TRISHbits.TRISH3 = 0;  //set pins as output (0)
    
    
    //NOTE: Modify the delay timings below based on friction of surface
    
    /*
     fullSpeedAhead(&motorL,&motorR);
    __delay_ms(2000);
    stop(&motorL,&motorR);
    __delay_ms(2000);
    fullSpeedBehind(&motorL,&motorR);
    __delay_ms(2000);
    stop(&motorL,&motorR);
     
     
     */
    
    while(1){
    
        
    }    
}
