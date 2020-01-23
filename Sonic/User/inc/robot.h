/*
 * robo.h
 *
 *  Created on: 2020年1月12日
 *      Author: User
 */

#ifndef INC_ROBOT_H_
#define INC_ROBOT_H_

void sonic_task(uint8_t send_id, int16_t distance);

void wait_for_ball();
void straight_back();
void straight_forward();

void step1(uint8_t send_id, int16_t distance);
void step2(uint8_t send_id, int16_t distance);

//void infra_task(int8_t infra_state[]);
//void infra_task(uint8_t enable);

#endif /* INC_ROBOT_H_ */
