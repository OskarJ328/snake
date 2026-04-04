/*
 * keyboard.c
 *
 *  Created on: Apr 4, 2026
 *      Author: ozker
 */

#include "keyboard.h"

uint8_t keyboard_check_key(keyboard_t *keyboard){
    for(uint8_t row = 0; row < keyboard->rows; row++){
        HAL_GPIO_WritePin(keyboard->outputs[row].port, keyboard->outputs[row].pin, GPIO_PIN_RESET);
        for(uint8_t column = 0; column < keyboard->columns; column++){
            if(HAL_GPIO_ReadPin(keyboard->inputs[column].port, keyboard->inputs[column].pin) == GPIO_PIN_RESET){
                uint8_t key = row * keyboard->columns + column + 1;
                HAL_GPIO_WritePin(keyboard->outputs[row].port, keyboard->outputs[row].pin, GPIO_PIN_SET);
                return key;
            }
            
        }
        HAL_GPIO_WritePin(keyboard->outputs[row].port, keyboard->outputs[row].pin, GPIO_PIN_SET);
    }
    return 0;
}

void keyboard_init(keyboard_t *keyboard){
    for(uint8_t row = 0; row < keyboard->rows; row++){
        HAL_GPIO_WritePin(keyboard->outputs[row].port, keyboard->outputs[row].pin, GPIO_PIN_SET);
    }
    
}
