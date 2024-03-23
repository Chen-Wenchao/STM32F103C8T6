#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB ,ENABLE );
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)//读取PB１端口的值
	{
		Delay_ms (20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) ==0);
		Delay_ms (20);
		KeyNum = 1;
	}
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) ==0)//读取PB2端口的值
	{
		Delay_ms (20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
		Delay_ms (20);
		KeyNum = 2;
	}
	return KeyNum;
}
