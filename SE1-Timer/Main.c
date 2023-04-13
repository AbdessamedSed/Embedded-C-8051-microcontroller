#include<REG51.h>

sbit LED1 = P2^7;
sbit LED2 = P2^0;

/*
Timer: A timer is a clock that controls the sequence of an event while counting in fixed intervals of time
AT89C51 microcontroller has two Timers designated as Timer0 and Timer1.
Each of these timers is assigned a 16-bit register
So the maximum allowed counts in value of Timer registers can be from 0000H to FFFFH
*/
void TM01Delay(void);
void TM02Delay(void);

void main(void) {
	
	for(;;)
	{
		// LED 1
		/*LED1 = 0;
		TM01Delay();
		LED1 = 1;
		TM01Delay();*/
		// LED 2
		LED2 = 0;
		TM02Delay();
		LED2 = 1;
		TM02Delay();
	}
	
	
}

void TM01Delay(void) {
	
	unsigned char z;
	
	for(z = 0 ; z < 15 ; z++)
	{
		TMOD = 0x01;	// Set Timer 0 Mode 1 (16-bit mode)
		
		/*
			TMOD = 2 * (Gate , C/T , M1 , M0)
			4 less bits for Timer0
			Gate = 1 : 
			C/T = 0 : Timer updates its value automatically corresponding to 8051 clock source , = 1 : it updates its value when it receives pulse from outside the 8051 controller
			M0, M1 : Timer modes 0, 1, 2 and 3 (00 , 01 , 10 , 11) 
		*/
		
		TL0 = 0x00;		// Initial Lower Value
		TH0 = 0x65;		// Initial Higher Value
		
		/*
			Delay = (MaxValue FFFF - count + 1) * cycle
			cycle = 1.085 ms
			external clock = 12 MHz => internal clock = 1/12 external clock = 1 MHz
		*/
		
		TR0 = 1;			// Start Timer 0
		while(TF0 == 0);	// wait until timer overflow
		
		TR0 = 0;	// Clear Timer run
		TF0 = 0;	// Cleat Timer flag
	}
}

void TM02Delay(void)
{
	unsigned char z;
	
	for(z = 0 ; z < 100 ; z++)
	{
		TMOD = 0x02; 		// Set Timer 0 Mode 1 (8-bit mode)
		TH0 = 01;			// Load in TH0 only , because it's a 8-bit mode
		TR0 = 1;				// Start Timer
		
		while(TF0 == 0); // wait
		
		TR0 = 0;		// Clear Timer run
		TF0 = 0;		// Clear Timer flag
		
	}
	
}