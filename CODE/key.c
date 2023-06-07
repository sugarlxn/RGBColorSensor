#include "stm32f10x.h"
#include "GPIOLIKE51.h"
#include "key.h"


#define key1press 1



//设置为上拉输入 低电平有效
void key_init(void){
	
	
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); 						 

//key -> PB4		 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

u8 key_scan(void){
	
	uint8_t statu=0;
	statu = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
	if(statu==0){
		return key1press;
	}
	return 0;
}

