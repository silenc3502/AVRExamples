#ifndef __MS5611_H__
#define __MS5611_H__

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define I2C_WRITE	            0
#define I2C_READ	            1

#define MS5611_ADDR             0x76

#define RESET                   0x1E
#define CMD_ADC_READ            0x00
#define MS5611_CMD_PROM(reg)    (0xA0 + ((reg) << 1))
#define CMD_PROM_READ           0xA0

// Conversion Time
#define OSR_256                 1
#define OSR_512                 2
#define OSR_1024                3
#define OSR_2048                5
#define OSR_4096                10

#define CONV_D1_256         0x40
#define CONV_D1_512         0x42
#define CONV_D1_1024        0x44
#define CONV_D1_2048        0x46
#define CONV_D1_4096        0x48
#define CONV_D2_256         0x50
#define CONV_D2_512         0x52
#define CONV_D2_1024        0x54
#define CONV_D2_2048        0x56
#define CONV_D2_4096        0x58

void ms5611_reset (void);
uint32_t ms5611_read_cal_reg (uint8_t reg);
void ms5611_init (void);
uint32_t ms5611_conv_read_adc (uint8_t command);
void ms5611_measure (void);
double ms5611_getAltitude (void);
uint32_t ms5611_getPress (void);
int32_t ms5611_getTemp (void);

#endif
