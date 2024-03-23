#include "stm32f10x.h"   // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Car.h"
#include "Serial.h"
#include "Ultrasonic.h"
#include "Servo.h"

uint16_t Data1;
uint16_t a;
uint16_t b;
uint16_t c;

int main(void)
{
	Serial_Init();
	Car_Init();
	Ultrasonic_Init();
	Servo_Init();	
	Servo_SetAngle(90);
	Go_Ahead();
	while(1)
	{
		
		a = Test_Distance();
		Serial_SendNum(a,3);
		if(a<20)
		{
			Car_Stop();
			Servo_SetAngle(0);
			Delay_ms(1000);
			b = Test_Distance();
			Serial_SendNum(b,3);
			if(b>20)
			{
				Servo_SetAngle(90);
				Delay_ms(1000);
				Self_Right();
				Delay_ms(1000);
				Go_Ahead();
			}
			else
			{
				Servo_SetAngle(180);
				Delay_ms(1000);
				c = Test_Distance();
				Serial_SendNum(c,3);
				if(c>15)
				{
					Servo_SetAngle(90);
					Delay_ms(1000);
					Self_Right();
					Delay_ms(1000);
					//Go_Ahead();
				}
				else
				{
					Servo_SetAngle(90);
					Self_Right();
					Delay_ms(2000);
					Go_Ahead();
				}
			}
		}
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		Data1 = USART_ReceiveData(USART1);
		if(Data1 == 0x47)
		{
			Go_Ahead();
		}
		if(Data1 == 0x49)
		{
			Car_Stop();
		}
		if(Data1 == 0x48)
		{
			Self_Right();
		}
		if(Data1 == 0x4A)
		{
			Self_Left();
		}
		if(Data1 == 0x4B)
		{
			Go_Back();
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
