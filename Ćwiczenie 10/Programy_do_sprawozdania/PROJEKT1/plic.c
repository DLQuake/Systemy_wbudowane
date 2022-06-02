#include <p24fj128ga010.h>

//Konfiguracja dla Explorer 16 z progr. icd2
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRI)

#define SCALE 308L

int BIN1(unsigned char display)
{
	display=display+1;
	return display;
}
int BIN2(unsigned char display){
	display=display-1;
	return display;
}
int GRAY(unsigned char display,int x)
{
	display=x^(x>>1);
	return display;
}
int BCD(unsigned char display, int x)
{
	display = ((x/10)*16)+(x%10);
	return display; 
}
unsigned char SNAKE(unsigned char display, int pom){
	int l = 7;
	int i=0;
	unsigned char arr[6] = {l,l*2,l*4,l*8,l*16,l*32};
	
	for(i;i<6;i++)
	{
		if(display==arr[i]&&pom==0){
			return display<<1;
		}
		else if(display==arr[i]&&pom==1){
			return display>>1;
		}
	}
	return l;
}
unsigned char QUEUE(unsigned char display)
{
	unsigned char i=0,j;
	unsigned char arr[7] = {254,252,248,240,224,192,128};
	for(i;i<7;i++){
		if(display==255) return 1;
		if(display>=arr[i]){
			j=display%arr[i];
			if(j==0) return display|1;
			return display-j|j<<1;
		}
	}
	return display<<1;
}
unsigned char PRNG_LFSR_1110011(unsigned char display){
	unsigned char xor=1&((display)^(display>>1)^(display>>4)^(display>>5));
	return display>>1|xor<<5;
}
int main(void){
	unsigned long i;
	unsigned char display=0;

	int pom = 1;
	int x = 0;
	//inicjalizacja
	 PORTA=0x0000;
	 TRISA=0xFF00;
	 TRISD=0xFFFF;
	 
	//niekoÅ?czÄ?ca siÄ? pÄ?tla 
	again:
		Nop();
		PORTA=(unsigned int) display;
		for(i=500L*SCALE;i>0;i--) Nop();
		if (PORTDbits.RD13 == 0)
		{
		   pom++;
		}
		else if(PORTDbits.RD6 == 0)
		{
		   pom--;
		}
		else if(PORTDbits.RD7 == 0)
		{	
	   		display=0;
		}	
		if(pom==10) pom=1;
		if(pom==0) pom=9;
		if(pom==1) display=BIN1(display);
		if(pom==2) display=BIN2(display);
		if(pom==3)
		{
	 		display=GRAY(display,x);
			x++;
		}
		if(pom==4)
		{
	 		display=GRAY(display,x);
			x--;
			if(x<0)x=255;
		}
		if(pom==5)
		{
			display=BCD(display,x);
			x++;
		}
		if(pom==6)
		{
			display=BCD(display,x);
			x--;
			if(x<0)x=99;
		}
		if(pom==7)
		{
			display=SNAKE(display,x);
			if(display==224)
			{
				x=1;
			}
			else if(display==7) 
			{
				x=0;
			}
		}
		if(pom==8)
		{
			display=QUEUE(display);
		}
		if(pom==9)
		{
			display=PRNG_LFSR_1110011(display);
		}
	goto again;
}