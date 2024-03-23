#ifndef __SERIAL_H
#define __SERIAL_H
#include "stdint.h"
#include <stdio.h>

void Serial_Init(void);

//发送数据
void Serial_SendByte(uint8_t Byte);

//发送数组
void Serial_SendArray(uint8_t *Array,uint16_t Length);

//发送字符串
void Serial_SendString(char *String);
	
//发送数字
void Serial_SendNum(uint32_t Number,uint8_t Length);

//打印字符串
void Serial_Printf(char *format,...);
#endif
