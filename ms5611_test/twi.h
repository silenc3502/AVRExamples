#ifndef __TWI_H__
#define __TWI_H__

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void i2c_init (void);
unsigned char i2c_start (unsigned char);
unsigned char i2c_repeat_start (unsigned char);
void i2c_stop (void);
unsigned char i2c_write (unsigned char);
unsigned char i2c_read_ack (void);
unsigned char i2c_read_nack (void);

#endif
