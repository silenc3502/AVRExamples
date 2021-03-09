/*
 */

#include <avr/io.h>

#define F_CPU       16000000UL
#include <util/delay.h>

#include <avr/interrupt.h>

#define sbi(PORTx, BITx)        (PORTx |= (1 << BITx))
#define cbi(PORTx, BITx)        (PORTx &= ~(1 << BITx))

void fast_pwm_mode_for_servo(void)
{
    cbi(SREG, 7);

    // non-inverted PWM
    sbi(TCCR1A, COM1A1);
    // PRESCALER = 8, MODE 14 (FAST PWM), 16 MHz / 8 = 2 MHz
    sbi(TCCR1A, COM1B1);
    // start Bottom
    sbi(TCCR1A, WGM11);

    sbi(TCCR1B, WGM13);
    sbi(TCCR1B, WGM12);
    sbi(TCCR1B, CS11);

    // 20 ms -> 50 Hz
    ICR1 = 39999;

    DDRB = 0x02;

    sbi(SREG, 7);
}

int main(void)
{
    fast_pwm_mode_for_servo();

    while(1)
    {
        // -90 degree 1 ms
        OCR1A = 2000;
        _delay_ms(1000);

        // 0 degree 1.5 ms
        OCR1A = 3000;
        _delay_ms(1000);

        // 90 degree 2 ms
        OCR1A = 4000;
        _delay_ms(1000);

        // 0 degree 1.5 ms
        OCR1A = 3000;
        _delay_ms(1000);
    }

    return 0;
}
