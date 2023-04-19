#include<reg51.h>

unsigned char Column[8] = {0x80 , 0x40 , 0x10 , 0x08 , 0x04 , 0x02 , 0x01};
unsigned char Row[102] = { 0xFF , 0xC0 , 0xB7 , 0x77 , 0xB7 , 0xC0, //A
													 0xFF , 0x00 , 0x6E , 0x6E , 0x6E , 0x91 , //B
													 0xFF , 0x81 , 0x7E , 0x7E , 0x7E , 0xBD , //C
													 0xFF , 0x00 , 0x7E , 0x7E , 0x7E , 0x81 , //D
													 0xFF , 0x00 , 0x6E , 0x6E , 0x6E , 0x7E , // E
													 0xFF , 0x00 , 0x6F , 0x6F , 0x6F , 0x7F , //F
													 0xFF , 0x81 , 0x7E , 0x7E , 0x76 , 0xB9 , //G
													 0xFF , 0x00 , 0xEF , 0xEF , 0xEF , 0x00 , //H
													 0xFF , 0xFF , 0x7E , 0x00 , 0x7E , 0xFF, //I
													 0xFF , 0xF9 , 0x7E , 0x7E , 0x01 , 0x7F, //J
													 0xFF , 0x00 , 0xE7 , 0xDB , 0xBD , 0x7E , //K
												   0xFF , 0x00 , 0xFE , 0xFE , 0xFE , 0xFE , //L
													 0xFF , 0x80 , 0x7F , 0x81 , 0x7F , 0x80, //M
													 0xFF , 0x00 , 0xBF , 0xC3 , 0xFD , 0x00, //N
													 0xFF , 0x81 , 0x7E , 0x7E , 0x7E , 0x81, //O
												   0xFF , 0x80 , 0x77 , 0x77 , 0x77 , 0x8F, //P
													 0xFF , 0x81 , 0x7E , 0x7E , 0x81 , 0xFE  //Q
};

sbit Data_Row = P2^7;	//
sbit LA_Clock_Row = P2^6;	// Latch Clock
sbit Sh_Clock_Row = P2^5;	// Shift Clock

sbit Data_Col = P2^2;
sbit LA_Clock_Col = P2^1;
sbit Sh_Clock_Col = P2^0;

void Delay(unsigned int);
unsigned char i, j, m, n, l, x, y, z;

void main()
{
	i = 0;
	j = 0;
	m = 0;
	n = 0;
	l = 0;
	x = 0;
	y = 0;
	
	LA_Clock_Row = 0;
	Sh_Clock_Row = 0;
	LA_Clock_Col = 0;
	Sh_Clock_Col = 0;
	
	while(1){
		for(m = 0 ; m < 15 ; m++) // Delay for next Alphabet
		{
			for(n = 0 ; n < 8 ; n++) // Send Column Data
			{
				for(z = 0 ; z < 8 ; z++)	// Send Colmun Data Bit by Bit
				{
					Data_Col = (x>>z) & 0x01;
					Sh_Clock_Col = 0; // Send Low to Shift Clock
					Sh_Clock_Col = 1;	// Send High to Shift Clock
				}
				LA_Clock_Col = 0; // Send Low to Latch Clock
				LA_Clock_Col = 1; // Send High to Latch Clock
				x = Column[n];
				
				for(z = 0 ; z < 8 ; z++)
				{
					Data_Row = (y>>z) & 0x01;
					Sh_Clock_Row = 0;	// Send Low to Latch Clock
					Sh_Clock_Row = 1;	// Send Hight to Shift Clock
				}
				LA_Clock_Row = 0;	// Send Low to Latch Clock
				LA_Clock_Row = 1;	// Send High to Latch Clock
				Delay(1);
				
				j++;
				if(j==102) j = 0;
				y = Row[j];  // Put Row data into y
			}
			j = l;
			if(l==102) l = 0;
		}
		l++;
		j = l;
	}
}

void Delay(unsigned int num)
{
	unsigned int i, j;
	for(i = 0 ; i < num ; i++)
	for(j = 0 ; j < 1000000 ; j++);
}