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
#define RABBIT_Y snake->rabbit->y

static void draw_body(snake_t *snake){
    for(uint8_t pxl = 0; pxl < snake->length; pxl++){
        max7219_set_pixel(snake->led_matrix, snake->body_x[pxl], snake->body_y[pxl]);
    }
}

static void draw_rabbit(snake_t *snake){
    max7219_set_pixel(snake->led_matrix, snake->rabbit->x, snake->rabbit->y);
}


static bool snake_check_collision(snake_t *snake, uint8_t next_x, uint8_t next_y){
    if(next_x > 7 || next_y > 7){
        return true;
    }
    
    for(uint8_t pxl = 0; pxl < snake->length - 1; pxl++){
        if(next_x == snake->body_x[pxl] && next_y == snake->body_y[pxl]){
            return true;
        }
    }

    return false;
}


//policz przyszly punkt. Jesli jest taki sam jak krolik to dlugosc zwiekszona o 1 i glowa weza w miejscu krolika, jesli nie to zwykly ruch

static void snake_count_body(snake_t *snake){
    uint8_t next_head_x = HEAD_X;
    uint8_t next_head_y = HEAD_Y;

    switch(snake->direction){
        case UP:
            next_head_y -= 1;
            break;
        case DOWN:
            next_head_y += 1;
            break;
        case LEFT:
            next_head_x -= 1;
            break;
        case RIGHT:
            next_head_x += 1;
            break;
        default:
            break; 
    }

    if(snake_check_collision(snake, next_head_x, next_head_y)){
        snake->collision = true;
    }else if(next_head_x == RABBIT_X && next_head_y == RABBIT_Y){
        snake->length += 1;
        HEAD_X = next_head_x;
        HEAD_Y = next_head_y;
    }else{
        for(uint8_t pxl = 0; pxl < snake->length - 1; pxl++){
            snake->body_x[pxl] = snake->body_x[pxl+1];
            snake->body_y[pxl] = snake->body_y[pxl+1];
	    }
        HEAD_X = next_head_x;
        HEAD_Y = next_head_y;
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
    snake->collision = false;
    snake->length = 5;
    for(uint8_t pxl = 0; pxl < snake->length; pxl++){
        snake->body_x[pxl] = pxl + 2;
        snake->body_y[pxl] = 4; 
    }

	srand(snake->rabbit->sead);
    snake_count_rabbit(snake);
}

keys_t snake_check_keyboard(snake_t *snake){
    return keyboard_check_key(snake->keyboard);
}


void snake_check_direction(snake_t *snake){
	keys_t key = keyboard_check_key(snake->keyboard);
    switch(key){
        case keyUP:
            if(!(HEAD_Y > NECK_Y)){
                snake->direction = UP;
            }
            break;
        case keyLEFT:
            if(!(HEAD_X > NECK_X)){
                snake->direction = LEFT;
            }
            break;
        case keyRIGHT:
            if(!(HEAD_X < NECK_X)){
                snake->direction = RIGHT;
            }
            break;
        case keyDOWN:
            if(!(HEAD_Y < NECK_Y)){
                snake->direction = DOWN;
            }
            break;
        default:
            break;
    }
}

void snake_count(snake_t *snake){
	if(snake->direction != NO_DIRECTION){
		snake_count_body(snake);
	}
    if(snake_has_eaten_rabbit(snake)){
	    snake_count_rabbit(snake);
    }
}

void snake_draw(snake_t *snake){
	max7219_clear_matrix(snake->led_matrix);
	draw_body(snake);
    draw_rabbit(snake);
}
