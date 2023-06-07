#include "ANO_DT.h"
#include "blueteeth.h"
#include "stm32f10x_usart.h"

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)      ) )     /*!< uint32_t 数据拆分 byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )     /*!< uint32_t 数据拆分 byte1  */
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )     /*!< uint32_t 数据拆分 byte2  */
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )     /*!< uint32_t 数据拆分 byte3  */

/*!
  * @brief    Send_Data函数是协议中所有发送数据功能使用到的发送函数
  *
  * @param    dataToSend   :   要发送的数据首地址
  * @param    length       :   要发送的数据长度
  *
  * @return   无
  *
  * @note     移植时，用户应根据自身应用的情况，根据使用的通信方式，实现此函数
  *
  * @see      内部调用
  *
  * @date     2019/5/28 星期二
  */
void ANO_DT_Send_Data(USART_TypeDef* USARTx, uint16_t *dataToSend, unsigned short length) {

    /**使用串口正常发送数据，大概需要1.5ms*/
    //UART4_PutBuff(dataToSend, length);     //可以修改不同的串口发送数据
    //uart_putbuff(USARTN, dataToSend, length);
	int i=0;
	while(length){
		Usart_SendByte(USARTx, dataToSend[i]);
		i++;
		length--;
	}
}

/**  发送数据缓存 */
uint16_t data_to_send[50];

/*!
  * @brief    向上位机发送发送8个int16_t数据
  *
  * @param    data1 - data8  ： 发送给上位机显示波形
  *
  * @return   无
  *
  * @note     无
  *
  * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
  *
  * @date     2019/5/28 星期二
  */
void ANO_DT_send_int16(USART_TypeDef* USARTx, short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8) {
    unsigned char _cnt = 0;
    unsigned char sum = 0, i = 0;

    data_to_send[_cnt++] = 0xAA;      //匿名协议帧头  0xAAAA
    data_to_send[_cnt++] = 0xAA;
    data_to_send[_cnt++] = 0xF1;      //使用用户协议帧0xF1
    data_to_send[_cnt++] = 0;        //8个int16_t 长度 16个字节

    data_to_send[_cnt++] = BYTE1(data1);
    data_to_send[_cnt++] = BYTE0(data1);

    data_to_send[_cnt++] = BYTE1(data2);
    data_to_send[_cnt++] = BYTE0(data2);

    data_to_send[_cnt++] = BYTE1(data3);
    data_to_send[_cnt++] = BYTE0(data3);

    data_to_send[_cnt++] = BYTE1(data4);
    data_to_send[_cnt++] = BYTE0(data4);

    data_to_send[_cnt++] = BYTE1(data5);
    data_to_send[_cnt++] = BYTE0(data5);

    data_to_send[_cnt++] = BYTE1(data6);
    data_to_send[_cnt++] = BYTE0(data6);

    data_to_send[_cnt++] = BYTE1(data7);
    data_to_send[_cnt++] = BYTE0(data7);

    data_to_send[_cnt++] = BYTE1(data8);
    data_to_send[_cnt++] = BYTE0(data8);
	
	data_to_send[3]=_cnt-4;
	
    sum = 0;
    for (i = 0; i < _cnt; i++)
        sum += data_to_send[i];
    data_to_send[_cnt++] = sum;

    ANO_DT_Send_Data(USARTx, data_to_send, _cnt);
}


