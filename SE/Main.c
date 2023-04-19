#include<REG51.h>
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit LED5 = P0^4;
sbit LED6 = P0^5;
sbit LED7 = P0^6;
sbit LED8 = P0^7;

sbit SW1 = P2^6;
sbit SW2 = P2^7;

void Delay();
void main(void){
	
	unsigned int z;
	
	/*while(1){
	LED = 1;
		Delay();
		LED = 0;
		Delay();
	
	}*/
	z = 0;
	SW1 = 1;
	SW2 = 1;
	while (1){
		
		if (SW1 == 0){
			z++;
			while(SW1 == 0);
			if (z == 9) z = 0;
		}
		
		if(SW2 == 0){
			
			switch(z){
				case (1):
				{
					LED1 = ~ LED1;
					z = 0;
					break;
				}
				case (2):
				{
					LED2 = ~ LED2;
					z = 0;
					break;
				}
				case(3):
				{
					LED3 = ~ LED3;
					z = 0;
					break;
				}
				case (4):
				{
					LED4 = ~ LED4;
					z = 0;
					break;
				}
				case (5):
				{
					LED5 = ~ LED5;
					z = 0;
					break;
				}case (6):
				{
					LED6 = ~ LED6;
					z = 0;
					break;
				}case (7):
				{
					LED7 = ~ LED7;
					z = 0;
					break;
				}
				case (8):
				{
					LED8 = ~ LED8;
					z = 0;
					break;
				}
				
			}
			
		}
		
	}
	
}
void Delay(){
	unsigned int x, y;
	for(x = 0 ; x < 1000 ; x++)
	for(y = 0 ; y < 165 ; y++);
}