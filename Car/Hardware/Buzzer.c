#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruce;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使用GPIO12
	
	
	GPIO_InitStruce.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruce.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruce.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruce);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}


void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_Turn(void)//调用这个函数LED取反
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12) == 0)//读取当前端口输出状态
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);//如果是0就置1
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);//如果是1就置0
	}
}
