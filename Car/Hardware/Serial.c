#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruce;
	USART_InitTypeDef USART_InitStruce;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO_InitTypeDef GPIO_InitStruce;
	GPIO_InitStruce.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruce.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruce.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruce);
	
	GPIO_InitStruce.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruce.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruce.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruce);
	
	//USART_InitTypeDef USART_InitStruce;
	USART_InitStruce.USART_BaudRate = 9600;
	USART_InitStruce.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruce.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruce.USART_Parity = USART_Parity_No;
	USART_InitStruce.USART_StopBits = USART_StopBits_1;
	USART_InitStruce.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruce);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
}

//发送数据
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待标志位
}

//发送数组
void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}

//发送字符串
void Serial_SendString(char *String)
{
	uint8_t i;
	for(i=0;String[i]!='\0';i++)
	{
		Serial_SendByte(String[i]);
	}
}

//次方函数
uint32_t Serial_Pow(uint32_t x,uint32_t y)
{
	uint32_t Result = 1;
	while(y--)
	{
		Result *= x;
	}
	return Result;
}

//发送数字
void Serial_SendNum(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number / Serial_Pow(10,Length-i-1+'0')%10);
	}
}

//printf
int fputc(int ch,FILE*f)
{
	Serial_SendByte(ch);
	return ch;
}

//封装sprintf
void Serial_Printf(char *format,...)
{
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);
}
