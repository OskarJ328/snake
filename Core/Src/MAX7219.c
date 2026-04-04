/*
 * MAX7219.c
 *
 *  Created on: Mar 26, 2026
 *      Author: ozker
 */

#include "MAX7219.h"

#define MAX7219_DELAY 100

#define MAX7219_DIGIT0_REG 0x1
#define MAX7219_DECODE_REG 0x9
#define MAX7219_INTENSITY_REG 0xA
#define MAX7219_SCAN_LIMIT_REG 0xB
#define MAX7219_SHUTDOWN_REG 0xC
#define MAX7219_DISPLAY_TEST_REG 0xF

#define MAX7219_SHUTDOWN 0x0
#define MAX7219_NO_DECODE 0x0
#define MAX7219_NO_SHUTDOWN 0x1
#define MAX7219_DISPLAY_ALL_DIGITS 0x7
#define MAX7219_NO_TEST 0x0

static void max7219_write(max7219_t *max, uint8_t reg, uint8_t val){
	uint8_t data[2] = {reg, val};
	HAL_GPIO_WritePin(max->cs_port, max->cs_pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(max->spi_handle, data, 2, MAX7219_DELAY);
	HAL_GPIO_WritePin(max->cs_port, max->cs_pin, GPIO_PIN_SET);
}

void max7219_init(max7219_t *max){
	max7219_write(max, MAX7219_SHUTDOWN_REG, MAX7219_SHUTDOWN);
	max7219_write(max, MAX7219_DECODE_REG, MAX7219_NO_DECODE);
	max7219_write(max, MAX7219_INTENSITY_REG, 0xA); // 0x0 - no light, 0xF - max brightness
	max7219_write(max, MAX7219_SCAN_LIMIT_REG, MAX7219_DISPLAY_ALL_DIGITS);
	max7219_write(max, MAX7219_DISPLAY_TEST_REG, MAX7219_NO_TEST);

	max7219_clear_matrix(max);
	
	max7219_write(max, MAX7219_SHUTDOWN_REG, MAX7219_NO_SHUTDOWN);
}

void max7219_set_pixel(max7219_t *max, uint8_t x, uint8_t y){
	if(x > 7){
		x = 7;
	}
	if(y > 7){
		y = 7;
	}
	max->buffer[y] |= 1 << x;
	max7219_write(max, MAX7219_DIGIT0_REG + y, max->buffer[y]);  
}

void max7219_reset_pixel(max7219_t *max, uint8_t x, uint8_t y){
	if(x > 7){
		x = 7;
	}
	if(y > 7){
		y = 7;
	}
	max->buffer[y] &= ~(1 << x);
	max7219_write(max, MAX7219_DIGIT0_REG + y, max->buffer[y]);  
}

void max7219_clear_matrix(max7219_t *max){
	for(uint8_t row = MAX7219_DIGIT0_REG; row < MAX7219_DIGIT0_REG + 8; row++){
		max7219_write(max, row, 0x00);
		max->buffer[row-1] = 0;
	}	
}
