#ifndef _timers_H
#define _timers_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void Timer0_init(void);
void write16bitTMR0val(unsigned int tmp);
unsigned char get8LSB_TMR0(void);
unsigned char get8MSB_TMR0(void);

#endif
