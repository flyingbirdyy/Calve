
#include "lora.h"
#include "main.h"
#include "user_uart.h"
#include "control.h"
#include <string.h>




void ModeSet(LoraModeTyp loramode)
{
	switch(loramode)
		{
			case	NormalMode:
					FL_GPIO_ResetOutputPin(GPIOB, FL_GPIO_PIN_2);
					FL_GPIO_ResetOutputPin(GPIOB, FL_GPIO_PIN_3);
					break;
			case	WakeUpMode:
					FL_GPIO_SetOutputPin(GPIOB, FL_GPIO_PIN_2);
					FL_GPIO_ResetOutputPin(GPIOB, FL_GPIO_PIN_3);
					break;
			case	LowPowerMode:
					FL_GPIO_ResetOutputPin(GPIOB, FL_GPIO_PIN_2);
					FL_GPIO_SetOutputPin(GPIOB, FL_GPIO_PIN_3);
					break;
			case	SleepMode:
					FL_GPIO_SetOutputPin(GPIOB, FL_GPIO_PIN_2);
					FL_GPIO_SetOutputPin(GPIOB, FL_GPIO_PIN_3);
					break;
			default	:
					break;
		}



}


void LoraParaGet(void)
{
	uint8_t cmd[3] = {0xC1, 0xC1, 0xC1};
	HAL_UART_Transmit(LPUART2, cmd, 3, 1000);
	FL_DelayMsStart(2000);
	while(!FL_DelayEnd() && !FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete));
	FlagStatusClear(&FlagCommStatus, Stat_LP2_Receive_Complete);
}


void LoraReset(void)
{
	uint8_t cmd[3] = {0xC4, 0xC4, 0xC4};
	HAL_UART_Transmit(LPUART2, cmd, 3, 1000);
	FL_DelayMsStart(500);
	while(!FL_DelayEnd() && !FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete));
	FlagStatusClear(&FlagCommStatus, Stat_LP2_Receive_Complete);
}




void SetAddr(uint16_t addr)
{
	LoraParaTyp parabuf;

	ModeSet(SleepMode);
	FL_DelayMs(50);
	memset(Lp2Buffer, 0, sizeof(Lp2Buffer));
	LoraParaGet();
//	FL_LPUART_EnableRX(LPUART2);
//	FL_DelayMsStart(5000);
//	do
//		{
//			if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
//				{
//					break;
//				}
//		}
//	while (!FL_DelayEnd());

//	WaitUartRx(10000, &FlagCommStatus, Stat_LP2_Receive_Complete);

	
	while(!FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete));
	if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete) && Lp2Rev.length == 6 && Lp2Buffer[0] == 0xC0)
		{
			FL_GPIO_ToggleOutputPin(GPIOC, FL_GPIO_PIN_0);
			memcpy((uint8_t *)&parabuf, &Lp2Buffer, Lp2Rev.length);
			parabuf.AddH = addr>>8;
			parabuf.AddL = (uint8_t)addr;
			FL_DelayMs(1000);
			HAL_UART_Transmit(LPUART2, (uint8_t *)&parabuf, 6, 1000);
			
		}
	FlagStatusClear(&FlagCommStatus, Stat_LP2_Receive_Complete);

}




uint8_t SetUartBaud(LoraUartBaudTyp baud)
{
	LoraParaTyp parabuf;

	ModeSet(SleepMode);
	
	LoraParaGet();

	FL_DelayMsStart(1000);
	while(!FL_DelayEnd() && !FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete));
	if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
		{
			memcpy((uint8_t *)&parabuf, (uint8_t *)&Lp2Rev.Buffer, Lp2Rev.length);
			parabuf.Sped_UartBaud = baud;
			HAL_UART_Transmit(LPUART2, (uint8_t *)&parabuf, 6, 500);
			return 1;
		}
	return 0;
}


uint8_t SetAirBaud(LoraAirBaudTyp baud)
{
	LoraParaTyp parabuf;

	ModeSet(SleepMode);
	LoraParaGet();

	FL_DelayMsStart(1000);
	while(!FL_DelayEnd() && !FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete));
	if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
		{
			memcpy((uint8_t *)&parabuf, (uint8_t *)&Lp2Rev.Buffer, Lp2Rev.length);
			parabuf.Sped_AirBaud = baud;
			HAL_UART_Transmit(LPUART2, (uint8_t *)&parabuf, 6, 500);
			return 1;
		}
	return 0;

}


uint8_t SetAirChan(uint8_t chan)  //0x50H      433mHz, 0x00~0xFF, 425~450.5MHz
{
	LoraParaTyp parabuf;

	ModeSet(SleepMode);

	LoraParaGet();

	FL_DelayMsStart(1000);
	while(!FL_DelayEnd() && !FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete));
	if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
		{
			memcpy((uint8_t *)&parabuf, (uint8_t *)&Lp2Rev.Buffer, Lp2Rev.length);
			parabuf.Chan = chan;
			HAL_UART_Transmit(LPUART2, (uint8_t *)&parabuf, 6, 500);
			return 1;
		}
	return 0;

}


void	TransmitData(uint8_t *data, uint8_t length)
{
	HAL_UART_Transmit(LPUART2, data, length, 1000);
}


void Update_Lora(void)
{
	uint8_t txbuf[50];
	uint8_t i=0;
	uint8_t length;
	uint16_t crc;
	uint8_t j;
	int32_t tempd;
//	static uint8_t cnt;
	
//	if(FlagStatusIs(FlagGlobal, Flag_WirlessCom) || FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
	if(FlagStatusIs(FlagGlobal, Flag_WirlessCom))
		{
			FlagStatusClear(&FlagGlobal, Flag_WirlessCom);
			
			txbuf[i] = 0x00;
			i++;
			txbuf[i] = 0x04;
			i++;
			txbuf[i] = DevPara.RF_Chan;
			i++;
			
			txbuf[i] = 0xFE;
			i+=2;
			txbuf[i] = (uint8_t) (UpdateData.addr >> 8);
			i++;
			txbuf[i] = (uint8_t) UpdateData.addr;
			i++;
			txbuf[i] = 0x02;
			i++;
			txbuf[i] = 0xF1;
			i++;
			txbuf[i] = UpdateData.ValveBatVal;
			i++;
			txbuf[i] = 0xF3;
			i++;
			tempd = UpdateData.valvedegree;
			txbuf[i] = (uint8_t) (tempd >> 24);
			i++;
			tempd = UpdateData.valvedegree;
			txbuf[i] = (uint8_t) (tempd  >> 16);
			i++;
			tempd = UpdateData.valvedegree;
			txbuf[i] = (uint8_t) (tempd  >> 8);
			i++;
			txbuf[i] = (uint8_t) UpdateData.valvedegree;
			length = i-3;
			i++;
			txbuf[4] = i-3;
			crc = CRC_Modbus(&txbuf[4],length);
			txbuf[i] = (uint8_t) (crc >> 8);
			i++;
			txbuf[i] = (uint8_t) (crc);
			
			ModeSet(WakeUpMode);

//			ModeSet(NormalMode);

			
			for(j=0;j<2;j++)
				{
//					ModeSet(WakeUpMode);
//					ModeSet(NormalMode);//debug 20240917

					FL_DelayMsStart(10);
					for(;;)
						{
							if(FL_DelayEnd() || FL_GPIO_GetInputPin(GPIOB, FL_GPIO_PIN_6))
								{
									break;
								}
						}
//					while(!FL_DelayEnd() && !FL_GPIO_GetInputPin(GPIOB, FL_GPIO_PIN_6) );
		//			ModeSet(NormalMode);//debug lysq 20240701
//					FL_DelayMs(200);
					TransmitData(txbuf, i+1);
//					memset(&Lp2Rev.Buffer, 0, 250);
					FL_DelayMsStart(1000);
					for(;;)
						{
							if(FL_DelayEnd() || FL_GPIO_GetInputPin(GPIOB, FL_GPIO_PIN_6))
								{
									break;
								}
						}
//					ModeSet(NormalMode);
//					FL_DelayMs(500);
					FL_DelayMsStart(1000);
//					cnt++;//debug 20241101
					for(;;)
						{
							if(FL_DelayEnd() || FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
								{
									break;
								}
						}

//					while(!FL_DelayEnd() && !FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete));
					if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
						{	
							FlagStatusClear(&FlagCommStatus, Stat_LP2_Receive_Complete);
							if(strstr((char *)&Lp2Rev.Buffer, "OK") != NULL)
								{
									break;
								}
						}
				}

//			ModeSet(LowPowerMode);
			
			ModeSet(SleepMode);
//			cnt = 0;
			
		}

}



void LoraRxPrce(UartBufferTyp *rxdata)
{
	uint8_t length;
	uint16_t crc;
	uint16_t addr;
	
	if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
		{
			FlagStatusClear(&FlagCommStatus, Stat_LP2_Receive_Complete);
			if(rxdata->Buffer[0] == 0xFE)
				{
					length = rxdata->Buffer[1];
					addr = rxdata->Buffer[2];
					addr = (addr<<8) |  rxdata->Buffer[3];
					
					crc = rxdata->Buffer[length];
					crc = (crc<<8) | rxdata->Buffer[length+1];

					if(crc == CRC_Modbus(&rxdata->Buffer[1],length - 2))
						{
							OpenTask();
						}
				}

		}



}

void ConfigWirlessModule(UartBufferTyp *data)
{
	uint8_t buf[6];
	uint8_t	tbuf[3] = {0xC1, 0xC1, 0xC1};
	signed char ret;
	
	memcpy(buf, (uint8_t *)&data->Buffer[3], 6);
	ModeSet(SleepMode);
	FL_DelayMs(10);
	TransmitData(buf, 6);
	FL_DelayMs(1000);

//	while(!FL_DelayEnd() || !FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete));
			TransmitData(tbuf, 3);
			FL_DelayMsStart(1000);
			for(;;)
				{
					if(FL_DelayEnd() || FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
						{
							break;
						}
				}
			if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
				{	
					FlagStatusClear(&FlagCommStatus, Stat_LP2_Receive_Complete);
					ret = memcmp(buf, (uint8_t *)&Lp2Rev.Buffer, 6);
					if(ret == 0)
						{
//							FL_RTCA_DisableIT_Second(RTCA); 
							LEDOn;
							FL_DelayMs(5000);
//							FL_RTCA_EnableIT_Second(RTCA); 

						}
					
			}

}



void GetRFChan(uint8_t *data)
{
	uint8_t	tbuf[3] = {0xC1, 0xC1, 0xC1};
	
	HAL_UART_Transmit(LPUART2, tbuf, 3, 1000);
	FL_DelayMsStart(1000);
	for(;;)
		{
			if(FL_DelayEnd() || FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
				{
					break;
				}
		}
	if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
		{
			*data = Lp2Rev.Buffer[4];
		}

}




