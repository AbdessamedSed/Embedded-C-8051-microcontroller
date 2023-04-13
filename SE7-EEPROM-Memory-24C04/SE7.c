#include<reg51.h>

sfr LCD = 0x0A;	// P2 = LCD Data pins
sbit RS = P0^5;	// Register Select(RS) pin of 16*2 LCD
sbit RW = P0^6;	// Read/Write (RW) pin of 16*2 LCd
sbit EN = P0^7;	// Enable (E) pin of 16*2 LCD

sbit SDA = P3^1;	// SDA pin of EEPROM
sbit SCL = P3^0;	// SCL pin of EEPROM
/*
	SCL : The SCL input is used to positive edge clock data into each
	EEPROM device and negative edge clock data out of each device.
	SDA : The SDA pin is bidirectional for serial data transfer. This pin is
	open-drain driven and may be wire-ORed with any number of other open-drain or 
	opencollector devices.

*/

void LCD_CMD(unsigned char x);
void LCD_DATA(char w);
void LCD_INIT(void);
void Send_Data(unsigned char *Str);
void msDelay(unsigned char Time);
void EEPROM_Start();
void EEPROM_Stop();
void EEPROM_Ack();
void EEPROM_Send(unsigned char Data);
unsigned char EEPROM_Read();
void EEPROM_WriteByte(unsigned char Data , unsigned char Address , unsigned char Page);
unsigned char EEPROM_ReadByte(unsigned char Address , unsigned char Page);
unsigned int i;

void main(void)
{
	char Data[] = "Welcome to EEPROM Programming Simulation";	// Data for writing in EEPROM
	msDelay(10);
	LCD_INIT();
	
	for (i = 0 ; i < 15 ; i++)
	{
		EEPROM_WriteByte(Data[i] , i , 0);
	}
	
	for (i = 0 ; i < 15 ; i++)
	{
		LCD_DATA(EEPROM_ReadByte(i , 0));
	}
	
	while(1);
	
}

void LCD_DATA(unsigned char w)
{
	LCD = w;
	RS = 1;	// data mode
	RW = 0;	// read
	EN = 1;
	msDelay(1);
	EN = 0;
	return;
		
}

void LCD_CMD(unsigned char x)
{
	LCD = x;
	RS = 0;	// command mode
	RW = 0;	// read
	EN = 1;
	msDelay(1);
	EN = 0;
	return;
}

void LCD_INIT(void)
{
	msDelay(100);
	LCD_CMD(0x38);	// 	2 lines and 5×7 matrix
	LCD_CMD(0x0E);	// Display ON, cursor blinking
	LCD_CMD(0x01);	// Clear display screen
}

void msDelay(unsigned int time)
{
	unsigned int y, z;
	for(y = 0 ; y < time ; y++)
	for(z = 0 ; z < 500 ; z++);	// For Loops for Delay
}

void Delay(unsigned char Time)
{
	unsigned char y;
	for(y = 0 ; y < Time ; y++);	// For Loop for delay
}

void EEPROM_Start()
{
	SCL = 0;	//	Clock Input = disable
	SDA = 1;	// Data I/O = enable
	Delay(30);	// Delay
	SCL = 1;	// Clock Input 
	Delay(30);	// Delay
	SDA = 0;
	Delay(30);	//Delay
	SCL = 0;
}

void EEPROM_Stop()
{
	SCL = 0;	// Clock Input = 0
	Delay(30);
	SDA = 0;	// Data I/O = 0
	Delay(30);
	SCL = 1;	// Clock Input = 1
	Delay(30);
	SDA = 1;	// Data Input = 1
}

void EEPROM_Ack()
{
	SDA = 0;
	Delay(30);
	SCL = 1;
	Delay(30);
	SCL = 0;
	Delay(30);
}

void EEPROM_Send(unsigned char Data)
{
	unsigned char i;
	
	for (i = 0 ; i < 8 ; i++)	// For loop for sending data bit by bit
	{
		SDA = Data & 0x80;	// AND with 1000000 for sending the MSB (Most Significant Bit)
		SCL = 1;
		SCL = 0;
		Data <<= 1;	// Shift Sata with 1	for prepaing the next bit to bed sent
	}
	
	EEPROM_Ack();	// Call EEPROM Acknowledge
	/*
		EEPROM Acknowledge: 
	*/
}

unsigned char EEPROM_Read()
{
	
}