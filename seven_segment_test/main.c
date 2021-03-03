/*
 */

#include <avr/io.h>

#define F_CPU       16000000L
#include <util/delay.h>

int main(void)
{
    DDRD = 0xff;
    DDRB = 0x0f;

    PORTB = 0x08;

    // A
    PORTD = 0x01;
    _delay_ms(1000);

    // B
    PORTD = 0x02;
    _delay_ms(1000);

    // C
    PORTD = 0x04;
    _delay_ms(1000);

    // D
    PORTD = 0x08;
    _delay_ms(1000);

    // E
    PORTD = 0x10;
    _delay_ms(1000);

    // F
    PORTD = 0x20;
    _delay_ms(1000);

    // G
    PORTD = 0x40;
    _delay_ms(1000);

    // DP
    PORTD = 0x80;
    _delay_ms(1000);

    // Zero
    PORTD = 0xbf;
    _delay_ms(1000);

    while(1)
        ;

    return 0;
}
