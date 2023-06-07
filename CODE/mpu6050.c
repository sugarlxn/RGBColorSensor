#include "stm32f10x.h"
#include "mpu6050.h"
#include "stm32f10x_i2c.h"


//ʹ��Ӳ��IIC
//PB9:SDA;PB8:SCL;AD0 ��GND���ӻ���ַΪ0x68,��VCC���ӻ���ַΪ0x69
void mpu_init(){
	
	//gpio_init
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//I2C���뿪©���
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	I2C_DeInit(I2C1);//ʹ��I2C1
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;//IICʱ��ռ�ձ�
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//������I2C��ַ,���д��
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;//400K

	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
	
	//mpu_init
	
	
	
}


