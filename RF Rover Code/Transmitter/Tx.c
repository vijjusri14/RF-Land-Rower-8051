#include <REG51.H>

void delay(unsigned int);
void putc(char);
void puts(char*);
char getc();
void send(char);

char *Direction = "Direction : ";
char *Right = "Right";
char *Left = "Left";
char *Forward = "Forward";
char *Reverse = "Reverse";
char *Stop = "Stop";

void main()
{	
	char a, temp;
	char *temp1, *temp2;

	SCON  = 0x50;                   	/* SCON: mode 1, 8-bit UART, enable rcvr    */
	TMOD |= 0x20;                   	/* TMOD: timer 1, mode 2, 8-bit reload      */
	TH1   = 0xFD;                   	/* TH1:  reload value for 9600 baud         */	
	TR1   = 1;                      	/* TR1:  timer 1 run      					*/

	while(1)
	{		
		a = getc();
							
		switch(a)
		{
			case 'R' :
					{
						temp1 = Right;												
						temp = 0x01;
						break;
					}
			case 'L' :
					{
						temp1 = Left;
						temp = 0x02;
						break;
					}
			case 'F' :
					{
						temp1 = Forward;						
						temp = 0x04;
						break;
					}
			case 'B' :
					{
						temp1 = Reverse;						
						temp = 0x08;
						break;
					}
			default :
					{
						temp1 = Stop;						
						temp = 0x00;
						break;
					}			
		}
		temp2 = temp1;
		puts(temp2);
		send(temp);
		delay(100);
	}
}
			
void send(char temp)
{
	P1 = temp;
	P1 &= 0x0F;
	delay(1000);
	P1 |= 0x10;
}			
			  
void putc(char b)
{
	SBUF = b;
	while(TI==0);
	TI=0;   
}

void puts(char* ptr)
{
	while(*ptr != 0x00)
	{
		putc(*ptr);
		ptr++;
	}
	putc('\r');
	putc('\n');
}

char getc()
{	
	char chr;
	while(RI==0);
	chr = SBUF;
	RI=0;   
	return chr;
}

void delay(unsigned int count)
{
	unsigned int count1;
	for(count1 = 0xFF; count1 !=0; count1--)
	{
		while(count > 0)
  		{
			count--;
  		}
	}
}
