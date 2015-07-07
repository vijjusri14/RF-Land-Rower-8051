#include <REG51.H>

void delay(unsigned int);
void controlrobot(void);

void main()
{	
	EX0 = 1;
	IT0 = 1;
	EA = 1;	
	while(1);	
}

void ext0() interrupt 0
{	 	
	controlrobot();	
}

void controlrobot()
{
	unsigned char a, b;	
	EX0 = 0;
	P0 = 0x00;
	while(1)
	{	
		a = P1 & 0x0F;
		switch(a)
		{
			case 0x01 : 
			{
				b = 0x09;
				break;
			}
			case 0x02 :
			{
				b = 0x06;
				break;		
			}
			case 0x04 : 
			{
				b = 0x05;
				break;
			}
			case 0x08 : 
			{
				b = 0x0A;
				break;		
			}			
			default : 
			{
				b = 0xFF;
				break;
			} 			  
		}
		P0 = b;	
		delay(100);
		EX0 = 1;
		P0 = 0x00;
	}
}

void delay(unsigned int count)
{ 
  	while(count > 0)
  	{
		count--;
  	}
}
