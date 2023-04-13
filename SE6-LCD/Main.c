#include<reg51.h>

sfr LCD = 0xA0; // P2 = LCD Data Pins
// Special Function Register
// sfr = access to SFR Register by byte
// sbit = acess to SFR register by bit

sbit RS = P1^0;
sbit RW = P1^1;
sbit EN = P1^2;

/*
Control Pins:

RS = Register Select : Toggles between Command/Data Register
0 -> Command Mode
1-> Data Mode

RW = Read/Write : Toggles the LCD between Read/Write Operation
0 -> Write Operation
1-> Read Operation

EN = Enable : Must be held high to perform Read/Write Operatio
always held high.

More details in datasheet
*/

void LCD_INIT(void);	// Initialized Function
void LCD_CMD(unsigned char);	// LCD commaned send function
void LCD_DATA(unsigned char);	// LCD data send function
void msDelay(unsigned int);
void Send_Data(unsigned char *str);	// send data
void LCD_LEFT(unsigned char);
void LCD_RIGHT(unsigned char);
void LCD_FLASH(unsigned char);
void LCD_LINE_ONE(unsigned char);
void LCD_LINE_TWO(unsigned char);

void main(void)
{
	msDelay(10);
	LCD_INIT();
	LCD_LINE_ONE(0);
	Send_Data("ESI Algiers 2022 2023");
	LCD_LINE_TWO(3);
	Send_Data("Abdessamed");
	msDelay(300);
	LCD_FLASH(6);
	LCD_LEFT(15);
	msDelay(300);
	LCD_FLASH(6);
	LCD_RIGHT(15);
	while(1);
}

void LCD_INIT(void)
{
	msDelay(100);
	LCD_CMD(0x38);	// 	2 lines and 5×7 matrix
	LCD_CMD(0x0E);	// Display ON, cursor blinking
	LCD_CMD(0x01);	// Clear display screen
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

void Send_DATA(unsigned char *str)
{
	while(*str)	// while str not finish
		LCD_DATA(*str++);	// increment
}

void LCD_LEFT(unsigned char left)
{
	unsigned char count;
	for(count = 0 ; count < left ; count++)
	{
		LCD_CMD(0x18);	
		// Shift the entire display to the left
		msDelay(200);
	}
}

void LCD_RIGHT(unsigned char right)
{
	unsigned char count;
	for(count = 0 ; count < right ; count++)
	{
		LCD_CMD(0x1C);
		// Shift the entire display to the right
		msDelay(200);
	}
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

void LCD_FLASH(unsigned char i)
{
	unsigned char count;
	for(count = 0 ; count < i ; count++)
	{
		LCD_CMD(0x0A);
		/* Display off, cursor on */
		msDelay(200);
		LCD_CMD(0x0E);
		/* Display on, cursor blinking */
		msDelay(200);
	}
}

void LCD_LINE_ONE(unsigned char pos)
{
	LCD_CMD(0x80 + pos);
	// Set cursor Position in Line No.1
}

void LCD_LINE_TWO(unsigned char pos)
{
	LCD_CMD(0xC0 + pos);
	// Set cursor Position in Line No.2
}

void msDelay(unsigned int time)
{
	unsigned int y, z;
	for(y = 0 ; y < time ; y++)
	for(z = 0 ; z < 500 ; z++);
}


/* 
For more details about LCD Display Module :
	https://circuitdigest.com/article/16x2-lcd-display-module-pinout-datasheet
	https://www.electronicsforu.com/technology-trends/learn-electronics/16x2-lcd-pinout-diagram
*/