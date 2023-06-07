#include "ANO_DT.h"
#include "blueteeth.h"
#include "stm32f10x_usart.h"

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)      ) )     /*!< uint32_t ���ݲ�� byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )     /*!< uint32_t ���ݲ�� byte1  */
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )     /*!< uint32_t ���ݲ�� byte2  */
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )     /*!< uint32_t ���ݲ�� byte3  */

/*!
  * @brief    Send_Data������Э�������з������ݹ���ʹ�õ��ķ��ͺ���
  *
  * @param    dataToSend   :   Ҫ���͵������׵�ַ
  * @param    length       :   Ҫ���͵����ݳ���
  *
  * @return   ��
  *
  * @note     ��ֲʱ���û�Ӧ��������Ӧ�õ����������ʹ�õ�ͨ�ŷ�ʽ��ʵ�ִ˺���
  *
  * @see      �ڲ�����
  *
  * @date     2019/5/28 ���ڶ�
  */
void ANO_DT_Send_Data(USART_TypeDef* USARTx, uint16_t *dataToSend, unsigned short length) {

    /**ʹ�ô��������������ݣ������Ҫ1.5ms*/
    //UART4_PutBuff(dataToSend, length);     //�����޸Ĳ�ͬ�Ĵ��ڷ�������
    //uart_putbuff(USARTN, dataToSend, length);
	int i=0;
	while(length){
		Usart_SendByte(USARTx, dataToSend[i]);
		i++;
		length--;
	}
}

/**  �������ݻ��� */
uint16_t data_to_send[50];

/*!
  * @brief    ����λ�����ͷ���8��int16_t����
  *
  * @param    data1 - data8  �� ���͸���λ����ʾ����
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
  *
  * @date     2019/5/28 ���ڶ�
  */
void ANO_DT_send_int16(USART_TypeDef* USARTx, short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8) {
    unsigned char _cnt = 0;
    unsigned char sum = 0, i = 0;

    data_to_send[_cnt++] = 0xAA;      //����Э��֡ͷ  0xAAAA
    data_to_send[_cnt++] = 0xAA;
    data_to_send[_cnt++] = 0xF1;      //ʹ���û�Э��֡0xF1
    data_to_send[_cnt++] = 0;        //8��int16_t ���� 16���ֽ�

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


