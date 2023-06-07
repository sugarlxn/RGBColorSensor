#include "timer.h"
#include "stm32f10x_tim.h"
#include "misc.h"

int time_s=0;
int time_ms=0;

//打开定时器3 timer3

void timer_init(void){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler=71;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_Period=1000;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);// 清除计数器中断标志位
	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);//中断使能
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void){
	
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
		time_ms++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
	
	if(time_ms==1000){
		time_ms=0;
		time_s++;
	}
	
}


