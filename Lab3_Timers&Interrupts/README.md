# Lab 3 - Timers and interrupts

## Learning outcomes

This lab session introduces two fundamental concepts in embedded system development, interrupts and  hardware timers. The learning objectives for this lab are.

- Understand what an interrupt is and how to configure the interrupt registers
- Understand how to write an interrupt service routine (ISR) and what they should (and shouldn't) do
- Understand what a hardware timer is and why it is useful
- Set up and use a hardware timer and display the value on an LED array
- Set up timers and interrupts to enable precisely timed events

## Interrupts
In the previous labs we recognised a button press by polling the button until the level went high. This wastes a lot of CPU cycles in checking the level at a pin and is a very inefficient way of recognising an event. Instead, wouldn’t it be better if the CPU was notified when an event occurs? We can achieve this using interrupts.

### Interrupt registers and service routines
Interrupts cause a special piece of code to execute when they occur. They are configured with the INTCON register and the PIEx, PIRx and IPRx registers as detailed below.

Register | Function
---------|---------
INTCON | Overall control of interrupts and priority
PIE(0-9) | Bits in these registers enable individual interrupts sources from the peripheral modules
PIR(0-9) | Bits in these registers are the flags that tell you which interrupt was triggered
IPR(0-9) | Registers for defining whether an interrupt source is high or low priority (high by default)

To turn on interrupts we need to first turn on the appropriate bit in the PIEx registers before turning on interrupts globally. As an example, if we wanted to configure the external interrupt source INT0 we would use the following code:
	
	INTCONbits.INT0=1; 	//enable interrupt source INT0
	INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)
	
The next thing we need to do is write a function that is executed when the interrupt event occurs. This function is special and is called an interrupt service routine or ISR. An ISR needs to perform two essential actions in addition to the code you want to run when the interrupt occurs. These are to check the source of the interrupt and clear the interrupt flag associated with that source. We need to check the interrupt source so that we can service multiple sources in the same ISR. We also need to clear the corresponding interrupt flag, otherwise we will be stuck in the ISR forever as it is a set interrupt flag that triggers the execution of the ISR. In our example for source INT0 the ISR might look like this:

	void __interrupt(high_priority) HighISR()
	{
		if(PIR0bits.INT0IF){ 					//check the interrupt source
		some code you want to execute here;
		PIR0bits.INT0IF=0; 						//clear the interrupt flag!
		}
	}

The __interrupt(high_priority) syntax is compiler specific and tells the compiler that this function is our ISR. The compiler then takes care of making sure this function is executed when an interrupt occurs by storing a link to it in a specific memory location within the PIC chip. The name of the function HighISR isn't critical, just make it clear to anyone that this is the ISR.  As a general rule, ISRs should execute as quickly as possible. Think about what the time critical, minimum necessary code is and aim for that. If you need to perform longer pieces of code that are less time critical, set a variable to indicate that the interrupt occurred and deal with it in your main while(1) loop.

### Using comparator, DAC and LDR to generate an interrupt
Unfortunately the buttons built into the Clicker 2 board are not wired directly to an external interrupt source such as INT0 (this is intentional as it leaves them free for you to access and do other things with). Instead of configuring an external interrupt source, we will generate an interrupt using the LDR and the comparator module on the PIC18F67K40. This will allow us to wave our hand above the LDR and generate an interrupt to make an action happen.

We will not go into too much detail in the configuration of the comparator and DAC as the focus of this lab is on interrupts. A comparator is a device that takes two input voltages and looks to see which one is bigger than the other, returning high or low depending on the result. In the functions provided in this GitHub repo the comparator takes its inputs from pin RF7 (you need to jump your LDR connection over from pin RA3) and the output the Digital to Analogue Conversion (DAC) module. The 5-bit DAC module is conceptually the reverse of the ADC module and provides an analogue voltage between 0V and 3.3V based on a digital value. Connecting it (internally) to the comparator allows it to act as the threshold value. 

When the LDR voltage passes through the threshold the output state of the comparator changes. The interrupt flag will be set when the state goes from low to high and corresponds to reducing the light on the LDR (i.e. by holding your hand over it). Note that you may have to adjust the DAC threshold value depending on your ambient light level. To make use of the comparator interrupt you need to enable it by setting C1IE in the PIE2 register and check the C1IF bit in PIR2 in your ISR.

### Sleep mode
The use of interrupts allows us to conserve power by putting our chip into a low power or sleep mode. When in sleep mode the PIC is no longer executing any code, but the hardware peripherals can still run if configured to do so. Since the PIC is not running any code in sleep mode it is down to interrupts to wake the chip from sleep mode and start running code again. Waking from sleep happens automatically when interrupts are configured so there is no additional configuration necessary. Sleep mode can be entered using the built in Sleep() function.

## Exercise 1 - Touchless switch

1. Clone the GitHub repo, create your MPLAB x project and add all the .c and .h files to your project (the timers.c/h files are not needed until exercise 2).
1. Complete the interrupt initialisation function and ISR to toggle the LED on RH3 when the LDR goes from light to dark. Remember to call the necessary init functions from your main and set the TRIS register for any outputs.
1. There should be nothing in the main while(1) loop. To conserve power, call the Sleep() function from the main while(1) loop to put the chip to sleep when the ISR finishes. How can you check that the chip has entered sleep mode?

## Timers
Timer/counter modules are another fundamental part of embedded systems and are necessary for precise timing, triggering/counting events and the measurement of time. While software delays can be used for short periods of time where precision is not critical, software delays take up processing time and your code is not free to perform other calculations when executing the software delay routines. Timers are hardware modules that count the number of edges from a clock source input signal and are independent from the processing of machine instructions. Timers can accept a variety of clock sources and often include prescaling options to allow the user to configure the rate at which the value stored in a timer increases. The clicker 2 board uses a 16MHz crystal oscillator and we have configured our chip to use a feature called 4x Phase Locked Loop (PLL) to increase this to 64MHz. This is the base oscillation frequency (Fosc) and we will use it as our main clock source for the timer module. There are 9 timer modules within the PIC18F67K40 with slightly different features and capabilities. In this lab we will learn to configure timer0.

### Timer0 configuration
Timer0 can be configured to run in 8 bit mode or 16 bit mode and can take its clock from a variety of sources. These options are configured through the T0CON0 and T0CON1 registers. The current timer value is stored in the TMR0L/H register pair. In 8 bit mode only the TMR0L is used to store the timer value.

Register | Function
---------|---------
T0CON0bits.T0EN | Turn timer on/off
T0CON0bits.T016BIT | Set 8/16 bit operation
T0CON1bits.T0CS |  Clock source setting bits
T0CON1bits.T0ASYNC | Asynchronous to system clock - needed for correct operation when using Fosc as timer source
T0CON1bits.T0CKPS | Prescaler value bits
TMR0L/H | Current timer value (only L register used in 8 bit mode)

### Timer prescaler
The interval, *Tint*, between the timer incrementing to the next value is set by the oscillator source and the prescaler, *PS*, according to:

<img src="https://render.githubusercontent.com/render/math?math=T_{int}={4*PS}/F_{osc}">

If we were to use a 1:1 prescaler with an Fosc of 64MHz (as it is on our board) the timer would increment every 62.5 ns. That's very fast! Adjusting the prescaler allows us to slow this down and time longer periods.

### Timer overflows and interrupts
When a timer reaches the maximum value it can store (255 in 8 bit mode, 65535 in 16 bit mode) it resets to 0, this is called an overflow. Overflow events can be set up to trigger interrupts, enabling you to perform tasks at set intervals. The time is takes to reach the overflow is simply the maximum count multiplied by the vale *T* calculated above. Adjusting the prescaler value allows you to change the length of this interval. Fine tuning of the interval can be achieved by writing values to the TMR0L/H registers on overflow, so instead of counting from 0 to the maximum value, the timer counts from some high valuer to the maximum value. This reduces the time period before the next overflow occurs.

### TMR0L/H read/write order
The current timer value is accessible through the TMR0L/H register pair. The TMR0H register is buffered. This means it is not directly mapped to the TMR0 value and only contains a copy of the 8 most significant bits from TMR0. The value in TMR0H is only updated when we read from TMR0L. This is to ensure the value is consistent should the timer change value between reading the low and high registers. If we try to read TMR0H without reading TMR0L first, we will get some old and meaningless value.

Similarly when writing to the timer the value written to TMR0H is not actually written to the timer until we write to TMR0L. Again this is to ensure the timer is updated correctly. You must write to TMR0H first, and then write to TMR0L to avoid problems.

## Exercise 2 - One Mississippi...
This exercise will explore the use of Timer0 in 8 and 16 bit mode, adjustment of prescaler, interrupts on overflow and fine tuning by writing to the TMR0 registers.

1. Use the functions in timers.c/h to set up Timer0 in 8 bit mode and display the current count on the LED array in binary. You will need to call your LEDout() function from the previous lab. Copy your LCDarray.c/h files to the project directory and add them to the project.
1. Complete the get16bitTMR0val() function to read the full 16 bit value and switch the timer to operator in 16 bit mode. See note above about read order for TMR0L/H bytes. Display the 8 most significant bits on the LED array.
1. Adjust the prescaler so that the timer overflows (reaches maximum value and starts again at 0) approximately every second.
1. Turn on the TMR0 interrupt source and toggle the LED on RH3 in the ISR (note - don't call the sleep function, it will stop the timer with the way we have configured Timer0).
1. Can you improve the accuracy of your timed second by writing initial values to TMR0L/H register pair? Note this needs to be done every time the timer overflows. How accurate would your device be over 1 year?
