/*
 */

#include <avr/io.h>

#define F_CPU   16000000UL
#include <util/delay.h>

#include <avr/interrupt.h>
#include <stdbool.h>

#define TC0_FAST_PWM        (1 << WGM00 | 1 << WGM01)
#define TC0_NONIVERT_PWM    (1 << COM01)
#define TC0_PRESCALE_32     (1 << CS00 | 1 << CS01)

#define TC1A_FAST_PWM       (1 << WGM10)
#define TC1_NONIVERT_PWM    (1 << COM1A1)
#define TC1_PRESCALE_64     (1 << CS11 | 1 << CS10)

#define TC1B_FAST_PWM       (1 << WGM12)

void init(void)
{
    DDRB |= _BV(PB1);

	TCCR1A |= _BV(COM1A1) | _BV(WGM10);
	TCCR1B |= _BV(CS10) | _BV(WGM12);
}

int main(void)
{
	init();

	uint8_t pwm = 0x00;
	bool up = true;

	for(;;) {

		OCR1A = pwm;

		pwm += up ? 1 : -1;
		if (pwm == 0xff)
			up = false;
		else if (pwm == 0x00)
			up = true;

		_delay_ms(10);
	}

    return 0;
}
