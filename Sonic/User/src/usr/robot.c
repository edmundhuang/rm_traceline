#include "dev.h"
#include "tutorial_lib.h"
#include "robot.h"
#include "util.h"
#include "chassis.h"

#define sonic_ball_id  1
#define sonic_left_id  2
#define sonic_right_id  3
#define sonic_tail_id  4

int8_t step = 0;
int8_t is_finish = 0;

int16_t default_delay = 50;

int16_t ball_distance = 100;

int8_t test_step[] = { 2, 2, 3, 4 };
int8_t step_num = 4;

int8_t left_right = 0;   //-1:left, 1:right
int16_t wall_distance = 50;
int16_t target_distance = 100;

int16_t max_safe_distance = 200;
int16_t min_safe_distance = 10;

float run_speed=0.2;
float run_direction=0;

float adjust_speed=0.1;


void wait_for_ball() {
	mute_buzzer();
	step = 1;
	is_finish = 0;

	int8_t test = find_index(test_step, step_num, step);

	if (test == -1)
		return;

	step_start(step, left_right);

	while (1) {
		if (is_finish == 1)
			break;

		task_delay(default_delay);

		sonic_mesg_request(sonic_ball_id);
	}

	step_finish(step);
}

void straight_back() {
	step = 2;
	is_finish = 0;

	int8_t test = find_index(test_step, step_num, step);

	if (test == -1)
		return;

	step_start(step, left_right);

	//back direction;
	run_direction=-1;
	motor_run(0, run_direction * run_speed, 0);

	while (1) {
		if (is_finish == 1)
			break;

		task_delay(default_delay);

		if (left_right == 0) {
			sonic_mesg_request(sonic_left_id);
			sonic_mesg_request(sonic_right_id);
		} else {
			if (left_right == -1)
				sonic_mesg_request(sonic_left_id);
			else
				sonic_mesg_request(sonic_right_id);
		}

		sonic_mesg_request(sonic_tail_id);
	}

	motor_stop();

	step_finish(step);
}

void horizontal_move() {
	step = 3;
	is_finish = 0;

	int8_t test = find_index(test_step, step_num, step);

	if (test == -1)
		return;

	step_start(step, left_right);

	//back direction;
	run_direction=left_right;

	//move at X Axis
	motor_run(run_direction*run_speed, 0, 0);

	while (1) {
		if (is_finish == 1)
			break;

		task_delay(default_delay);

		if (left_right == -1)
			sonic_mesg_request(sonic_left_id);
		else
			sonic_mesg_request(sonic_right_id);

		sonic_mesg_request(sonic_tail_id);
	}

	motor_stop();

	step_finish(step);
}

void straight_forward() {
	step = 4;
	is_finish = 0;

	int8_t test = find_index(test_step, step_num, step);

	if (test == -1)
		return;

	step_start(step, left_right);

	//forward direction;
	run_direction=1;

	//move at Y Axis
	motor_run(0, run_direction*run_speed, 0);

	while (1) {
		if (is_finish == 1)
			break;

		if (left_right == -1)
			sonic_mesg_request(sonic_left_id);
		else
			sonic_mesg_request(sonic_right_id);

		task_delay(default_delay);
	}

	motor_stop();

	step_finish(step);
}

void move_back(int16_t seconds) {

}

void sonic_task(uint8_t send_id, int16_t distance) {
	switch (step) {
	case 1:
		step1(send_id, distance);
		break;
	case 2:
		step2(send_id, distance);
		break;
	case 3:
		step3(send_id, distance);
		break;
	case 4:
		step4(send_id, distance);
		break;
	default:
		break;
	}
}

//when ball was received by our car
void step1(uint8_t send_id, int16_t distance) {
	if (send_id == sonic_ball_id) {
		if (distance < ball_distance) {
			is_finish = 1;
		}
	}
}

void step2(uint8_t send_id, int16_t distance) {
	switch (send_id) {
	case sonic_left_id:
		if (left_right == 0) {
			if (distance < wall_distance && distance > 10)
				left_right = -1;
		} else {
			//如果車沒擺正，則需要考慮糾偏。
			//离太远
			if (distance > max_safe_distance) {
				motor_run(-1* adjust_speed, run_direction* run_speed, 0);
			} else {
				if (distance < min_safe_distance)
					motor_run(adjust_speed, run_direction* run_speed, 0);
				else
					motor_run(0, run_direction* run_speed, 0);
			}
		}

		break;
	case sonic_right_id:
		if (left_right == 0) {
			if (distance < wall_distance && distance > 10)
				left_right = 1;
		} else {
			if (distance > max_safe_distance) {
				motor_run(adjust_speed, run_direction* run_speed, 0);
			} else {
				if (distance < min_safe_distance)
					motor_run(-1*adjust_speed, run_direction* run_speed, 0);
				else
					motor_run(0, run_direction* run_speed, 0);
			}
		}

		//如果車沒擺正，則需要考慮糾偏。

		break;
	case sonic_tail_id:
		if (distance < target_distance) {
			is_finish = 1;
		}
		break;
	default:
		break;
	}
}

//horizontal move
void step3(uint8_t send_id, int16_t distance) {
	switch (send_id) {
	case sonic_left_id:
	case sonic_right_id:
		if (distance < target_distance)
			is_finish = 1;

		break;
	case sonic_tail_id:
		if (distance > max_safe_distance) {
			motor_run(run_direction*run_speed, -1* adjust_speed, 0);
		}
		else
		{
			if(distance<min_safe_distance)
				motor_run(run_direction*run_speed, adjust_speed, 0);
			else
				motor_run(run_direction*run_speed, 0, 0);
		}

		break;
	default:
		break;
	}
}

int16_t out_of_range=1000;

//move forward
void step4(uint8_t send_id, int16_t distance) {
	if(distance> out_of_range )
	{
		is_finish=1;
		return;
	}

	if(distance > max_safe_distance)
	{
		motor_run(-1*adjust_speed,run_direction*run_speed, 0);
		return;
	}

	if(distance < min_safe_distance)
	{
		motor_run(adjust_speed,run_direction*run_speed, 0);
		return;
	}

	motor_run(0,run_direction*run_speed, 0);
}
