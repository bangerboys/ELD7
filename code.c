#define F_CPU 16000000UL    // Setting Frecquency
#include <avr/io.h> 
#include <util/delay.h>
uint16_t adcread(uint8_t adcx)
{
	uint8_t ch;
	ch = adcx;
	ADMUX = (ADMUX & 0xf8)|ch; 
	ADCSRA |= (1 << ADSC);
	while((ADCSRA & (1 << ADSC)));
	return ADC;
}
int main()
{
	PRR |= (unsigned char)((1 << PRSPI)|(1 << PRTIM2)|(1 << PRTIM0)|(1 << PRTWI));
	DDRB |= (1 << 5);
	DDRB |= (1 << 4);
	ADCSRA |= (1 << ADEN);
	ADMUX = (1<<REFS0);
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);
	while(1)
	{
		if(adcread(0) < 512 && adcread(5) > 130)
		{
			PORTB |= (1 << 5);
			PORTB |= (1 << 4);
		} 
		else if(adcread(0) < 512 && adcread(5) < 130)
		{
			PORTB |= (1 << 5);
			PORTB &= ~(1 << 4);
		}
		else if(adcread(0) > 512 && adcread(5) > 130)
		{
			PORTB &= ~(1 << 5);
			PORTB |= (1 << 4);
		}
		else if(adcread(0) > 512 && adcread(5) < 130)
		{
			PORTB &= ~(1 << 5);
			PORTB &= ~(1 << 4);
		}
	}
	return 0;
}

