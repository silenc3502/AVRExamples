/*
 */

#include <avr/io.h>

#define F_CPU       16000000L
#include <util/delay.h>

// 7: DP
// 6: G
// 5: F
// 4: E

// 3: D
// 2: C
// 1: B
// 0: A
//                            0     1    2     3      4     5     6     7     8     9
//unsigned char digit[10] = { 0xeb, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0x3e, 0xd4, 0xfd, 0xd6 };

// 0: A, B, C, D, E, F    -> 0, 1, 2, 3, 4, 5
// 1: B, C                -> 1, 2
// 2: A, B, G, E, D       -> 0, 1, 3, 4, 6
// 3: A, B, C, D, G       -> 0, 1, 2, 3, 6
// 4: B, C, F, G          -> 1, 2, 5, 6
// 5: A, C, D, F, G       -> 0, 2, 3, 5, 6
// 6: C, D, E, F, G       -> 2, 3, 4, 5, 6
// 7: A, B, C, F          -> 0, 1, 2, 5
// 8: A, B, C, D, E, F, G -> 0, 1, 2, 3, 4, 5, 6
// 9: A, B, C, F, G       -> 0, 1, 2, 5, 6
unsigned char digit[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x27, 0x7f, 0x67 };
unsigned char digit_select[4] = { 0x01, 0x02, 0x04, 0x08 };
unsigned char fnd[4];

int main(void)
{
    DDRD = 0xff;
    DDRB = 0x0f;

    PORTB = 0x08;

    int i, count = 0;

    for(i = 0; i < 10; i++)
    {
        PORTD = digit[i];
        _delay_ms(1000);
    }

    while(1)
    {
        count++;

        if (count == 10000)
        {
            count = 0;
        }

        fnd[0] = (count / 1000) % 10;
        fnd[1] = (count / 100) % 10;
        fnd[2] = (count / 10) % 10;
        fnd[3] = count % 10;

        for (i = 0; i < 4; i++)
        {
            PORTD = digit[fnd[i]];
            PORTB = digit_select[i];

            _delay_ms(2);

            if (i % 2)
            {
                _delay_ms(1);
            }
        }
    }

    return 0;
}
