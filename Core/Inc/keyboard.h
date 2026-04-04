/*
 * keyboard.h
 *
 *  Created on: Apr 4, 2026
 *      Author: ozker
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#define MAX_PINS 16

#include "gpio.h"

typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
}gpio_t;

typedef struct{
	uint8_t rows;
	uint8_t columns;
	const gpio_t *inputs;
	const gpio_t *outputs;
}keyboard_t;


void keyboard_init(keyboard_t *keyboard);
uint8_t keyboard_check_key(keyboard_t *keyboard);

#endif /* INC_KEYBOARD_H_ */
