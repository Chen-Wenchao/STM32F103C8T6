#ifndef __SERVO_H
#define __SERVO_H
#include "stdint.h"

void PWM_Init(void);

void PWM_SetCompare4(uint16_t Compare);

void Servo_Init(void);

void Servo_SetAngle(float Angle);


#endif
