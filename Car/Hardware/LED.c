#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruce;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使用GPIO12
	
	
	GPIO_InitStruce.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruce.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruce.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruce);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}


void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void LED1_Turn(void)//调用这个函数LED取反
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 0)//读取当前端口输出状态
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);//如果是0就置1
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//如果是1就置0
	}
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED2_Turn(void)//调用这个函数LED取反
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == 0)//读取当前端口输出状态
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);//如果是0就置1
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);//如果是1就置0
	}
}
