#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	
	//需要额外初始化方向控制的两个角
	GPIO_InitTypeDef GPIO_InitStruce;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使用GPIO12
	
	
	GPIO_InitStruce.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruce.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruce.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruce);	
	
	PWM_Init();
}

void Motor_SetLiftspeed(int8_t Speed)//设置左边的速度
{
	if(Speed >= 0)//大于0轮子向前转
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(Speed);
	}
	else if(Speed == 0)//全部设置高电平制动
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(-Speed);
	}
}
 
void Motor_SetRightSpeed(int8_t Speed)//设置右边
{
	if(Speed > 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		PWM_SetCompare2(Speed);
	}
	else if(Speed == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		PWM_SetCompare2(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		PWM_SetCompare2(-Speed);
	}
	
}
