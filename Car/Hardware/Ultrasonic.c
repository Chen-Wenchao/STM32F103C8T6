#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint16_t Cnt;
uint16_t OverCnt;
void Ultrasonic_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM4);
	//TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 60000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	
}

float Test_Distance()
{
	float distance = 0;
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//先吧B12设置成高电平
	Delay_us(20);//在B12设置成20微妙的高电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);//然后再设置成低电平
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) == RESET){};//等待B13返回的超声波
	TIM_Cmd(TIM4,ENABLE);//接收到高电平就打开定时器
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) == SET){};
	TIM_Cmd(TIM4,DISABLE);//等变为低电平之后就关闭定时器
	Cnt = TIM_GetCounter(TIM4);
	distance = (Cnt*1.0/10*0.34)/2;
	TIM4->CNT=0;//计数器清零方便下次测量
	Delay_ms(100);//延迟一百毫秒
	return distance;
}
