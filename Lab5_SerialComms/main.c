// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
//#include <stdio.h>
#include "LCD.h"
#include "serial.h"
#include "ADC.h"
#include "timers.h"
#include "interrupts.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {
    LCD_Init();  
    ADC_init();
    initUSART4();
    Interrupts_init();
    Timer0_init();
    
    unsigned char voltage;
    char voltage_string[5]; // example: " 1.24"

    while (1) {
        
        //send voltage readings every second
        if(timer_flag) { //1 second has passed 
            voltage = ADC_getval(); //read voltage
            ADC2String(voltage_string,voltage); //convert reading to string

            TxBufferedString(voltage_string); // writes string to buffer
            sendTxBuf(); //interrupt will handle the rest
            
            timer_flag =0;
        }
        
        if(isDataInRxBuf()){ //if data is read display it in LCD
            LCD_clear();
            while(isDataInRxBuf()) {
                LCD_sendbyte(getCharFromRxBuf(), 1);
            } 
        }
        

    }
}

