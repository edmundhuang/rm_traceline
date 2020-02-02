#include <chassis.h>
#include "dev.h"
#include "tutorial_lib.h"

#include "math.h"

/* 底盘移动最大速度，单位是毫米每秒 */
#define MAX_CHASSIS_VX_SPEED 500
#define MAX_CHASSIS_VY_SPEED 500
/* 底盘旋转最大速度，单位是度每秒 */
#define MAX_CHASSIS_VR_SPEED 200

/* 底盘轮距(mm) */
#define WHEELTRACK     250
/* 底盘轴距(mm) */
#define WHEELBASE      250
/* 云台偏移(mm) */
#define GIMBAL_OFFSET  0
/* 角度转弧度系数 */
#define RADIAN_COEF    57.3f
/* 底盘轮子周长(mm) */
#define PERIMETER      76
/* 底盘电机减速比 */
#define CHASSIS_DECELE_RATIO (1.0f/36.0f)
/* 单个电机速度极限，单位是每分钟转 */
#define MAX_WHEEL_RPM        15000   //15000rpm = 528mm/s
//MAX_WHEEL_RPM / 60 * PERIMETER * CHASSIS_DECELE_RATIO

/**
 * @param 输入参数1: vx左右平移速度(mm/s)，右为正方向
 *        输入参数2: vy前后平移速度(mm/s)，前为正方向
 *        输入参数3: vw底盘旋转速度(degree/s)，逆时针为正方向
 *        输入参数4: speed[] 4个电机转速(rpm)
 * @note  下面是电机轮子编号，左上角为0号
 * @map   1 %++++++% 0
 ++++
 ++++
 2 %++++++% 3
 */

chassis_t chassis;
motor_ctrl_t moto_ctrl;
static int16_t chassis_moto_speed_ref[4];

void motor_run(float vx, float vy, float vw) {
	moto_ctrl.m1_enable = 1;
	moto_ctrl.m2_enable = 1;
	moto_ctrl.m3_enable = 1;
	moto_ctrl.m4_enable = 1;

	VAL_LIMIT(vx, -1, 1);
	VAL_LIMIT(vy, -1, 1);
	VAL_LIMIT(vw, -1, 1);

	//对底盘的控制信息转化为标准单位，平移为(mm/s)旋转为(degree/s)
	chassis.vx = vx * MAX_CHASSIS_VX_SPEED;
	chassis.vy = vy * MAX_CHASSIS_VY_SPEED;
	chassis.vw = vw * MAX_CHASSIS_VR_SPEED;

	chassis_moto_speed_calc(chassis.vx, chassis.vy, chassis.vw,
			chassis_moto_speed_ref);

	moto_ctrl.m1_rpm = chassis_moto_speed_ref[0];
	moto_ctrl.m2_rpm = chassis_moto_speed_ref[1];
	moto_ctrl.m3_rpm = chassis_moto_speed_ref[2];
	moto_ctrl.m4_rpm = chassis_moto_speed_ref[3];

	motor_ctrl_data(1, moto_ctrl);
}

void motor_stop() {
	moto_ctrl.m1_enable = 0;
	moto_ctrl.m2_enable = 0;
	moto_ctrl.m3_enable = 0;
	moto_ctrl.m4_enable = 0;

	motor_ctrl_data(1, moto_ctrl);
}

void chassis_moto_speed_calc(float vx, float vy, float vw, int16_t speed[]) {
	static float rotate_ratio_f = ((WHEELBASE + WHEELTRACK) / 2.0f
			- GIMBAL_OFFSET) / RADIAN_COEF;
	static float rotate_ratio_b = ((WHEELBASE + WHEELTRACK) / 2.0f
			+ GIMBAL_OFFSET) / RADIAN_COEF;
	static float wheel_rpm_ratio = 60.0f / (PERIMETER * CHASSIS_DECELE_RATIO);

	int16_t wheel_rpm[4];
	float max = 0;

	VAL_LIMIT(vx, -MAX_CHASSIS_VX_SPEED, MAX_CHASSIS_VX_SPEED);  //mm/s
	VAL_LIMIT(vy, -MAX_CHASSIS_VY_SPEED, MAX_CHASSIS_VY_SPEED);  //mm/s
	VAL_LIMIT(vw, -MAX_CHASSIS_VR_SPEED, MAX_CHASSIS_VR_SPEED);  //deg/s

	wheel_rpm[0] = (-vx - vy + vw * rotate_ratio_f) * wheel_rpm_ratio;
	wheel_rpm[1] = (-vx + vy + vw * rotate_ratio_f) * wheel_rpm_ratio;
	wheel_rpm[2] = (+vx + vy + vw * rotate_ratio_b) * wheel_rpm_ratio;
	wheel_rpm[3] = (+vx - vy + vw * rotate_ratio_b) * wheel_rpm_ratio;

	//find max item
	for (uint8_t i = 0; i < 4; i++) {
		if (abs(wheel_rpm[i]) > max)
			max = abs(wheel_rpm[i]);
	}
	//equal proportion
	if (max > MAX_WHEEL_RPM) {
		float rate = MAX_WHEEL_RPM / max;
		for (uint8_t i = 0; i < 4; i++)
			wheel_rpm[i] *= rate;
	}
	memcpy(speed, wheel_rpm, 4 * sizeof(int16_t));
}
