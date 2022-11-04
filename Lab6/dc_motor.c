#include <xc.h>
#include "dc_motor.h"

/* Function initialise T2 and PWM for DC motor control */
void initDCmotorsPWM(int PWMperiod){
	//initialise your TRIS and LAT registers for PWM

    // timer 2 config
    T2CONbits.CKPS=011; // 1:8 prescaler
    T2HLTbits.MODE=0b00000; // Free Running Mode, software gate only
    T2CLKCONbits.CS=0b0001; // Fosc/4

    // Tpwm*(Fosc/4)/prescaler - 1 = PTPER
    T2PR=PWMperiod; //Period reg 10kHz base period
    T2CONbits.ON=1;
    
    
    // D?recion Pins
    TRISEbits.TRISE4=0;
    TRISGbits.TRISG6=0;
    
    // COnfigure TRIS registers for output
    TRISEbits.TRISE2=0;
    TRISCbits.TRISC7=0;
    
    RE2PPS=0x0A; //PWM6 on RE2
    RC7PPS=0x0B; //PMW7 on RC7
    
    //the pins start high so once it reaches value below it is set low
    PWM6DCH=0; //0% power
    PWM7DCH=0; //0% power
    
    PWM6CONbits.EN = 1;
    PWM7CONbits.EN = 1;
}

/* Function to set PWM output from the values in the motor structure
 */
void setMotorPWM(struct DC_motor *m)
{
	int PWMduty; //temp variable to store PWM duty cycle

	if (m->direction){// forward
		PWMduty = m->PWMperiod - ((int)(m->power)*(m->PWMperiod))/100; // low time increases with power
        //eg. power = 20%, PWMduty = 160, so that the low state from 179-199 gives power
	}
	else {// reverse
		PWMduty =((int)(m->power)*(m->PWMperiod))/100; // high time increases with power
        //eg. power = 20%, PWMduty = 39, so that the high state from 0-39 gives power
	}

	*(m->dutyHighByte) = PWMduty; //set high duty cycle byte - this dereferences the pointer and updates the value Timer2 looks at
        
    
	if (m->direction){ // forward
		*(m->dir_LAT) = *(m->dir_LAT) | (1<<(m->dir_pin)); // set dir_pin bit in LAT to high without changing other bits
	} else {
		*(m->dir_LAT) = *(m->dir_LAT) & (~(1<<(m->dir_pin))); // set dir_pin bit in LAT to low without changing other bits
	}
}

// High level functions to control left and right motor
// Use setMotorPWM to perform low level update

// NOTE for all below functions : 
// You can reduce delay at the end gradually to find the minimum acceptable delay

/*Function to stop the robot gradually 
 * Decrements the power of each motor by 1 until they are zero
 
 */ 
void stop(struct DC_motor *mL, struct DC_motor *mR)
{
    //decrement values gradually 
    while ((mL->power + mR->power) > 0){
        if(mL->power > 0){
            mL->power = mL->power -1;  
        }
        if(mR->power > 0){
            mR->power = mR->power - 1;
        }
        setMotorPWM(mL);
        setMotorPWM(mR);
        __delay_ms(1); // delay for gradual change
    }    
}

/*Function to make the moving robot turn left a little 
 * Decreases power on left-side  wheels by 10% 
 */ 
void turnLeft(struct DC_motor *mL)
{
    char new_power = mL->power * 9/10;
    while (mL->power > new_power) {
        mL->power  = mL->power -1; // slow down right wheels
        setMotorPWM(mL); //update
        __delay_ms(1);
    }
}

/*Function to make the moving robot turn right a little 
 * Decreases power on right-side wheels by 10% 
 */ 
void turnRight(struct DC_motor *mR)
{
    char new_power = mR->power * 9/10;
    while (mR->power > new_power) {
        mR->power  = mR->power -1; // slow down right wheels
        setMotorPWM(mR); //update
        __delay_ms(1);
    }
}

/*Function to make the robot go full speed ahead ahead 
 */ 
void fullSpeedAhead(struct DC_motor *mL, struct DC_motor *mR)
{
    // Update directions
    mL->direction = 1;
    mR->direction = 1;
    //mL->power = 25;
    //mR->power = 25;
    //setMotorPWM(mL);
    //setMotorPWM(mR);
    
    
    
    // Increment values gradually 
    // note that left and right power are equal 
    while ((mL->power + mR->power   < 50)){
        
        if(mL->power < 25){
            mL->power ++;
        }          
        if(mR->power < 25){
            mR->power ++;
        } 
        setMotorPWM(mL);
        setMotorPWM(mR);
        __delay_ms(1); 
    }
    
    
}

void fullSpeedBehind(struct DC_motor *mL, struct DC_motor *mR)
{
    // Update directions
    mL->direction = 0;
    mR->direction = 0;
    //mL->power = -25;
    //mR->power = -25;
    //setMotorPWM(mL);
    //setMotorPWM(mR);
    
    
    // Increment values gradually 
    // note that left and right power are equal 
    
    while ((mL->power + mR->power   < 150)){
        
        if(mL->power < 75){
            mL->power ++;
        }          
        if(mR->power < 75){
            mR->power ++;
        } 
        setMotorPWM(mL);
        setMotorPWM(mR);
        __delay_ms(1); 
    }
    
    
}









/*Function to make a stationary robot do a full left turn quickly  
 * Reduce power on left-side wheels to 0
 * Increase power on right-side wheels to 100
 */ 
void fullTurnLeft(struct DC_motor *mL, struct DC_motor *mR)
{
    //set left motors to zero and right motors to full power 
    while ((mL->power + mR->power) != 100){
        if(mL->power > 0){
            mL->power --;  
        }
        if(mR->power < 100){
            mR->power ++;
        }
        setMotorPWM(mL);
        setMotorPWM(mR);
        __delay_ms(1); 
    }    
}

/*Function to make a stationary robot do a full right turn quickly  
 * Reduce power on right-side wheels to 0
 * Increase power on left-side wheels to 100
 */ 
void fullTurnRight(struct DC_motor *mL, struct DC_motor *mR)
{
    //set right motors to zero and right motors to full power 
    while ((mL->power + mR->power) != 100){
        if(mL->power < 100){
            mL->power  ++;  
        }
        if(mR->power > 0){
            mR->power --;
        }
        setMotorPWM(mL);
        setMotorPWM(mR);
        __delay_ms(1); 
    }    
}


