/*
 * keyboard.c
 *
 *  Created on: Apr 4, 2026
 *      Author: ozker
 */

#include "keyboard.h"
#include "stdbool.h"


static void keyboard_control_output(const gpio_t *output, GPIO_PinState state){
    HAL_GPIO_WritePin(output->port, output->pin, state);
}

static GPIO_PinState keyboard_check_input(const gpio_t *input){
    return HAL_GPIO_ReadPin(input->port, input->pin);
}


uint8_t keyboard_check_key(keyboard_t *keyboard){
    for(uint8_t row = 0; row < keyboard->rows; row++){
        keyboard_control_output(&keyboard->outputs[row], GPIO_PIN_RESET);
        for(uint8_t column = 0; column < keyboard->columns; column++){
            if(keyboard_check_input(&keyboard->inputs[column]) == GPIO_PIN_RESET){
                uint8_t key = row * keyboard->columns + column + 1;
                keyboard_control_output(&keyboard->outputs[row], GPIO_PIN_SET);
                return key;
            }
            
        }
        keyboard_control_output(&keyboard->outputs[row], GPIO_PIN_SET);
    }
    return 0;
}

void keyboard_init(keyboard_t *keyboard){
    for(uint8_t row = 0; row < keyboard->rows; row++){
        keyboard_control_output(&keyboard->outputs[row], GPIO_PIN_SET);
    }
}
