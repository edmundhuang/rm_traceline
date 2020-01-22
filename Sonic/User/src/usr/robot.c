#include "dev.h"
#include "tutorial_lib.h"
#include "robot.h"
#include "util.h"

int8_t step = 0;
int8_t is_finish = 0;

int8_t sonic_ball_id = 1;
int8_t sonic_left_id = 2;
int8_t sonic_right_id = 3;
int8_t sonic__tail_id = 4;

int16_t default_delay = 100;

int16_t ball_distance = 100;

void wait_for_ball() {
	mute_buzzer();
	step = 1;
	is_finish = 0;

	while (1) {
		if (is_finish == 1)
			break;

		task_delay(default_delay);

		sonic_mesg_request(sonic_ball_id);
//		task_delay(default_delay);
	}

	set_buzzer(1000, 200, 200, step);
}

void straight_back() {
	step = 2;
	is_finish = 0;
	while (1) {
		if (is_finish == 1)
			break;

		move_back();

		task_delay(default_delay);
		sonic_mesg_request(sonic_left_id);
		task_delay(default_delay);
		sonic_mesg_request(sonic_right_id);
	}

	set_buzzer(500, 200, 500, step);
}

void move_back(int16_t seconds)
{

}

void sonic_task(uint8_t send_id, int16_t distance) {
	switch (step) {
	case 1:
		step1(send_id, distance);
		break;
	case 2:
		step2(send_id, distance);
		break;
	default:
		break;
	}
}

void step1(uint8_t send_id, int16_t distance) {
	if (send_id == sonic_ball_id) {
		if (distance < ball_distance) {
			is_finish = 1;
		}
	}
}

int8_t left_right = 0;
int16_t left_wall_distance = 50;

void step2(uint8_t send_id, int16_t distance) {
	if (left_right == 0) {
		if (distance < left_wall_distance && distance>10) {
			if (send_id == sonic_left_id) {
				left_right = 1;
//				set_buzzer(1200,200,200,2);
			}

			if (send_id == sonic_right_id) {
//				set_buzzer(200,200,200,5);
				left_right = 2;
			}
		}
	}



//	task_delay(1000);

}

void infra_task(uint8_t enable) {
//	set_buzzer(50, 500);
//	reverse=enable;
}
