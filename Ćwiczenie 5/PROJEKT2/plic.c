#include <p24fj128ga010.h>

_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRI)

#define SCALE 308L

/* numer którym dostajemy siê do czujnika temperatury */

#define TSENS 4
#define AINPUTS 0xffcf
void ADCinit(int amask)

{
	AD1PCFG = amask;
	AD1CON1 = 0x00e0;
	AD1CSSL = 0;
	AD1CON2 = 0;
	AD1CON3 = 0x1f02;
	AD1CON1bits.ADON = 1;
}

int readADC(int ch)

{
	AD1CHS = ch;
	AD1CON1bits.SAMP = 1;
	while (!AD1CON1bits.DONE);
	return ADC1BUF0;
}


int main(void)
{
	TRISA = 0xFF00;
	TRISD = 0xFFFF;

	unsigned long i;
	unsigned char display = 0;
	int temp;
	unsigned int szybkosc = 90L;
	unsigned int czas = 0;
	unsigned char lampka = 0;
	unsigned int wylacznik = 0;

	PORTA = 0x0000;
	ADCinit(AINPUTS); /*inicjalizacja konwertera AD*/

	display = 1;

	while (1) {
		PORTA=(unsigned int) display;
		//Nop();
		for (i = szybkosc * SCALE; i > 0; i--) Nop();
		temp = readADC(TSENS);
		if(wylacznik == 0)
		{
			if(temp > 250)
			{
				czas += szybkosc;
				lampka = 1 - lampka;
				display = lampka;
				if(czas >= 3000)
				{
					display = 255;
				}
			
			}
			else
			{
				display = 0;
				czas = 0;
			}	
		}
		if(PORTDbits.RD6 == 0)
		{
			wylacznik = 1 - wylacznik;
			display = 0;
			czas = 0;
		}
	}

}