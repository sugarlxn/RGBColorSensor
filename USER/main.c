#include "stm32f10x.h"
#include "GPIOLIKE51.h"
#include "led.h"
#include "key.h"
#include "blueteeth.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "oled.h"
#include "stdio.h"
#include "TCS34725.h"

extern COLOR_RGBC rgb;
extern COLOR_HSL hsl;

int fputc(int ch,FILE *p) 
 
{
 
 Usart_SendByte(USART1,(u8)ch);
 
 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
 
 return ch;
 
}

int main(void)
{

	DelayInit();
	led_init();
	key_init();
	blueteeth_init();
	OLED_Init();
	TCS34725_Init();

	OLED_CLS();
	while (1)
	{

		TCS34725_GetRawData(&rgb);
		RGBtoHSL(&rgb, &hsl);
		OLED_ShowStr(0, 1, (u8*)"RGB.R", 1);OLED_Showint(30, 1, rgb.r, 3);
		OLED_ShowStr(0, 2, (u8*)"RGB.G", 1);OLED_Showint(30, 2, rgb.g, 3);
		OLED_ShowStr(0, 3, (u8*)"RGB.B", 1);OLED_Showint(30, 3, rgb.b, 3);
		OLED_ShowStr(0, 4, (u8*)"HSL.H", 1);OLED_Showint(30, 4, hsl.h, 3);
		OLED_ShowStr(0, 5, (u8*)"HSL.S", 1);OLED_Showint(30, 5, hsl.s, 3);
		OLED_ShowStr(0, 6, (u8*)"HSL.L", 1);OLED_Showint(30, 6, hsl.l, 3);
		OLED_ShowStr(0, 7, (u8*)"RGB.C", 1);OLED_Showint(30, 7, rgb.c, 3);
		DelayMs(100);
		
	}
}
