/*
 * util.h
 *
 *  Created on: 2020年1月18日
 *      Author: User
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

void buzzer(int16_t frequency);
void mute_buzzer();
void set_buzzer(int16_t frequency, int16_t duration,int16_t interval, int16_t times);

void set_led(int8_t arr[]);

int8_t find_index(int8_t arr[], int8_t num_elements, int8_t value);

void step_start(int8_t step, int8_t direction);

void step_finish(int8_t step);

#endif /* INC_UTIL_H_ */
