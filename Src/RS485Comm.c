#include "main.h"
#include "user_uart.h"
#include "control.h"
#include "user_time.h"
#include "RS485Comm.h"
#include "gd25q_driver.h"
#include "lora.h"







//void SendGetCalveDataCmd(void)
//{
//	uint8_t	i;
//	uint16_t crc;
//	s_btf	floatdata;
//	uint8_t	CMD_GetValveDate[12]={0xFE, 0x09, 0x01, 0x21, 0x01, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0xEF};
//	FL_RTCA_InitTypeDef tim;
//	if(FlagStatusIs(FlagGlobal, Flag_GetCalve))
//	{
//		memset(CalveRevBuf, 0, sizeof(CalveRevBuf));
//		RTCA_GetRTCA(&tim);
//		CMD_GetValveDate[3] = (uint8_t)tim.year;
//		CMD_GetValveDate[4] = (uint8_t)tim.month;
//		CMD_GetValveDate[5] = (uint8_t)tim.day;
//		CMD_GetValveDate[6] = (uint8_t)tim.hour;
//		CMD_GetValveDate[7] = (uint8_t)tim.minute;
//		CMD_GetValveDate[8] = (uint8_t)tim.second;
//		crc = CRC_Modbus(CMD_GetValveDate, 9);
//		CMD_GetValveDate[9] = (uint8_t)(crc>>8);
//		CMD_GetValveDate[10] = (uint8_t)crc;
//		FlagStatusClear(&FlagCalveStatus, Stat_RS485_Receive_Complete);
//		TxEN_RS485();
//		HAL_UART_Transmit(LPUART2, CMD_GetValveDate, sizeof(CMD_GetValveDate), 100000);
//		RxEN_RS485();
//		WaitUartRx(3000, &FlagCalveStatus, Stat_RS485_Receive_Complete);
//		crc = CalveRevBuf[9];
//		crc = (crc<<8) + CalveRevBuf[10];
//		if(CalveRevBuf[0] == 0xFE && crc == CRC_Modbus(CalveRevBuf, 9))
//			{
//				UpdateData.ValveSatus = CalveRevBuf[3];
//				for(i=0;i<4;i++)
//					{
//						floatdata.byte[i] = CalveRevBuf[4+i];
//					}
//				UpdateData.ValveBatVal = floatdata.float32;
//				UpdateData.ValveBatLvl = CalveRevBuf[8];
//			}
//		else
//			{
//				


//			}
//			
//		
//		FlagStatusClear(&FlagGlobal, Flag_GetCalve);
//	}


//	



//	
//	
//}




void SendData(uint8_t *data, uint8_t length)
{
	TxEN_RS485();
	HAL_UART_Transmit(LPUART2, data, length, 500);
	RxEN_RS485();

}



void UIDProcess()
{
	uint8_t uidmcu[12];
	uint8_t enuidmcu[12];
	
	UID_ReadMCU(uidmcu);
	UID_En_Decrypt(enuidmcu, uidmcu, (uint8_t *)&DevPara.Key);
	GD25_Wakeup();
	FL_DelayMs(100);
	UID_WriteFlash(enuidmcu);
	GD25_Sleep();
	FlagStatusClear(&FlagGlobal, Flag_DecryptFail);
	FL_RTCA_ClearFlag_Second(RTCA);
  	FL_RTCA_DisableIT_Second(RTCA);  
	FL_LPUART_DeInit(LPUART0);
	LEDOff;
}



void ProcessPkt(uint8_t *data)
{
	uint16_t lenght, crc;

	lenght = *(data + 1);

	crc = *(data+lenght+2);
	crc = (crc<<8) | *(data+lenght+3);



	if(crc == CRC_Modbus(data+1, *(data+1)+1))
		{
			switch(*(data+2))
				{
				case	0x01:
//						CalCalveTimeComplete();
						break;
				case	0x02:
//						CalveDataProcess(data);
						break;
				case	0x05:
//						ReadCalvBatt();
						break;
				default:
						break;
					
				}

		}

}




void ProcessPktUID(UartBufferTyp *data)
{
	uint16_t lenght, crc;



	if(FlagStatusIs(FlagCommStatus, Stat_LP0_Receive_Complete))
		{
			FlagStatusClear(&FlagCommStatus, Stat_LP0_Receive_Complete);		
			lenght = data->Buffer[1];
			
			crc = data->Buffer[lenght];
			crc = (crc<<8) | data->Buffer[lenght+1];
			if(crc == CRC_Modbus((uint8_t *)&data->Buffer[1], data->Buffer[1]-1))
				{
					switch(data->Buffer[2])
						{
						case	0x11:
								SetSerialNo((uint8_t *)&data->Buffer);
								break;
						case	0x68:
								if(FlagStatusIs(FlagGlobal, Flag_DecryptFail))
									{
										UIDProcess();
									}
								break;
						case	0x1D:
								ConfigWirlessModule(data);
						default:
								break;
							
						}
				}
		}
}


