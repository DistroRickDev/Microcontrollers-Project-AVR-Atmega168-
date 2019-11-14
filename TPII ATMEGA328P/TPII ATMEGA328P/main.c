#define F_CPU 1000000UL // Clock Speed
#define BAUD 4800
#define MYUBRR ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int melody_counter =0;

void setPWM()
{
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0)|(1<<WGM11);
	TCCR1B |= (1<<WGM12) |(1<<WGM13)|(1<<CS10);
	ICR1 = 19999;
}



void setBuzzer()
{
	TCCR0A |=(1<<COM0A0)
	|(0<<COM0A1)
	|(1<<WGM01);
	
	TCCR0B |=(0<<CS00);//set it to one
	
	
	TIMSK0 |=(1<<OCIE0A)|(1<<TOIE0);//enables overflow interrupt
	
	OCR0A = 0;
}

void adc_setup()
{
	ADMUX |= (1<<REFS0)|(0<<REFS1)|(1<<MUX1);//Enables VCC as ref voltage
	//write the remaining registers
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	ADCSRB |= (0<<ADTS0)|(0<<ADTS1)|(0<<ADTS2);
}

ISR(TIMER0_COMPA_vect)
{
	while(melody_counter<5000 && PIND &(1<<PD2)){
		OCR1A = ICR1-700;
		PORTD|=(1<<PD4);
		if(melody_counter<=2500)
		{
			OCR0A = 200;
		}
		
		else if(melody_counter<5000)
		{
			OCR0A = 50;
		}
		melody_counter++;
	}
	PORTD&=~(1<<PD4);
	melody_counter = 0;
}

ISR(ADC_vect)
{
	if(ADC>=256){//this will turn on the led if ADC value is >= than 512
		PORTD |= (1<<PD4);
	}
	if(ADC<512){//this will turn on the led if ADC value is >= than 512
		PORTD &= ~(1<<PD4);
	}
}

void USART_Init( unsigned int ubrr){
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

unsigned char USART_Receive( void ){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

int main(void)
{
	DDRB |= (1<<DDB1); //pinMode(pinb1, OUTPUT);
	DDRD |= (1<<DDD6);
	DDRD &= ~(1<<PD2);//Makes pin D2 as Input
	DDRD &= ~(1<<PD3);//Makes pin D3 as Input
	DDRD |= (1<<PD4);
	setPWM();
	setBuzzer();
	adc_setup();
	USART_Init(MYUBRR); //serial.begin(4800)
	OCR1A = ICR1 - 1200; //sets Servo to 0º position
	OCR1A = ICR1 - 800;
	OCR1A = ICR1 - 2100;
	sei();
	while (1)
	{
		//USART_Receive();
		//if(USART_Receive()	== 65)
		//{
		//	PORTD |= (1<<PD4);
		//	_delay_ms(1000);
		//	PORTD &= ~(1<<PD4);
		//	_delay_ms(1000);
		//}
		if(PIND &(1<<PD2)) //checks if push button is pressed
		{
			// if button in PD2 gets pressed the servo opens to -90º
			TCCR0B |=(1<<CS00);//set it to one
		}
		else if(PIND &(1<<PD3))
		{
			OCR1A = ICR1 - 2100; //if button in PD3 gets pressed the servo opens to 90º
			UDR0 = 66;
		}
		else
		{
			OCR1A = ICR1 - 1200; //if there is no button pressed servo is closed at 0º
			TCCR0B &= ~(1<<CS00);//set it to one
		}
	}
}
