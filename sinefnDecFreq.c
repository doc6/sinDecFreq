/*
 * sinDecFreqButtonControl.c
 *
 * A program to generate a sine wave using the DCA module
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define sinearraylength 256		// change this number to change frequency (16 for 82 kHz, 256 for 6 kHz)
//#define sin(x) 4*(sin(x)/(x))

unsigned char sinearray[sinearraylength];

/*
 * init_portD()
 *
 * Initialise Port D to be all outputs.  Port D is digital pins
 * 0 to 7 of the Arduino Uno.
 *
 * modified by D O Corlett 2/08/16
 */
void init_ports(void)
{
	/* Make all 8 bits of Port D outputs */
	DDRD = 0xff;
	/* Set outputs to low voltage. */
	PORTD = 0;

	DDRB = 0x00;
}

void delay_ms(unsigned int xms)
{
    while (xms) {
        _delay_ms(0.96);
        xms--;
    }
}



void sineArray(void)
{
	float angle, step;

	angle = 0.0;
	step = 6.28/sinearraylength;
	for(int i = 0; i < (sinearraylength+1); i++)
	{
		sinearray[i] = (unsigned char)
				((sin(angle) + 1)*127);		// fixed the sine calculation to range from 0 to 254.
		angle += step;
	}
}

/*
 * write_dac()
 *
 * Write 8-bit number out to DAC via port D.
 */
void write_dac(unsigned char value)
{
	PORTD = value;
}

/**  Main Function  ********************************************************/

int main(void)
{
	init_ports();
	sineArray();

	while (1) {
		for(int i=1; i < (sinearraylength+1); i++)
		{
			write_dac(sinearray[i]);
			delay_ms(10);				// delay to decrease frequency
		}
	}


	return 0;
}

