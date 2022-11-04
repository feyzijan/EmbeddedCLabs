#ifndef _timers_H
#define _timers_H

#include <xc.h>

#define _XTAL_FREQ 64000000
// redefine TimerBits for ease of reference
#define TimerL0 TMR0Lbits.TMR0L0
#define TimerL1 TMR0Lbits.TMR0L1
#define TimerL2 TMR0Lbits.TMR0L2
#define TimerL3 TMR0Lbits.TMR0L3
#define TimerL4 TMR0Lbits.TMR0L4
#define TimerL5 TMR0Lbits.TMR0L5
#define TimerL6 TMR0Lbits.TMR0L6
#define TimerL7 TMR0Lbits.TMR0L7
#define TimerH0 TMR0Hbits.TMR0H0
#define TimerH1 TMR0Hbits.TMR0H1
#define TimerH2 TMR0Hbits.TMR0H2
#define TimerH3 TMR0Hbits.TMR0H3
#define TimerH4 TMR0Hbits.TMR0H4
#define TimerH5 TMR0Hbits.TMR0H5
#define TimerH6 TMR0Hbits.TMR0H6
#define TimerH7 TMR0Hbits.TMR0H7

void Timer0_init(void);
unsigned int get8MSB_TMR0(void);
unsigned int get8LSB_TMR0(void);

#endif
