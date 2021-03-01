/*
 */

#include <avr/io.h>

#define F_CPU       16000000L
#include <util/delay.h>

int main(void)
{
    DDRB = 0x20;

    while(1)
    {
        if((PINB & 0x01) == 0x00)
        {
            PORTB = 0x20;
            _delay_ms(500);
        }
        else
        {
            PORTB = 0x00;
            _delay_ms(500);
        }
    }

    return 0;
}
