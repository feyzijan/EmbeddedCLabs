#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "ADC.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
	unsigned int voltage=0; // to store voltage reading
    unsigned int voltage_disp; // the value displayed in the LED
    unsigned int max_voltage = 0; // maximum voltage in the past 1 s
    
    
    // Will use below variables to determine when to decrement the Max value
    unsigned int count = 0;
    // Change count_max and delay times to configure speed 
    // Max value decrements by one LED every:  delay_time * count_max ms
    unsigned int count_max = 10;
    
    // initialise LED and ADC
    LEDarray_init(); 
    ADC_init();
    __delay_ms(100);
    
    // Calibration variables:
    unsigned int darkness = 16; // reading when thumb is pressed
    unsigned int ambient = 104; // reading in ambient light
    unsigned int bin = (ambient-darkness) / 7; // length of the 7 intervals for the intensity meters
    // #interval is 7 so values below and above thresholds are in the 0th and 8th interval
    // For precision make (ambient-darkness)%7 = 0 
    

    while (1) 
    {   
        voltage = ADC_getval(); // take reading
        voltage_disp = 1; // assign 1 so this can later be raised to powers of 2
        
        // Below we convert values in the nth interval to 2^n -1 and displaying them in LED in binary
        // First assign voltage = n where n is the interval
        
        if (voltage < darkness) // no display, n=0, display nothing
        {
            voltage = 0;
            voltage_disp = 0; 
        } 
        
        else 
        {   
            if (voltage > ambient)
            {
                voltage = 8; // max interval   
            }
            else 
            {
                voltage = (voltage - darkness) / (bin) + 1; // assign to interval between 0-7
            }
        
            // pick correct binary number to display by performing voltage_disp = 2^n
            for (voltage; voltage >0; --voltage)
            {
                voltage_disp *= 2; 
            }
        }
                    
        // update max_voltage if need be
        if (voltage_disp >= max_voltage) // current voltage exceeds max
        {
            max_voltage = voltage_disp; 
            count = 0;
        } 
        else if (count == count_max) { // max voltage displayed for 1 second
            max_voltage >>= 1; // right shift(decrement by one LED)
            count = 0;
        }
                
        
        if (voltage_disp == 0) {
            // separate case for 0 so we don't overflow voltage_disp
            LEDarray_disp_PPM(voltage_disp, max_voltage); 
        } else { 
            // Pass in (voltage_disp*2-1) so all LEDs up to nth LED light up
            LEDarray_disp_PPM(voltage_disp*2 -1, max_voltage);
        }
            
            
        __delay_ms(100); // buffer time
        count += 1; // increment count

    }
    
}