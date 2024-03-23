#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Delay.h"

void Car_Init()
{
	Motor_Init();
}

void Go_Ahead()//前进
{
	Motor_SetLiftspeed(70);
	Motor_SetRightSpeed(70);
}

void Go_Back()//向后
{
	Motor_SetLiftspeed(-70);
	Motor_SetRightSpeed(-70);
}

void Turn_Left()//左转
{
	Motor_SetLiftspeed(0);
	Motor_SetRightSpeed(70);
}

void Turn_Right()//右转
{
	Motor_SetLiftspeed(70);
	Motor_SetRightSpeed(0);
}

void Self_Left()//左自转
{
	Motor_SetLiftspeed(-70);
	Motor_SetRightSpeed(70);
}

void Self_Right()//右自转
{
	Motor_SetLiftspeed(70);
	Motor_SetRightSpeed(-70);
}

void Car_Stop()
{
	Motor_SetLiftspeed(0);
	Motor_SetRightSpeed(0);
}
