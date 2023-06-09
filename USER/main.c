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

unsigned char page = 1;
const unsigned char BMPm[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE4,0x38,0x00,
0x03,0x03,0x03,0x03,0x02,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,
0x70,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x03,0x03,
0x03,0x03,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x00,0x0F,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xC0,0x40,0x18,0x18,0x18,0x18,0x08,0x18,0x18,0x18,0x18,0x08,0x00,
0x00,0x03,0x87,0x4C,0x18,0x18,0x18,0x18,0x08,0x08,0x18,0x18,0x18,0x18,0x08,0x18,
0x18,0x18,0x18,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xEF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0xC0,0x40,0x18,0x18,0x18,
0x18,0x08,0x18,0x18,0x18,0x18,0x08,0x08,0x18,0x18,0x18,0x18,0x00,0x80,0x00,0x00,
0x00,0x00,0x00,0xC0,0xE0,0x00,0x08,0x18,0x18,0x18,0x98,0x00,0x40,0xC0,0x00,0x00,
0x00,0x18,0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0xE0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x1C,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x78,0x1C,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,
0x1C,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x07,0x3C,0x70,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x78,0x1C,0x03,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x0F,0x3C,
0x60,0x00,0x00,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
0x40,0x40,0x40,0x40,0x40,0x00,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x7F,0x00,0x00,
0x00,0xC0,0x70,0x1C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0x18,0x0E,0x02,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0xFC,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0xFC,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,
0x8E,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x86,0xFC,0x08,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x01,0x31,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x80,0xC3,0x30,0x10,0x00,
0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x02,0x02,0x02,0x02,0x00,0x01,
0x01,0x00,0x00,0x00,0x00,0xC0,0xF0,0x30,0x00,0x00,0x00,0xFB,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFB,0x00,0x00,0x20,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,
0x01,0x01,0x02,0x02,0x02,0x02,0x02,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0xC0,0xF0,
0x10,0x00,0x00,0xFB,0xFB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0A,0xFB,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0x0C,0x00,0x10,0x10,0x10,0x10,0x00,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0C,0x07,0x01,0x00,0x00,0x00,
0x00,0x03,0x06,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x0C,0x0E,0x01,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x10,0x10,
0x10,0x10,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x03,0x0E,0x08,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0C,0x06,0x01,0x00,
0x00,0x00,0x00,0x1F,0x1F,0x00,0x10,0x10,0x10,0x10,0x18,0x00,0x00,0x00,0x1F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

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

	OLED_ShowStr(0, 0, (u8*)"TCS34725 init...", 1);
	OLED_DrawBMP(0,1,128,7,(unsigned char *)BMPm);
	DelayS(1);
	OLED_CLS();

	while (1)
	{
		TCS34725_GetRawData(&rgb);
//		if(key_scan()){page ++;OLED_CLS();}
	  
		OLED_ShowStr(0, 1, (u8*)"R", 1);OLED_Showint(10, 1, rgb.r, 3);OLED_showfloat(60, 1, ((double)rgb.r)*255/rgb.c, 3);
		OLED_ShowStr(0, 2, (u8*)"G", 1);OLED_Showint(10, 2, rgb.g, 3);OLED_showfloat(60, 2, ((double)rgb.g)*255/rgb.c, 3);
		OLED_ShowStr(0, 3, (u8*)"B", 1);OLED_Showint(10, 3, rgb.b, 3);OLED_showfloat(60, 3, ((double)rgb.b)*255/rgb.c, 3);
		OLED_ShowStr(0, 4, (u8*)"C", 1);OLED_Showint(10, 4, rgb.c, 3);	
		
		printf("%d,%d,%d,%d,\n\r",rgb.r,rgb.g,rgb.b,rgb.c);
		DelayMs(100);
	
		
	}
}
