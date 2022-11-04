#ifndef _LCD_H
#define _LCD_H

#include <xc.h>

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

//Define Pins Used with the LCD Screen
#define LCD_RS LATCbits.LATC6
#define LCD_E LATCbits.LATC2
#define LCD_DB4 LATBbits.LATB3
#define LCD_DB5 LATBbits.LATB2
#define LCD_DB6 LATEbits.LATE3
#define LCD_DB7 LATEbits.LATE1


void LCD_E_TOG(void);
void LCD_sendnibble(unsigned char number);
void LCD_sendbyte(unsigned char Byte, char type);
void LCD_Init(void);
void LCD_setline (char line);	
void LCD_sendstring(char *string);
void LCD_scroll(void);
void LCD_clear(void);
void ADC2String(char *buffer, unsigned char voltage);

#endif
