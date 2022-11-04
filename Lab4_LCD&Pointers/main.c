// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
//#include <stdio.h>
#include "LCD.h"
#include "ADC.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {
    LCD_Init();  
    ADC_init();
    
    unsigned char voltage;
    char display_voltage [4]; // string to display
    char *ptr;  //set pointer to first element of string
    
    while (1) {

        ptr = display_voltage; // have to reassign this or it wont work
        voltage = ADC_getval();
        
        ADC2String(ptr, voltage); //resulting string stored in display_voltage
        LCD_sendstring("      ");
        LCD_sendstring(display_voltage);
        LCD_setline(1); //so it overwrites
        __delay_ms(1000);

    }

}

