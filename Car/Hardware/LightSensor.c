#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruce;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使用GPIO13
	
	
	GPIO_InitStruce.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruce.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruce.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruce);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}
