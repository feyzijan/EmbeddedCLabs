#include <xc.h>
#include "LCD.h"
#include <stdio.h>

/************************************
 * Function to toggle LCD enable bit on then off
 * when this function is called the LCD screen reads the data lines
************************************/
void LCD_E_TOG(void)
{
    LCD_E = 1; //turn the LCD enable bit on   
	__delay_us(2); //wait a short delay
    LCD_E = 0; //turn the LCD enable bit off again
}

/************************************
 * Function to set the 4-bit data line levels for the LCD
************************************/
void LCD_sendnibble(unsigned char number)
{
	//set the data lines )
    LCD_DB7 = number >>3 & 1;
    LCD_DB6 = number >>2 & 1;
    LCD_DB5 = number >>1 & 1;
    LCD_DB4 = number & 1;
    
    LCD_E_TOG();			//toggle the enable bit to instruct the LCD to read the data lines
    __delay_us(5);      //Delay 5uS
}

/************************************
 * Function to send full 8-bit commands/data over the 4-bit interface
 * high nibble (4 most significant bits) are sent first, then low nibble sent
************************************/
void LCD_sendbyte(unsigned char Byte, char type)
{
    // set RS pin whether it is a Command (0) or Data/Char (1) using type argument
    LCD_RS = type; 
    
    // send high bits of Byte using LCDout function
    LCD_sendnibble(Byte >> 4);
    
    // send low bits of Byte using LCDout function
	LCD_sendnibble(Byte & 0b00001111);
    
    __delay_us(50);               //delay 50uS (minimum for command to execute)
}

/************************************
 * Function to initialise the LCD after power on
************************************/
void LCD_Init(void)
{

    //Define LCD Pins as Outputs and set all pins to low
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC2=0;
    TRISBbits.TRISB3=0;
    TRISBbits.TRISB2=0;
    TRISEbits.TRISE3=0;
    TRISEbits.TRISE1=0;
    
    LCD_RS = 0; 
    LCD_E = 0;
    LCD_DB4 = 0;
    LCD_DB5 = 0;
    LCD_DB6  = 0;
    LCD_DB7 = 0;
    
    //Initialisation sequence code
    __delay_ms(100);
    LCD_sendnibble(0b0011); // Function set
    
    LCD_sendbyte(0b00101000, 0); // Function set
    LCD_sendbyte(0b00101000, 0); // Function set
    
    LCD_sendbyte(0b00001000, 0); // Display off, cursor off, blink off
    LCD_sendbyte(0b00000001, 0); // Display clear
    __delay_ms(5);
    LCD_sendbyte(0b00000110, 0); // Entry Mode Set: cursor go right, dont shift screen
    
    LCD_sendbyte(0b00001100, 0); // turn display back on  + cursor and blink off
    
	// follow the sequence in the GitHub Readme picture for 4-bit interface.
	// first Function set should be sent with LCD_sendnibble (the LCD is in 8 bit mode at start up)
    
	// after this use LCD_sendbyte to operate in 4 bit mode

	//remember to turn the LCD display back on at the end of the initialisation (not in the data sheet)
}

/************************************
 * Function to set the cursor to beginning of line 1 or 2
************************************/
void LCD_setline (char line)
{
    if (line == 1) {
    //Send 0x80 - 8th bit- set line to 1 (0x00 ddram address)
    LCD_sendbyte(0b10000000, 0); // set ddram address 00
    }
    
    if(line == 2) {
        //Send 0xC0 -8th adn 7th bit- to set line to 2 (0x40 ddram address)
        LCD_sendbyte(0b11000000, 0); // set ddram address 40
    }
   
}





/************************************
 * Function to send string to LCD screen
************************************/
void LCD_sendstring(char *string)
{
	while(*string != 0){  // While data pointed to isn?t 0x00 (strings in C must end with a NULL byte) 
		LCD_sendbyte(*string++,1); 	//Send out current byte pointed to and increment pointer
	}
}

/************************************
 * Function to scroll through the LCD screen
************************************/
void LCD_scroll(void)
{
    for(int i = 0; i< 24; i++ ){
    LCD_sendbyte(0b00011000,0); // Shift display left to scroll (1, 1/0: Display/Cursor, 1/0: Right/Left)
    __delay_ms(400);
    }
    
    
}

/************************************
 * Function takes a ADC value and works out the voltage to 2 dp
 * the result is stored in buf as ascii text ready for display on LCD
 * Note result is stored in a buffer using pointers, it is not sent to the LCD
************************************/
void ADC2String(char *ptr, unsigned char voltage){
	//code to calculate the inegeter and fractions part of a ADC value
	// and format as a string using sprintf (see GitHub readme)
    
    unsigned char int_part = voltage/77; // i.e. 255 / 3.3V = 77
    unsigned char frac_part=(voltage*100)/77 - int_part*100;
    
    sprintf(ptr,"%d.%02d ",int_part,frac_part);
 
}

void LCD_clear(){
    LCD_sendbyte(0b00000001, 0); // Display clear
    __delay_ms(5);
}
