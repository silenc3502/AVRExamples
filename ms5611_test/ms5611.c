#define F_CPU 16000000UL

#include "ms5611.h"
#include "twi.h"
#include "uart.h"

int32_t _ms5611_temp;
uint32_t _ms5611_pres;

struct _ms5611_cal
{
	uint16_t sens, off, tcs, tco, tref, tsens;
}
ms5611_cal;

void ms5611_reset (void)
{
	i2c_start((MS5611_ADDR << 1) | I2C_WRITE);
	i2c_write(RESET);
	i2c_stop();
	_delay_ms(10);
}

uint32_t ms5611_read_cal_reg (uint8_t reg)
{
	uint8_t PROM_dat1;
	uint8_t PROM_dat2;

	uint16_t data;

	i2c_start((MS5611_ADDR << 1) | I2C_WRITE);
	i2c_write(MS5611_CMD_PROM(reg));
	i2c_repeat_start(MS5611_ADDR << 1 | I2C_READ);

	PROM_dat1 = i2c_read_ack();
	PROM_dat2 = i2c_read_nack();
	i2c_stop();

	printf("PROM_dat1:%d, %d\n", PROM_dat1, PROM_dat2);

	data = ( PROM_dat1 << 8 ) + (uint16_t)PROM_dat2;

	return data;
}

void ms5611_init (void)
{
	ms5611_reset();
	uart_string_transmit("ms5611 reset ok\n");

	ms5611_cal.sens  = ms5611_read_cal_reg(1);
	ms5611_cal.off   = ms5611_read_cal_reg(2);
	ms5611_cal.tcs   = ms5611_read_cal_reg(3);
	ms5611_cal.tco   = ms5611_read_cal_reg(4);
	ms5611_cal.tref  = ms5611_read_cal_reg(5);
	ms5611_cal.tsens = ms5611_read_cal_reg(6);

	_delay_ms(1000);
}

uint32_t ms5611_conv_read_adc (uint8_t command)
{
	uint8_t rv1;
	uint8_t rv2;
	uint8_t rv3;

	uint32_t adc_data;

	i2c_start((MS5611_ADDR << 1) | I2C_WRITE);
	i2c_write(command);
	i2c_stop();
	_delay_ms(10); //conversion Time delay

	i2c_start((MS5611_ADDR << 1) | I2C_WRITE);
	i2c_write(CMD_ADC_READ);
	i2c_repeat_start(MS5611_ADDR <<1 | I2C_READ);

	rv1 = i2c_read_ack();
	rv2 = i2c_read_ack();
	rv3 = i2c_read_nack();
	i2c_stop();

	adc_data = ((uint32_t)rv1 << 16) + ((uint32_t)rv2 << 8) + (uint32_t)rv3;

	return adc_data;
}

void ms5611_measure (void)
{
	int32_t temp_raw, press_raw, dt;
	int64_t sens, off;

	temp_raw = ms5611_conv_read_adc(CONV_D2_4096);
	press_raw = ms5611_conv_read_adc(CONV_D1_4096);

	dt = temp_raw - ((int32_t)ms5611_cal.tref << 8);
	_ms5611_temp = 2000 + ((dt*((int64_t)ms5611_cal.tsens)) >> 23);
	off = ((int64_t)ms5611_cal.off << 16) + (((int64_t)dt*(int64_t)ms5611_cal.tco) >> 7);
	sens = ((int64_t)ms5611_cal.sens << 15) + ((int64_t)ms5611_cal.tcs*dt >> 8);
	_ms5611_pres = ((((uint64_t)press_raw*sens) >> 21) - off) >> 15;
}

double ms5611_getAltitude (void)
{
	double alt;
	alt = (1 - pow(_ms5611_pres / (double)101325, 0.1903)) / 0.0000225577;
	return alt;
}

uint32_t ms5611_getPress (void)
{
	return _ms5611_pres;
}

int32_t ms5611_getTemp (void)
{
	return _ms5611_temp;
}
