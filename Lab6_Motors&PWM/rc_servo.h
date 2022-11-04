#ifndef _RC_servo_H
#define _RC_servo_H

#include <xc.h>

#define _XTAL_FREQ 64000000
#define T_PERIOD 40000 // TMR0H:0b10011100 TMR0L:0b01000000 

unsigned int on_period,off_period;

void angle2PWM(int angle);
unsigned int ADC2Angle(unsigned char ldr_reading );

#endif
