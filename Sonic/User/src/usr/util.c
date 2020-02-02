#include <chassis.h>
#include "dev.h"
#include "tutorial_lib.h"

buzzer_ctrl_t buzzer_ctrl; //定义蜂鸣器模块相关的结构体变量

void buzzer(int16_t frequency) {
	buzzer_ctrl.freq = frequency;  //设置蜂鸣器模块频率为1000Hz
	buzzer_ctrl.enable = 1;
	buzzer_ctrl_data(1, buzzer_ctrl);
}

void mute_buzzer() {
	buzzer_ctrl.enable = 0;
	buzzer_ctrl_data(1, buzzer_ctrl);
}

void set_buzzer(int16_t frequency, int16_t duration, int16_t interval,
		int16_t times) {

	for (int i = 0; i < times; i++) {
		buzzer(frequency);
		task_delay(duration);
		mute_buzzer();
		task_delay(interval);
	}
}

led_ctrl_t led_ctrl;

void set_led(uint8_t arr[]) {
	led_ctrl.led1 = arr[0];
	led_ctrl.led2 = arr[1];
	led_ctrl.led3 = arr[2];
	led_ctrl.led4 = arr[3];
	led_ctrl.led5 = arr[4];
	led_ctrl.led6 = arr[5];
	led_ctrl.led7 = arr[6];
	led_ctrl.led8 = arr[7];

	led_ctrl_data(1, led_ctrl);
}

int8_t find_index(int8_t arr[], int8_t num_elements, int8_t value) {
	int8_t i;
	for (i = 0; i < num_elements; i++) {
		if (arr[i] == value) {
			return (i); /* it was found */
		}
	}
	return (-1); /* if it was not found */
}

void step_start(int8_t step, int8_t direction) {
	set_buzzer(1000, 200, 500, step);

	uint8_t led[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	led[step - 1] = 1;

	switch (direction) {
	case -1:
		led[6] = 1;
		break;
	case 1:
		led[7] = 1;
		break;
	default:
		break;
	}

	set_led(led);
}

void step_finish(int8_t step) {
	set_buzzer(1000, 200, 200, step);
	set_buzzer(100, 100, 100, 1);
}
