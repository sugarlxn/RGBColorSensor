#include "stm32f10x.h"
#include "GPIOLIKE51.h"
#include "stm32f10x_usart.h"
#include "misc.h"

void blueteeth_init(void);
void Usart_SendByte(USART_TypeDef* USARTx, uint16_t ch);
void Usart_SendString(USART_TypeDef* USARTx, unsigned char *str);



