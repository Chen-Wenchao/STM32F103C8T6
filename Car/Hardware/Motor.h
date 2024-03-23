#ifndef __MOTOR_H
#define __MOTOR_H
#include "stdint.h"


void Motor_Init(void);

void Motor_SetLiftspeed(int8_t Speed);//设置左边的速度

void Motor_SetRightSpeed(int8_t Speed);//设置右边

#endif
