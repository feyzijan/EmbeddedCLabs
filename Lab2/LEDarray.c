#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers as 0 (output) for pins connected to LED array
	TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    
    //set initial output LAT values to 0 (led off)
    
    Pin0 = 0; //most significant digit
    Pin1 = Pin2 = Pin3 = Pin4 = Pin5 = Pin6 = Pin7 = 0; 
    Pin8 = 0; //least significant digit
    
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/


void LEDarray_disp_bin(unsigned int number)
{
	//Use Bit Masks to determine which pins should be turned on 
    
    Pin0 = (number & 0b100000000) >> 8; // > 255; 
    Pin1 = (number & 0b010000000) > 127;
    Pin2 = (number & 0b001000000) > 63;
    Pin3 = (number & 0b000100000) > 31;
    Pin4 = (number & 0b000010000) > 15;
    Pin5 = (number & 0b000001000) > 7;
    Pin6 = (number & 0b000000100) > 3;
    Pin7 = (number & 0b000000010) > 1;
    Pin8 = (number & 0b000000001) > 0;
    
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{
    if (number >= 10) { 

        unsigned int disp_val = 1;
        number /=10; // number is an integer hence 10-19 -> 1, 20-29 -> 2 etc..

        // let disp_val equal  2^number and pass that into the display_bin function 
        for (number; number >0; --number){
            disp_val *= 2; 
        }

        LEDarray_disp_bin(disp_val); 	//display value on LED array
    } 
}


/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max)
{
	unsigned int disp_val;

    // use bitwise OR so resulting value lights all LEDS that would light up 
    // individually by max and current voltages
    disp_val = cur_val | max;
    
	LEDarray_disp_bin(disp_val);	//display value on LED array
}


// Function that initialises LED when RF2 button is pressed
void LEDarray_button_init(void)
{
    TRISFbits.TRISF2=1; //set TRIS value for pin to 1 (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin  
    
    while(1) 
    {
        // initialise LED when button is pressed then exit function
        if (!PORTFbits.RF2) 
        {
            LEDarray_init(); 
            break;
        }  
    }
    
    
}
