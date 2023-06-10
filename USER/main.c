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
extern COLOR_HSV hsv;

unsigned char page = 1;

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

		if(TCS34725_GetRawData(&rgb)){
			RGBtoHSL(&rgb, &hsl);
			RGBtoHSV(&rgb, &hsv);
		}
		if(key_scan()){page ++;OLED_CLS();}
		switch(page%2){
			
			case 0:
		
		OLED_ShowStr(0, 1, (u8*)"HSV.H", 1);OLED_Showint(30, 1, hsv.h, 3);
		OLED_ShowStr(0, 2, (u8*)"HSV.S", 1);OLED_Showint(30, 2, hsv.s, 3);
		OLED_ShowStr(0, 3, (u8*)"HSV.V", 1);OLED_Showint(30, 3, hsv.v, 3);
		OLED_ShowStr(0, 4, (u8*)"HSL.H", 1);OLED_Showint(30, 4, hsl.h, 3);
		OLED_ShowStr(0, 5, (u8*)"HSL.S", 1);OLED_Showint(30, 5, hsl.s, 3);
		OLED_ShowStr(0, 6, (u8*)"HSL.L", 1);OLED_Showint(30, 6, hsl.l, 3);
		OLED_ShowStr(0, 7, (u8*)"RGB.C", 1);OLED_Showint(30, 7, rgb.c, 3);
			break;
			case 1:
	  
		OLED_ShowStr(0, 1, (u8*)"R", 1);OLED_Showint(10, 1, rgb.r, 3);OLED_showfloat(60, 1, ((double)rgb.r)*255/rgb.c, 3);
		OLED_ShowStr(0, 2, (u8*)"G", 1);OLED_Showint(10, 2, rgb.g, 3);OLED_showfloat(60, 2, ((double)rgb.g)*255/rgb.c, 3);
		OLED_ShowStr(0, 3, (u8*)"B", 1);OLED_Showint(10, 3, rgb.b, 3);OLED_showfloat(60, 3, ((double)rgb.b)*255/rgb.c, 3);
		OLED_ShowStr(0, 4, (u8*)"C", 1);OLED_Showint(10, 4, rgb.c, 3);
//		OLED_ShowStr(0, 5, (u8*)"HSL.S", 1);OLED_Showint(30, 5, hsl.s, 3);
//		OLED_ShowStr(0, 6, (u8*)"HSL.L", 1);OLED_Showint(30, 6, hsl.l, 3);
//		OLED_ShowStr(0, 7, (u8*)"RGB.C", 1);OLED_Showint(30, 7, rgb.c, 3);		
				break;
			default:
				break;
			
		}
		printf("%d,%d,%d,%d,\n\r",rgb.r,rgb.g,rgb.b,rgb.c);
		DelayMs(100);
		
	}
}
