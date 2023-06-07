#include "stm32f10x.h"
#include "GPIOLIKE51.h"
#include "led.h"
#include "key.h"
#include "blueteeth.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "oled.h"





int main(void)
{
	
	DelayInit();
	led_init();
	key_init();
	blueteeth_init();
	OLED_Init();
	
	OLED_CLS();
	OLED_ShowStr(0,1,"ok!",1);
	OLED_ShowStr(0,2,"data1:",1);
   while (1)
	{

		DelayMs(100);
		PCout(13)=1;
		DelayMs(200);
		PCout(13)=0;
		
		
		
   }
	
}




