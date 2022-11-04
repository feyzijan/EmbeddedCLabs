#ifndef _ADC_H
#define _ADC_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void ADC_init(void);
unsigned int ADC_getval(void);

#endif
