/*
 * util.h
 *
 *  Created on: 2020年1月18日
 *      Author: User
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

void set_buzzer(int16_t frequency, int16_t duration,int16_t interval, int16_t times);
void mute_buzzer();
void buzzer(int16_t frequency);

void enable_motor(int8_t enable);
void move_x(int16_t x);
void move_y(int16_t y);

void rotate(int16_t x);

#endif /* INC_UTIL_H_ */
