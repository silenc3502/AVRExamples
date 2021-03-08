/*
 */

#include <avr/io.h>

#define F_CPU       16000000UL
#include <util/delay.h>

#include <avr/interrupt.h>

#define sbi(PORTx, BITx)        (PORTx |= (1 << BITx))
#define cbi(PORTx, BITx)        (PORTx &= ~(1 << BITx))

unsigned char counter = 0;

SIGNAL(TIMER0_OVF_vect)
{
    if (counter == 125)
    {
        PORTB = 0x02;
        counter = 0;
    }
    else
    {
        PORTB = 0x00;
        counter++;
    }
}

void overflow_timer_init(void)
{
    cbi(SREG, 7);

    TCCR0A = 0;
    TCCR0B = 0;

    DDRB = 0x02;
    PORTB = 0x02;

    // prescale 1024
    // clk = 16000000 / 1024 = 15625;
    TCCR0B = (1 << CS02) | (1 << CS00);
    // 1 / clk => t = 64us
    // 64us * 125 = 8ms
    TCNT0 = 131;

    sbi(TIMSK0, TOIE0);
    sbi(SREG, 7);
}

int main(void)
{
    overflow_timer_init();

    while(1)
    {
        ;
    }

    return 0;
}
