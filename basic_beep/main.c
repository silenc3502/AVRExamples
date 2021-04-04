/*
 */

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRC = 0xff;

    while(1)
    {
        PORTC = 0x01;
        _delay_ms(100);
        PORTC = 0x00;
        _delay_ms(100);
    }

    return 0;
}
