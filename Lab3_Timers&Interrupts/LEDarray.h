#ifndef _LEDarray_H
#define _LEDarray_H

#include <xc.h>

#define _XTAL_FREQ 64000000

// define lat bits to refer to pins more easily
#define Pin0 LATGbits.LATG0
#define Pin1 LATGbits.LATG1
#define Pin2 LATAbits.LATA2
#define Pin3 LATFbits.LATF6
#define Pin4 LATAbits.LATA4
#define Pin5 LATAbits.LATA5 
#define Pin6 LATFbits.LATF0
#define Pin7 LATBbits.LATB0   
#define Pin8 LATBbits.LATB1

//function prototypes
void LEDarray_init(void);
void LEDarray_button_init(void); 
void LEDarray_disp_bin(unsigned int number);
void LEDarray_disp_dec(unsigned int number);
void LEDarray_disp_PPM(unsigned int number, unsigned int max);


#endif
