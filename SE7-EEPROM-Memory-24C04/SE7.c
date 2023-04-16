#include<reg51.h>

sfr LCD = 0xA0;	// P2 = LCD Data pins
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
void msDelay(unsigned int Time);
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
	char Data[] = "EEPROM";	// Data for writing in EEPROM
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

void LCD_DATA(char w)
{
	LCD = w;
	RS = 1;	// data mode
	RW = 0;	// read
	EN = 1;
	msDelay(1);
	EN = 0;
	return;
		

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

void msDelay(unsigned int Time)
{
	unsigned int y, z;
	for(y = 0 ; y < Time ; y++)
	for(z = 0 ; z < 500 ; z++);	// For Loops for Delay
}

void Delay(unsigned char Time)
{
	unsigned char y;
	for(y = 0 ; y < Time ; y++);	// For Loop for delay
}

void EEPROM_Start()
{
	/*
		Start is identified by a falling edge of serial data (SDA) while serial clock (SCL) is stable in the high state. A start
		condition must precede any data transfer instruction. The device continuously monitors (except during a write
		cycle) serial data (SDA) and serial clock (SCL) for a start condition.
		from datasheet
	*/
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
	/*
		Stop is identified by a rising edge of serial data (SDA) while serial clock (SCL) is stable in the high state. A stop
		condition terminates communication between the device and the bus master. A read instruction that is followed by
		NoAck can be followed by a stop condition to force the device into the standby mode.
		A stop condition at the end of a write instruction triggers the internal write cycle.
		from datasheet
	*/
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
	/*
		The acknowledge bit is used to indicate a successful byte transfer. The bus transmitter, whether it be bus master
		or slave device, releases serial data (SDA) after sending eight bits of data. During the 9th clock pulse period, the
		receiver pulls serial data (SDA) low to acknowledge the receipt of the eight data bits.
	*/
	SDA = 0;
	Delay(30);
	SCL = 1;
	Delay(30);
	SCL = 0;
	SDA = 1;
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
	unsigned char i , Data = 0;
	for(i = 0 ; i < 8 ; i++)
	{
		Delay(20);
		SCL = 1;
		Data |= SDA;
		if (i < 7)
			Data <<= 1;
		SCL = 0;
	}
	return Data;
}

void EEPROM_WriteByte(unsigned char Data, unsigned char Address , unsigned char Page)
{
	EEPROM_Start();
	EEPROM_Send(0xA0|(Page<<1));	// Page Number
	EEPROM_Send(Address);
	EEPROM_Send(Data);
	EEPROM_Stop();
	Delay(10);
}

unsigned char EEPROM_ReadByte(unsigned char Address , unsigned char Page)
{
	unsigned char Data;
	
	EEPROM_Start();
	EEPROM_Send(0xA0|(Page<<1));
	EEPROM_Send(Address);
	EEPROM_Start();
	EEPROM_Send(0x0A|(Page<<1));
	Data = EEPROM_Read();
	EEPROM_Stop();
	Delay(5);
	return Data;
}

