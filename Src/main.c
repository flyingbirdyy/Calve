/**
  ****************************************************************************************************
  * @file    main.c
  * @author  FMSH Application Team
  * @brief   Header file of FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */

#include "main.h"
#include "fm33_assert.h"
#include "globaldef.h"
#include "globaltyp.h"
#include "globalval.h"
#include "LSM6DSM_REG.H"
#include "IMU.h"
#include "GetSensors.h"
#include <math.h>
#include "control.h"
#include "RS485Comm.h"
#include "imu.h"
#include "lora.h"
#include "gd25q_driver.h"
#include "flashdata.h"



/**    
* Chip Series: FM33LG0xx;
* FL Version: v2.3;
* Project Name: Calve;
* Project Version: v2.3.0.0;
* Project ID: 1778417974562566146;
* Create Date: 2024-04-11;
*/

  uint8_t test[10];
lsm6dsm_all_sources_t all_source;

int main(void)
{

	uint8_t uidbuf[12];
	uint8_t decryptuid[12];
	uint8_t encryptuid[12];
	uint8_t i;
	uint8_t buf[6] = {0xC0, 0x00, 0x00, 0x1F, 0x50, 0x47};

    /* Initialize FL Driver Library */
    FL_Init();

    /* Configure the system clock */
    MF_Clock_Init();
    

    /* Initialize all configured peripherals */
//    MF_Config_Init();
	MF_PowerUp_Config_Init();
	ModeSet(SleepMode);
	LEDOn;
	FL_DelayMs(2000);
	
//	MF_Config_Init();//debug 20240917
//FL_LPUART_EnableTX(LPUART2);
//FL_LPUART_EnableRX(LPUART2);
//FL_LPUART_ClearFlag_FrameError(LPUART2);
//FL_LPUART_ClearFlag_RXBuffFull(LPUART2);
//FL_LPUART_ClearFlag_RXBuffOverflow(LPUART2);
//
////LoraReset();
//
//
//
////FL_DelayMs(2000);
////TransmitData(buf, 6);
////FL_DelayMs(2000);
////
////LoraParaGet();
////FL_DelayMs(2000);
//ModeSet(NormalMode);
//
//
//while(1)
//{
//	TogLED;
//	FL_DelayMs(2000);
//	TransmitData("Hello", sizeof("Hello"));
////SysSleepTest();
//}





	
//debug

	
//DevInit();
//debug lysq 0515
//FlagStatusSet(&FlagGlobal, Flag_MotionDetect);
//FlagStatusSet(&FlagGlobal, Flag_GetG0);
//
//while(1)
//{
//	if(FlagStatusIs(FlagGlobal, Flag_GetG0))
//		{
////						GetGsense0();	
//			GetDryrate0();
//
//		}
//	else
//		{
//			GetGsense();
//		}


//}

//debug



	FL_LPUART_EnableTX(LPUART0);
	FL_LPUART_EnableRX(LPUART0);
	FL_LPUART_ClearFlag_FrameError(LPUART0);
	FL_LPUART_ClearFlag_RXBuffFull(LPUART0);
	FL_LPUART_ClearFlag_RXBuffOverflow(LPUART0);


	FL_LPUART_EnableTX(LPUART2);
	FL_LPUART_EnableRX(LPUART2);
	FL_LPUART_ClearFlag_FrameError(LPUART2);
	FL_LPUART_ClearFlag_RXBuffFull(LPUART2);
	FL_LPUART_ClearFlag_RXBuffOverflow(LPUART2);


	
	FL_SPI_Enable(SPI0);

	GD25_Wakeup();
	FL_DelayMs(100);
	ReadDevPara(&DevPara, sizeof(DevPara));
//	RestoreDevPara();
	if(DevPara.CfgHead != 0x88)
	{
		RestoreDevPara();
		
		GD25QXX_Write((uint8_t *)&DevPara, Flash_DfgData_StartAddr, sizeof(DevPara));
	}
	
	UID_ReadMCU(uidbuf);
	UID_ReadFlash(decryptuid);
	UID_En_Decrypt(encryptuid, decryptuid, (uint8_t *)&DevPara.Key);
	GD25_Sleep();
	for(i=0;i<12;i++)
		{
			if(uidbuf[i] != encryptuid[i])
				{
					FlagStatusSet(&FlagGlobal, Flag_DecryptFail); 
//					FL_RTCA_ClearFlag_Second(RTCA);
//    				FL_RTCA_EnableIT_Second(RTCA);  
					break;
				}
		}


//	FlagStatusClear(&FlagGlobal, Flag_DecryptFail);  //debug lysq
//	DevInit();
//FlagStatusSet(&FlagGlobal, Flag_WirlessCom);
//UpdateData.addr = 0x1234;
//UpdateData.ValveBatVal = 0x35;
//UpdateData.valvedegree = 150;

//while(1)
//{

//	Delayms(100);
//	TogLED;
////	if(FlagStatusIs(FlagCommStatus, Stat_LP2_Receive_Complete))
////		{
////			Update_Lora();
////		}
//}
//LEDOn;
//						DevInit();
//						LEDOn;
//						FlagStatusClear(&FlagGlobal, Flag_PowerOnInit);
//						FlagStatusSet(&FlagGlobal, Flag_GetG0);
//						FlagStatusSet(&FlagGlobal, Flag_GetBatVoltage);


//	FlagStatusSet(&FlagGlobal, Flag_DecryptFail); //debug
//
//	FL_RTCA_ClearFlag_Second(RTCA);
//	FL_RTCA_EnableIT_Second(RTCA);  
	LEDOff;
    while(1)
    {     
		if(!FlagStatusIs(FlagGlobal, Flag_DecryptFail))
			{

				

				if(FlagStatusIs(FlagGlobal, Flag_PowerOnInit))
					{
						MF_Config_Init();
						DevInit();
						FlagStatusClear(&FlagGlobal, Flag_PowerOnInit);
						FlagStatusClear(&FlagGlobal, Flag_KeyAct);
					}
				if(FlagStatusIs(FlagGlobal, Flag_PowerDownDeInit))
					{
						FlagStatusClear(&FlagGlobal, Flag_PowerDownDeInit);
						FlagStatusClear(&FlagGlobal, Flag_KeyAct);
						DevDeInit();
					}


				if(FlagStatusIs(FlagGlobal, Flag_GetG0))
					{
			//						GetGsense0();	
						GetDryrate0();
			
					}
				else
					{
						GetGsense();
					}

				GetVoltage();
				Update_Lora();
				LoraRxPrce(&Lp2Rev);
//				ConfigDev();
//					SysSleepTest();
				StoreData();
				ProcessPktUID(&Lp0Rev);
				SysSleep();

			}
		else
			{
				ProcessPktUID(&Lp0Rev);
				FL_DelayMs(1000);
				TogLED;
			}

    }

}


