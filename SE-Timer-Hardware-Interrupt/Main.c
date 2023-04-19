#include<REG51.h>

void Delay(void);
unsigned char Count;
unsigned char Pattern[10] = {0xF9 , 0xA4 , 0xB0 , 0x99 , 0x92 , 0x82 , 0xF8 , 0x80 , 0x90 , 0xC0};

void timer0(void) interrupt 1
{
	P2 = Pattern[Count];	// send data to port No.2
}

void UpCounter(void) interrupt 0	// Timer Interrupt
{
	Count++;
	if(Count == 10) Count = 0;
	Delay();
	P2 = Pattern[Count];
	while(INT0 == 0);	// stay here while switch is pressed
}

void DownCounter(void) interrupt 2	// External Interrupt
{
	if(Count == 0) Count = 10;
	Count--;
	Delay();
	P2 = Pattern[Count];
	while(INT1 == 0);	// stay here while switch is pressed
}

void main(void)
{
	TMOD = 0x02;
	TH0 = 0x01;
	IE = 0x87;
	TR0 = 1;
	Count = 9;	// Initial value
	P2 = Pattern[Count];
	
	while(1);	// stay here
	
}

void Delay(void)
{
	unsigned int x;
	for(x = 0 ; x < 5 ; x++);
}