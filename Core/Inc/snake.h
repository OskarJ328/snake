/*
 * snake.h
 *
 *  Created on: Apr 4, 2026
 *      Author: ozker
 */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#include "stdint.h"
#include "stdbool.h"
#include "MAX7219.h"
#include "keyboard.h"

typedef enum{
	NO_DIRECTION,
	UP,
	DOWN,
	LEFT,
	RIGHT
}snake_direction_t;

typedef enum{
    keyUP = 3,
    keyDOWN = 11,
    keyLEFT = 6,
    keyRIGHT = 8,
    keyENTER = 7
}keys_t;

typedef enum{
    MENU,
    GAME,
    PAUSE,
    END
}game_state_t;

typedef struct{
	uint8_t x;
	uint8_t y;
	uint16_t sead;
}rabbit_t;

typedef struct{
    uint8_t body_x[64];
    uint8_t body_y[64];
    uint8_t length;
    snake_direction_t direction;
    bool collision;
    rabbit_t *rabbit;

    uint16_t time_min;
    uint16_t time_s;
    uint16_t score;
    max7219_t *led_matrix;
    keyboard_t *keyboard;
}snake_t;




void snake_init(snake_t *snake);
keys_t snake_check_keyboard(snake_t *snake);
void snake_check_direction(snake_t *snake);
void snake_count(snake_t *snake);
void snake_draw(snake_t *snake);



#endif /* INC_SNAKE_H_ */
