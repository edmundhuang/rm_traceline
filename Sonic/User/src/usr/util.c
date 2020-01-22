#include "dev.h"
#include "tutorial_lib.h"
#include "chassis_task.h"

buzzer_ctrl_t buzzer_ctrl; //定义蜂鸣器模块相关的结构体变量

void set_buzzer(int16_t frequency, int16_t duration, int16_t interval,
		int16_t times) {

	for (int i = 0; i < times; i++) {
		buzzer(frequency);
		task_delay(duration);
		mute_buzzer();
		task_delay(interval);
	}
}

void buzzer(int16_t frequency) {
	buzzer_ctrl.freq = frequency;  //设置蜂鸣器模块频率为1000Hz
	buzzer_ctrl.enable = 1;
	buzzer_ctrl_data(1, buzzer_ctrl);
}

void mute_buzzer() {
	buzzer_ctrl.enable = 0;
	buzzer_ctrl_data(1, buzzer_ctrl);
}

#define RC_MAX_VALUE      1000.0f

/* 底盘移动最大速度，单位是毫米每秒 */
#define MAX_CHASSIS_VX_SPEED 500
#define MAX_CHASSIS_VY_SPEED 500
/* 底盘旋转最大速度，单位是度每秒 */
#define MAX_CHASSIS_VR_SPEED 200

chassis_t chassis;
int16_t wheel_rpm[4];
//int16_t speed[];

motor_ctrl_t moto_ctrl;

void enable_motor(int8_t enable) {
	moto_ctrl.m1_enable = enable;
	moto_ctrl.m2_enable = enable;
	moto_ctrl.m3_enable = enable;
	moto_ctrl.m4_enable = enable;
}

void move_y(int16_t y) {

	moto_ctrl.m1_rpm = -y;
	moto_ctrl.m2_rpm = y;
	moto_ctrl.m3_rpm = y;
	moto_ctrl.m4_rpm = -y;

	motor_ctrl_data(1, moto_ctrl);
}

void move_x(int16_t x) {

	moto_ctrl.m1_rpm = x;
	moto_ctrl.m2_rpm = x;
	moto_ctrl.m3_rpm = -x;
	moto_ctrl.m4_rpm = -x;

	motor_ctrl_data(1, moto_ctrl);
}

void rotate(int16_t x) {
	moto_ctrl.m1_rpm = x;
	moto_ctrl.m2_rpm = x;
	moto_ctrl.m3_rpm = -x;
	moto_ctrl.m4_rpm = -x;

	motor_ctrl_data(1, moto_ctrl);
}

