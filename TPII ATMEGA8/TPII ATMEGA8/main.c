/*
 * TPII ATMEGA8.c
 *
 * Created: 6/22/2019 12:17:19 PM
 * Author : ricar
 */ 

#define F_CPU 1000000UL // Clock Speed
#define BAUD 4800
#define MYUBRR  12//(F_CPU/8/BAUD-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int melody_counter =0;
int val = 0;
uint16_t counter;

void USART_Init( unsigned int ubrr){
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRA |= (1<<RXC);
	UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
	}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

ISR(USART_RXC_vect)
{
		val = USART_Receive();
	for(counter = 0; counter < 10000; counter++)
	{
		if(val == 65)
		{
			PORTB|=(1<<PB0);
			OCR1A = ICR1 - 2100;
		}
		else
		{
			PORTB&=~(1<<PB0);
			OCR1A = ICR1 - 1200;
		}
	}
	counter = 0;
}


void setPWM()
{
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0)|(1<<WGM11);
	TCCR1B |= (1<<WGM12) |(1<<WGM13)|(1<<CS10);
	ICR1 = 19999;
}

void setBuzzer()
{
	TCCR0 |=(0<<CS00)
	|(0<<CS01)
	|(0<<CS02); //no prescaling
		
	TIMSK |=(1<<TOIE0);//enables overflow interrupt
	
		
}

int main(void)
{
	DDRB |= (1<<DDB0);
	DDRB |= (1<<DDB1); //pinMode(pinb0, OUTPUT);
	DDRB |= (1<<DDB2); //pinMode(pinb2, OUTPUT);
	DDRD &= ~(1<<PD2);//Makes pin D2 as Input send data button
	USART_Init(MYUBRR);
	setPWM();
	OCR1A = ICR1 - 1200; //sets Servo to 0º position
	setBuzzer();
	sei();
    /* Replace with your application code */
    while (1) 
    {
		if(PIND&(1<<PD2))
		{
			UDR = 'C';
		}
	}
}

