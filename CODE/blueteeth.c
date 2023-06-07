#include "blueteeth.h"
#include "stm32f10x.h"
#include "GPIOLIKE51.h"
#include "misc.h"


//蓝牙初始化 PB6:Tx ; PB7:Rx;
void blueteeth_init(void){
	
	GPIO_InitTypeDef PB6;
	GPIO_InitTypeDef PB7;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE); 
	
	//输出Tx
	PB6.GPIO_Pin = GPIO_Pin_6;
	PB6.GPIO_Speed = GPIO_Speed_50MHz;
	PB6.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOB, &PB6);
	
	//输入Rx
	PB7.GPIO_Pin = GPIO_Pin_7;
	PB7.GPIO_Speed = GPIO_Speed_50MHz;
	PB7.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOB, &PB7);
	
	
	
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;  //设置uart1为中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
	
	
	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
}

void Usart_SendByte(USART_TypeDef* USARTx, uint16_t ch){

	USART_SendData(USARTx,ch);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)== RESET);
}


void Usart_SendString(USART_TypeDef* USARTx, unsigned char *str){
	unsigned int k=0;
	do{
		Usart_SendByte(USARTx,*(str+k));
		k++;
		
	}while(*(str+k)!='\0');
	
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)== RESET);
}


