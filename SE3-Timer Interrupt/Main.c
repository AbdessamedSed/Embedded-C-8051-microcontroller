#include<REG51.h>
/*
Interrupts are done by configuring the Interrupt Enable (IE) register
Bit EA = 1;
Bits ET0, ET1, ET2 bits are used to enable the Timer Interrupts 0, 1, 2, respictively

*/
/*
Timer Interrupt : 
To enable the timer 0 interrupt, we take the following steps:
	1. Bit D7 of the IE register (EA) must be set to high enable the Global Interrupt
	2. Bit D1 of the IE register (ET0) must be set to high to enable the Timer Interrupt
	3. Set The Timer mode
	4. Load the initial timer value
*/

void Delay(void);
unsigned char Count;
unsigned char Pattern[10] = {0xF9 , 0xA4 , 0xB0 , 0x99 , 0x92 , 0x82 , 0xF8 , 0x80 , 0x90 , 0xC0}; // Numbering data in Array
// Pattern [10] = {11111001 , 11000100 , 11010000 , 10011001}

/* Interrupt Routine */
void timer0(void) interrupt 1 // interrupt 1 = timer 0 interrupt
{ 
	for(Count = 0 ; Count < 10 ; Count++) // For loop for counting
	{
		P2 = Pattern[Count]; // Send data to Port No.2
		Delay();
	}
}

void main(void)
	
{
	TMOD = 0x02; // Configuring TMOD register to select Timer 0 Mode 2
	TH0 = 0x01; // Timer TH0 = -92
	IE = 0x82; // load 0x82 value in IE register to enable interrupt for timer 0
	TR0 = 1;  // start timer
	while(1);	// stay here
}

void Delay(){
	unsigned int x, y;
	for(x = 0 ; x < 700 ; x++)
	for(y = 0 ; y < 160 ; y++);
}