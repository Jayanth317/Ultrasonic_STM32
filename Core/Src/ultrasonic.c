/*
 * ultrasonic.c
 *
 *  Created on: Aug 2, 2022
 *      Author: Lenovo
 *      usable for DYP-A02YYU model only,since it is UART auto output
 */
#include"ultrasonic.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;
uint8_t g_dataBuf_u8[100];
uint8_t g_rxBufByte_u8 = 0;
uint32_t g_rxBufCounter_u32 = 0;
uint8_t g_byte_counter_u8=0;
uint8_t g_data_h;
uint8_t g_data_l;
uint8_t g_dataReady_u8 = 0;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3)
	{
		g_dataBuf_u8[g_rxBufCounter_u32] = g_rxBufByte_u8;
		g_rxBufCounter_u32++;
		if(g_rxBufCounter_u32 > sizeof(g_dataBuf_u8))
		{
			g_rxBufCounter_u32 = 0;
		}

		uint8_t gethex = g_rxBufByte_u8;

		if(gethex == 0xff)
	    {
	    	g_byte_counter_u8 = 1;

	    }
	    else if(g_byte_counter_u8 == 1)
	    {
	    	g_byte_counter_u8 = 2;
	    	g_data_h = g_rxBufByte_u8;
	    }
	    else if(g_byte_counter_u8 == 2)
	    {
	    	g_data_l = g_rxBufByte_u8;
	    	g_byte_counter_u8 = 3;
	    	g_dataReady_u8 = 1;
	    }
	    HAL_UART_Receive_DMA(&huart3, &g_rxBufByte_u8, sizeof(g_rxBufByte_u8));
	}
}


uint16_t Get_distance()
{
	//while(g_dataReady_u8!=1);
	//g_dataReady_u8 = 0;
    return  (g_data_h*256+g_data_l);
}


void ultrasonic_init()
{
	HAL_UART_Receive_DMA(&huart3, &g_rxBufByte_u8, sizeof(g_rxBufByte_u8));
}




