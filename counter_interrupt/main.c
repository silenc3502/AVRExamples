/*
 */

#include <avr/io.h>

#define F_CPU       16000000UL
#include <util/delay.h>

#include <avr/interrupt.h>

#define sbi(PORTx, BITx)        (PORTx |= (1 << BITx))
#define cbi(PORTx, BITx)        (PORTx &= ~(1 << BITx))

volatile unsigned int counter = 0;

SIGNAL(TIMER0_COMPA_vect)
{
    counter++;
}

void counter_init(void)
{
    cbi(SREG, 7);

    TCCR0A = 0;
    TCCR0B = 0;

    DDRB = 0x02;
    PORTB = 0x00;

    // CTC Mode, Use OCRA pin
    TCCR0A = (1 << WGM01);
    // clk / 64 => 16 MHz / 64 = 250 KHz => 0.004 ms
    TCCR0B = (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << OCIE0A);
    TCNT0 = 0;

    // 1 ms / 0.004 ms - 1 = 249
    // 249 * 0.004 ms = 1 ms
    OCR0A = 249;

    sbi(SREG, 7);
}

int main(void)
{
    counter_init();

    while(1)
    {
        if (counter == 1000)
        {
            PORTB ^= 0x02;
            counter = 0;
        }
    }

    return 0;
}
