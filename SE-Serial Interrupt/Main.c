#include <reg51.h>

sbit LED1 = P2^0;
sbit LED2 = P2^1;

void SerTx(unsigned char);	//data	 transfer
void Delay(void);
unsigned char y;

void serial0() interrupt 4	//serial interrupt subroutine
{
	if (TI == 1)	//transmit interrupt flag
	{
		TI = 0;	//clear interrupt
	}
	else
	{
		y = SBUF;	//put value in pins
		if(y == '1')
		{
			LED1 = ~ LED1;
			Delay();
		}
		if(y == '2')
		{
			LED2 =  ~ LED2;
			Delay();
		}
		RI = 0;	//clear interrupt
						//receive interrupt flag
	}
}

void main()
{
	TMOD = 0x20;	// Timer 1 , Mode 2 Auto Reload
	TH1 = 0xFD;	//Selecting Baud Rate
	SCON = 0x50;	//Mode 1 with start bit and stop bit = Serial mode selection
	TR1 = 1;	//start timer
	IE = 0x90;	//enable serial interrupt
	while(1);
	
}

void SerTx(unsigned char x)
{
	SBUF = x;
	while (TI == 0);	//wait until data transfer
	TI = 0;	//clear TI
}

void Delay(void)
{
	unsigned char i;
	for(i = 0 ; i < 5 ; i++);
}