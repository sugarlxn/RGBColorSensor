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
		OLED_ShowStr(0, 1, "RGB.R", 1);OLED_Showint(50, 1, rgb.r, 3);
		OLED_ShowStr(0, 2, "RGB.G", 1);OLED_Showint(50, 2, rgb.g, 3);
		OLED_ShowStr(0, 3, "RGB.B", 1);OLED_Showint(50, 3, rgb.b, 3);
		OLED_ShowStr(0, 4, "HSL.H", 1);OLED_Showint(50, 4, hsl.h, 3);
		OLED_ShowStr(0, 5, "HSL.S", 1);OLED_Showint(50, 5, hsl.s, 3);
		OLED_ShowStr(0, 6, "HSL.L", 1);OLED_Showint(50, 6, hsl.l, 3);
	}
}
