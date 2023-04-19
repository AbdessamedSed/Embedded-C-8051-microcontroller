#include<REG51.h>
void Delay();

void main(void) {
	while(1){
		
		P2 = 0xFF;
		Delay();
		P2 = 0xFE;
		Delay();
		P2 = 0xFD;
		Delay();
		P2 = 0xFB;
		Delay();
		P2 = 0xF7;
		Delay();
		P2 = 0xEF;
		Delay();
		P2 = 0xDF;
		Delay();
		P2 = 0xBF;
		Delay();
		P2 = 0x7F;
		Delay();
	
	}
}

void Delay(){
	unsigned int x, y;
	for(x = 0 ; x < 1000 ; x++)
	for(y = 0 ; y < 165 ; y++);
}