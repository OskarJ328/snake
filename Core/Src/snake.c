/*
 * snake.c
 *
 *  Created on: Apr 4, 2026
 *      Author: ozker
 */
#include "snake.h"
#include "stdlib.h"

#define HEAD_X snake->body_x[snake->length - 1] 
#define HEAD_Y snake->body_y[snake->length - 1]
#define NECK_X snake->body_x[snake->length - 2] 
#define NECK_Y snake->body_y[snake->length - 2]
#define RABBIT_X snake->rabbit->x
#define RABBIT_Y snake->rabbit->x

static void draw_body(snake_t *snake){
    for(uint8_t pxl = 0; pxl < snake->length; pxl++){
        if(snake->body_x[pxl] > 7){
            return;
        }else if(snake->body_y[pxl] > 7){
            return;
        }
        max7219_set_pixel(snake->led_matrix, snake->body_x[pxl], snake->body_y[pxl]);
    }
}

static void draw_rabbit(snake_t *snake){
    max7219_set_pixel(snake->led_matrix, snake->rabbit->x, snake->rabbit->y);
}

static void snake_count_body(snake_t *snake){
	for(uint8_t pxl = 0; pxl < snake->length - 1; pxl++){
		snake->body_x[pxl] = snake->body_x[pxl+1];
        snake->body_y[pxl] = snake->body_y[pxl+1];
	}
    switch(snake->direction){
        case UP:
            snake->body_y[snake->length - 1] -= 1;
            break;
        case DOWN:
            snake->body_y[snake->length - 1] += 1;
            break;
        case LEFT:
            snake->body_x[snake->length - 1] -= 1;
            break;
        case RIGHT:
            snake->body_x[snake->length - 1] += 1;
            break;
        default:
            break; 
    }
}

static void snake_count_rabbit(snake_t *snake){
    bool collision;
    do {
        collision = false; 
        snake->rabbit->x = rand() % 8;
        snake->rabbit->y = rand() % 8;
        for(uint8_t pxl = 0; pxl < snake->length; pxl++){
            if(snake->rabbit->x == snake->body_x[pxl] && snake->rabbit->y == snake->body_y[pxl]){
                collision = true; 
                break;
            }
        }
    } while(collision);
}

static bool snake_has_eaten_rabbit(snake_t *snake){
    if(HEAD_X == snake->rabbit->x && HEAD_Y == snake->rabbit->y){
        return true;
    }
    return false;
}

void snake_init(snake_t *snake){
	snake->direction = NO_DIRECTION;
	srand(snake->rabbit->sead);
    snake_count_rabbit(snake);
    draw_rabbit(snake);
}

void snake_check_direction(snake_t *snake){
	uint8_t key = keyboard_check_key(snake->keyboard);
    switch(key){
        case 3:
            if(!(HEAD_Y > NECK_Y)){
                snake->direction = UP;
            }
            break;
        case 6:
            if(!(HEAD_X > NECK_X)){
                snake->direction = LEFT;
            }
            break;
        case 8:
            if(!(HEAD_X < NECK_X)){
                snake->direction = RIGHT;
            }
            break;
        case 11:
            if(!(HEAD_Y < NECK_Y)){
                snake->direction = DOWN;
            }
            break;
        default:
            break;
    }
}

void snake_count(snake_t *snake){
    if(snake_has_eaten_rabbit(snake)){
	    snake_count_rabbit(snake);
    }
	if(snake->direction != NO_DIRECTION){
		snake_count_body(snake);
	}
}

void snake_draw(snake_t *snake){
	max7219_clear_matrix(snake->led_matrix);
	draw_body(snake);
    draw_rabbit(snake);
}
