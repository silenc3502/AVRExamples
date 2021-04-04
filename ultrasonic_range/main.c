/*
 */

#define F_CPU               16000000L
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define PRESCALER           1024

static volatile uint32_t first_reading = 0;
static volatile uint32_t second_reading = 0;
static volatile uint32_t duty_cycle = 0;

void uart_init(void)
{
    UCSR0A |= _BV(U2X0);

    UBRR0H = 0x00;
    UBRR0L = 207;

    UCSR0C |= 0x06;

    UCSR0B |= _BV(RXEN0);
    UCSR0B |= _BV(TXEN0);
}

unsigned char uart_receive(void)
{
    while (!(UCSR0A & (1 << RXC0)))
        ;

    return UDR0;
}

void uart_transmit(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    UDR0 = data;
}

void uart_print_string(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        uart_transmit(str[i]);
    }
}

void uart_print_8bit_num(uint8_t no)
{
    char num_string[4] = "0";
    int i, index = 0;

    if (no > 0)
    {
        for (i = 0; no != 0; i++)
        {
            num_string[i] = no % 10 + '0';
            no = no / 10;
        }

        num_string[i] = '\0';
        index = i - 1;
    }

    for (i = index; i >= 0; i--)
    {
        uart_transmit(num_string[i]);
    }
}

void HCSR04_Init(void)
{
	cli(); //clear prior interrupts
	/*Fast PWM Configuration*/
	DDRD |= (1<<DDD6); //set PD6 as output
	TCCR0A = (1<<COM0A1)|(1<<COM0A0)|(1<<WGM01)|(1<<WGM00);
	TCCR0B |= (1<<CS01); //prescaler = 8 for timer 0
	OCR0A = 235; //10uS trigger pulse, 118uS off-time (128uS repetition rate)
	/*Input Capture configuration*/
	//Timer 1 running in normal mode
	DDRB &= ~(1<<DDB0); //PB0 as input (ICP1)
	TCCR1B = (1<<ICNC1)|(1<<ICES1)|(1<<CS11); //noise canceling + positive edge detection for input capture and Prescaler = 8.
	sei();//enable global interrupts
	TIMSK1 |= (1<<ICIE1); //enable timer1 input capture interrupt
}

uint32_t getDistance(void)
{
	static uint32_t echo_pulse_uS;
	static uint32_t distance_cm;
        //32768uS = 65536 clock ticks for Timer 1 with prescaler = 8
	echo_pulse_uS = (float)duty_cycle * 32768 / 65536;
	distance_cm = echo_pulse_uS * 0.034 / 2;
	return distance_cm;
}

ISR(TIMER1_CAPT_vect)
{
	if ((TCCR1B & (1<<ICES1)) == (1<<ICES1))
	{
		first_reading = ICR1;
	}
	else
	{
		second_reading = ICR1;
	}

	if (first_reading != 0 && second_reading != 0)
	{
		duty_cycle = second_reading - first_reading;
		first_reading = 0;
		second_reading = 0;
	}

	TCCR1B ^= (1<<ICES1); //toggle edge detection bit
	TIFR1 = (1<<ICF1);//clear Input Capture Flag
}

int main(void)
{
    uint32_t distance;

    DDRC |= 0x01;
    DDRC &= ~0xFD;

    uart_init();
    HCSR04_Init();

    while(1)
    {
        distance = getDistance();

        uart_print_string("distance(cm) = ");
        uart_print_8bit_num(distance);
        uart_transmit('\n');

        _delay_ms(1000);
    }

    return 0;
}
