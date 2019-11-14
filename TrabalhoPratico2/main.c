/*
 * TrabalhoPratico2.c
 *
 * Created: 03/06/2019 09:40:36
 * Author : Ricardo and Wilson Simoes
 * Course : Sistemas Eletronicos e de Computadores 1st Year
 * Curricular Unit: Microprocessadores e Microcontroladores
 */ 
#define F_CPU 1000000UL // Clock Speed
#define BAUD 4800 // Baud Rate
#define MYUBRR ((F_CPU/16/BAUD)-1) //

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
uint16_t melody_counter =0;
uint16_t val = 0;
uint16_t counter=0;
uint16_t counter2=0;

void setPWM() //function responsible to setup PWM
{
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0)|(1<<WGM11); //Register modified to have fast PWM
	
	TCCR1B |= (1<<WGM12) |(1<<WGM13)|(1<<CS10); //Register modified to have no PRESCALER and having ICR1 has top value
	
	ICR1 = 19999; /*PWM_FREQUENCY = F_CPU/N*(1+TOP) PWM CALCULATED FOR 50HZ*/
}

void setBuzzer()
{
	TCCR0A |=(1<<COM0A0) /* Toggle OC0A on Compare Match*/
		   |(0<<COM0A1) /**/
		   |(1<<WGM01); //clear on time compare
	
	TCCR0B |=(0<<CS00);//To enable the counter register must be set to one
	
	TIMSK0 |=(1<<OCIE0A)|(1<<TOIE0);//enables overflow interrupt
	
	OCR0A = 0; // On Compare Register 0 A is set to have the value 0
}

void adc_setup()
{
	ADMUX |= (1<<REFS0)|(0<<REFS1)|(1<<MUX1);//Enables VCC as ref voltage also selects ADC2 analog channel
	
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //enables ADC, starts conversion, auto trigger enabled, ADC presacler set to 128
	
	ADCSRB |= (0<<ADTS0)|(0<<ADTS1)|(0<<ADTS2); // trigger set for free running mode
}

void USART_Init( unsigned int ubrr)
{ // function responsible to set up RX and TX communication
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8); //sets the baud rate value
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0); // register enables RX and TX and also their respective interrupts
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}


unsigned char USART_Receive( void )
{ // function responsible to read RX buffer
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0; // returns the value read in RX
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

ISR(TIMER0_COMPA_vect) // interruption enabled on TIMER 0A compare
{
	while(melody_counter<5000  && (~PIND&(1<<PD2))){ // while meloduy_counter is minor thant 5000 (hardcoded value) 
													//and while button is not pressed
		PORTB|=(1<<PB2); // turn on LED
		OCR1A= ICR1 - 700; // open servo to -90º
			if(melody_counter<=2500)
			{
				OCR0A = 200; //sets value of counter one top to 200 (0-255)
			}
		
			else if(melody_counter<5000)
			{
				OCR0A = 50; //after 2500 loops sets top value of counter to 50
			} //loop with if else statement responsible to produce a melody
		melody_counter++; // increments variable in +1
	}
	PORTB&=~(1<<PB2);// after the loop led is turned off
	melody_counter = 0;// variable is set 0 again
}

ISR(ADC_vect) //interruption to run on ADC update not used for now
{
}

ISR(USART_RX_vect) // RX interrupt
{
	val = USART_Receive(); // stores the value read in the function USART_receive
		if(val == 65) // If value equals 65 or 'A' 
		{
			TCCR0B |=(1<<CS00); // it enables time counter 0A and activates the corresponding interrupt
		}
}

ISR(USART_TX_vect)
{
	UDR0 = 0x00;
}

int main(void)
{
	DDRB |= (1<<DDB1);  //Sets PB1 as an Output
	DDRB |= (1<<DDB2); //Sets PB2 as an Output
	DDRD |= (1<<DDD6); //Sets PD6 as an Output
	DDRD &= ~(1<<PD2); //Makes PD2 as Input
	DDRD |= (1<<PD4); //Makes PD2 as Output
	setPWM(); // calls function setPWM() on main
	setBuzzer(); // calls function setBuzzer() on main
	adc_setup(); // calls adcSetup() on main
	USART_Init(MYUBRR); //calls USART_Init on main passing baud rate as parameter
	OCR1A = ICR1 - 1200; // sets the position of the servo to 0º
	sei(); // it enables interrupts
	while (1) 
    {
		if(PIND&(1<<PD2)) //checks if push button is pressed
		{
			while(counter<(ADC*20)) // runs the equivalence of 20 times the value of the potentiometer to send the communication
			{
				counter+=2;//it increments the value by 2 at the time
			}
			counter = 0; // resets the counter
			USART_Transmit('C');//sends 'C' to the arduino via USART_Transmit function, passing the char as parameter
			PORTB&=~(1<<PB2); // turns off LED
			OCR1A = ICR1 - 1200; //sets Servo back to position 0º
			TCCR0B &= ~(1<<CS00);	//turns of timer 0 where the buzzer is connected	
		}
		
	}
}
