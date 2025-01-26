#include "main.h"
#include <stdint.h>
#include "user_uart.h"
#include "FM33LG0XX_FL.h"
#include "globalval.h"
#include "control.h"
#include <stdio.h>
//uint8_t     RxBuffer[1000];
//uint8_t			RS485RxBuf[100] = {0x41,0x03,0x24,0x3E,0x9C,0x45,0xEB,0x42,0x57,0x59,0x6A,0x00,0x00,0x0D,0xB7,0x00,0x00,0x0D,0xB7,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x8D,0x00,0x0B,0x00,0x01,0x00,0x02,0x00,0x09,0x00,0x09,0x00,0x58,0x6A,0xB8};
//uint8_t			RS485RxBuf[100] = {0x01, 0x03, 0x10, 0xE1, 0x85, 0x45, 0xA0, 0xE1, 0x8C, 0x45, 0xA0, 0x37, 0xF3, 0x3B, 0x5D, 0x00, 0x00, 0x00, 0x00, 0x86, 0xD1};



void TxEN_RS485(void)
{
	FL_GPIO_SetOutputPin(GPIOB, FL_GPIO_PIN_3);
	FL_GPIO_SetOutputPin(GPIOB, FL_GPIO_PIN_6);

}

void RxEN_RS485(void)
{
	FL_GPIO_ResetOutputPin(GPIOB, FL_GPIO_PIN_3);
	FL_GPIO_ResetOutputPin(GPIOB, FL_GPIO_PIN_6);

}


void Sleep_RS485(void)
{
	FL_GPIO_SetOutputPin(GPIOB, FL_GPIO_PIN_3);
	FL_GPIO_ResetOutputPin(GPIOB, FL_GPIO_PIN_6);
}



// 1 timeout == 0.1s, 超时时间, timeoutflag: 串口接收结束标志�?
//void WaitUartRx(uint16_t timeout, bool *timeoutflag, LPTIM32_Type *LPTIM32x)
//{
//	Flag_Global.UartTimeout_EN = true;
//
//	Flag_Global.Tim32outCnt = timeout;
//	
//	*timeoutflag = false;
//	while(!Flag_Global.Tim32Out)
//	{
//		if(*timeoutflag == true)
//		{
////			*timeoutflag = false;
//			break;
//
//		}
//	}
//	Flag_Global.UartTimeout_EN = false;
//	Flag_Global.Tim32Out = false;
//	*timeoutflag = false;
//}



//timeout ��λms
void WaitUartRx(uint16_t timeout, uint16_t *flagstatus, uint16_t flag)
{

	FL_DelayMsStart(timeout);
	while(!FL_DelayEnd())
		{
			if(FlagStatusIs(*flagstatus, flag))
				{
//					FlagStatusClear(flagstatus, flag);
					break;
				}
		}
}




//HardErrTypeDef HAL_UART_Transmit(LPUART_Type *huart,  uint8_t *pData,  uint16_t Size,   uint32_t timeout, LPTIM32_Type *LPTIM32x)
//{
//
//	uint32_t timeout = 0;
//	Flag_Global.UartTimeout_EN = true;
//	Flag_Global.Tim32outCnt = timeout;
//	while(!Flag_Global.Tim32Out)
//	{
//		while(Size>0)
//		{
//			
////			FL_DelayMs(2);
//			FL_LPUART_WriteTXBuff(huart, *pData);
//			pData++;
//			Size--;
//			do
//			{
//				timeout++;
//			}
//			while(!FL_LPUART_IsActiveFlag_TXBuffEmpty(huart) && timeout < TIMEOUT_VAL);
//		}
//		if(Size == 0)
//		{
//			break;
//		}
//	}
//	Flag_Global.UartTimeout_EN = false;
//	Flag_Global.Tim32Out = false;
//	if(Size == 0)
//	{
//		return HAL_OK;
//	}
//	else
//	{
//		return HAL_TIMEOUT;
//	}
//	
//}


uint8_t HAL_UART_Transmit(LPUART_Type *huart,  uint8_t *pData,  uint16_t Size, uint32_t timeout)
{

	while(Size>0)
	{
		FL_LPUART_WriteTXBuff(huart, *pData);
		pData++;
		Size--;
		FL_DelayMsStart(timeout);
		while(!FL_LPUART_IsActiveFlag_TXBuffEmpty(huart) && !FL_DelayEnd());
	}

	if(Size == 0)
	{
		return HAL_OK;
	}
	else
	{
		return HAL_TIMEOUT;
	}
	
}


uint8_t HAL_UART_TransmitStr(LPUART_Type *huart,  uint8_t *pData, uint32_t timeout)
{

	while(*pData != 0)
	{
		FL_LPUART_WriteTXBuff(huart, *pData);
		pData++;
		FL_DelayMsStart(timeout);
		while(!FL_LPUART_IsActiveFlag_TXBuffEmpty(huart) && !FL_DelayEnd());
	}

    return HAL_OK;
	
}





void SendTestData(uint8_t data)
{
	TxEN_RS485();
	HAL_UART_Transmit(LPUART2, &data, 1, 10);


}


int _write(int file, uint8_t *ptr, int len)
{
	(void)file;
	HAL_UART_Transmit(LPUART2, ptr, len, 1000);

//	RF_Transmit(ptr,len,RouteMsg);  //debug lysq
	return len;
}


