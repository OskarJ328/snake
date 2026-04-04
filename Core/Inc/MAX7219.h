/*
 * MAX7219.h
 *
 *  Created on: Mar 26, 2026
 *      Author: ozker
 */

#ifndef INC_MAX7219_H_
#define INC_MAX7219_H_

#include "spi.h"
#include "gpio.h"

typedef struct{
	SPI_HandleTypeDef *spi_handle;
	GPIO_TypeDef *cs_port;
	uint16_t cs_pin;
	uint8_t buffer[8];
}max7219_t;

void max7219_init(max7219_t *max);
void max7219_set_pixel(max7219_t *max, uint8_t x, uint8_t y);
void max7219_reset_pixel(max7219_t *max, uint8_t x, uint8_t y);
void max7219_clear_matrix(max7219_t *max);
#endif /* INC_MAX7219_H_ */
