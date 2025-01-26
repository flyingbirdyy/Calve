
#ifndef USER_UART_H
#define USER_UART_H


#include "main.h"

//extern uint8_t     		RxBuffer[1000];

uint8_t HAL_UART_Transmit(LPUART_Type *huart,  uint8_t *pData,  uint16_t Size, uint32_t timeout);

void SendTestData(uint8_t data);

void WaitUartRx(uint16_t timeout, uint16_t *flagstatus, uint16_t flag);
void TxEN_RS485(void);
void RxEN_RS485(void);
void Sleep_RS485(void);
uint8_t HAL_UART_TransmitStr(LPUART_Type *huart,  uint8_t *pData, uint32_t timeout);




#endif
