#include <xc.h>
#include "rc_servo.h"


/************************************
 * Function to set the on_period and off_period variables used in the ISR
 * the on_period varies linearly according to angle (-90 deg is 0.5 ms, +90 is 2.1 ms)
 * off_period is the remaining time left (calculate from on_period and T_PERIOD)
************************************/
void angle2PWM(int angle){
    on_period = ( (angle + 90) * (1600000/180) + 500000)/1000 * 2;	//0.001ms=2000 TMRbits
    off_period = T_PERIOD - on_period;
}

unsigned int ADC2Angle(unsigned char ldr_reading ) {
    if(ldr_reading <16){
        return -90;
    } else if (ldr_reading > 106){
        return 90;
    } else {
        return (int) ( (ldr_reading-16)*2 -90 );
    }
}