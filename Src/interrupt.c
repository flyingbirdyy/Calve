//#include "adc.h"
#include "GlobalVal.h"
#include "control.h"
#include "main.h"
#include "user_time.h"
#include "imu.h"

//void DMA_IRQHandler(void)
//{
//    uint32_t IE_Flag, IF_Flag;
//    IE_Flag = FL_DMA_IsEnabledIT_TransferComplete(DMA, FL_DMA_CHANNEL_0);             //??????????????
//    IF_Flag = FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0);
//    if((0x01U == IE_Flag) && (0x01U == IF_Flag))
//    {
//        FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0);                     //???
//		FlagStatusSet(&FlagGlobal, Flag_DMAComplete);
//    }
//}




void LPUARTx_IRQHandler(void)
{
		volatile uint32_t abc = 0;
    //LPUART0接收中断处理	GPS L76
    if((FL_ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART0)) &&
		(FL_SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART0)))      //接收数据中断
    {
			
		FL_LPUART_ClearFlag_RXBuffFull(LPUART0);
		Lp0Rev.Buffer[Lp0Rev.bufcnt] = FL_LPUART_ReadRXBuff(LPUART0);
		FlagStatusSet(&FlagCommStatus, Stat_LP0_Start_RevTimout);
		FL_LPTIM32_Enable(LPTIM32);
		Lp0Rev.bufcnt++;
		Lp0Rev.bufcnt %= 250;
		
		Lp0Rev.timcnt = 0;
    }




    //LPUART2接收中断处理Calve
    if((FL_ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART2))
            && (FL_SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART2)))      //接收数据中断
    {
    	FL_LPUART_ClearFlag_RXBuffFull(LPUART2);
		Lp2Rev.Buffer[Lp2Rev.bufcnt] = FL_LPUART_ReadRXBuff(LPUART2);
		FlagStatusSet(&FlagCommStatus, Stat_LP2_Start_RevTimout);
		FL_LPTIM32_Enable(LPTIM32);
		Lp2Rev.bufcnt++;
		Lp2Rev.bufcnt %= 250;
		Lp2Rev.timcnt = 0;

    }


	FL_LPUART_ClearFlag_FrameError(LPUART0);
	FL_LPUART_ClearFlag_RXBuffFull(LPUART0);
	FL_LPUART_ClearFlag_RXBuffOverflow(LPUART0);
	FL_LPUART_ClearFlag_RXWakeup(LPUART0);


	FL_LPUART_ClearFlag_FrameError(LPUART2);
	FL_LPUART_ClearFlag_RXBuffFull(LPUART2);
	FL_LPUART_ClearFlag_RXBuffOverflow(LPUART2);
	FL_LPUART_ClearFlag_RXWakeup(LPUART2);

}



void RTC_IRQHandler(void)
{
 	static uint8_t	i;
	if(FL_RTCA_IsEnabledIT_Hour(RTCA)  == FL_ENABLE
	&& FL_RTCA_IsActiveFlag_Hour(RTCA) == FL_SET)
	{  
		FL_RTCA_ClearFlag_Hour(RTCA);
		i++;
		if(i == 3)
			{
				FlagStatusSet(&FlagGlobal, Flag_GetG0);
				i = 0;
			}
		

	}

	if(FL_RTCA_IsEnabledIT_Second(RTCA)  == FL_ENABLE
	&& FL_RTCA_IsActiveFlag_Second(RTCA) == FL_SET)
	{  
		FL_RTCA_ClearFlag_Second(RTCA);
		TogLED;
	}

//	if(FL_ENABLE == FL_RTCA_IsEnabledIT_Alarm(RTCA)
//		&& FL_SET == FL_RTCA_IsActiveFlag_Alarm(RTCA))			  
//	{
//		
//		FL_RTCA_ClearFlag_Alarm(RTCA);								
//		WriteAlarm(DevPara.FrozenTime);
//	}

}



void LPTIM_IRQHandler(void)//100ms
{

//	FL_GPIO_ToggleOutputPin(GPIOC, FL_GPIO_PIN_0);
    if(FL_LPTIM32_IsEnabledIT_Update(LPTIM32) == FL_ENABLE
	&& FL_LPTIM32_IsActiveFlag_Update(LPTIM32) == FL_SET)
    {
        FL_LPTIM32_ClearFlag_Update(LPTIM32);
		
		if(FlagStatusIs(FlagGlobal, Flag_MagTim32Start))
			{
				MagTim32Cnt++;
				if(MagTim32Cnt == 255)
					{
						MagTim32Cnt = 0;
					}
				if(!FlagStatusIs(FlagGlobal, Flag_Stat_PowerOn))
					{
						if(MagTim32Cnt>50)
							{
								LEDOn;
							}
					}
					else
					{
							if(MagTim32Cnt>50)
							{
								LEDOff;
							}
					}
			}


		if(FlagStatusIs(FlagCommStatus, Stat_LP0_Start_RevTimout))
			{
				Lp0Rev.timcnt++;
				if(Lp0Rev.timcnt > 2)
					{
						Lp0Rev.timcnt = 0;
						Lp0Rev.bufcnt = 0;
						Lp0Rev.length = Lp0Rev.bufcnt;
						FlagStatusClear(&FlagCommStatus, Stat_LP0_Start_RevTimout);
						FlagStatusSet(&FlagCommStatus, Stat_LP0_Receive_Complete);
					}

			}

		if(FlagStatusIs(FlagCommStatus, Stat_LP2_Start_RevTimout))
			{
				Lp2Rev.timcnt++;
				if(Lp2Rev.timcnt > 3)
					{
						Lp2Rev.timcnt = 0;
						Lp2Rev.length = Lp2Rev.bufcnt;
						Lp2Rev.bufcnt = 0;
//						Lp2Rev.newpkt = false;
//						FL_LPUART_DisableRX(LPUART2);
						FlagStatusClear(&FlagCommStatus, Stat_LP2_Start_RevTimout);
						FlagStatusSet(&FlagCommStatus, Stat_LP2_Receive_Complete);
					}
			}


		
		if(FlagStatusIs(FlagGlobal, Flag_WakeUpCnt))
			{
//				FL_GPIO_ToggleOutputPin(GPIOC, FL_GPIO_PIN_0);
				WakeUpCnt++;
				if(WakeUpCnt > StatTimout)//关闭所有任务进入休眠
					{
						WakeUpCnt = 0;
						FlagStatusClear(&FlagGlobal, Flag_WakeUpCnt);
						FlagStatusClear(&FlagGlobal, Flag_WirlessCom);
						FlagStatusClear(&FlagGlobal, Flag_GetBatVoltage);
						
					}


			}
//		if(FlagStatusIs(FlagGlobal, Flag_DecryptFail))
//			{
//				FL_GPIO_ToggleOutputPin(GPIOC, FL_GPIO_PIN_0);
//			}

    }

}




void GPIO_IRQHandler(void)
{
	lsm6dsm_all_sources_t	status;
	
    if(FL_GPIO_IsActiveFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_1) == 0x01UL)
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_1);
		if(FL_GPIO_GetInputPin(GPIOA, FL_GPIO_PIN_4) == 1)
		{
//			GetAcc((XLRwaTyp *)&XYZXLRaw.XLRwa);
			FlagStatusSet(&FlagGlobal, Flag_MotionDetect | Flag_WakeUpCnt);
			WakeUpCnt = 0;
			FL_LPTIM32_Enable(LPTIM32);
//			lsm6dsm_all_sources_get(SPI2, &status);
//			if(status.wake_up_src.wu_ia == true)
//				{
////启动陀螺仪
////					lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_1k66Hz);
//					FlagStatusSet(&FlagGlobal, Flag_MotionDetect | Flag_WakeUpCnt);
//					WakeUpCnt = 0;
//					FL_LPTIM32_Enable(LPTIM32);
//					LEDOn;
//				}
		

		}
    }

    if(FL_GPIO_IsActiveFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_2) == 0x01UL)
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_2);
		if(FL_GPIO_GetInputPin(GPIOA, FL_GPIO_PIN_8) == 1)
		{
//			GetAcc((XLRwaTyp *)&XYZXLRaw.XLRwa);
//			GetGry((GryRwaTyp *)&XYZGyRaw.GryRwa[XYZGyRaw.nextpoint]);
//			if(!FlagStatusIs(FlagGlobal, Flag_InitDy))
//				{
//					XYZGyRaw.nextpoint++;
//					XYZGyRaw.nextpoint %= DryDatalebgth;
//					FlagStatusSet(&FlagGlobal, Flag_GryReady);
//				}
//			else
//				{
//					DyDiscardCnt++;
//					if(DyDiscardCnt == 3)//135)
//						{
//							DyDiscardCnt = 0;
//							FlagStatusClear(&FlagGlobal, Flag_InitDy);
//						}
//				}

			FlagStatusSet(&FlagGlobal, Flag_GryReady);
//			TogLED;
			
			

		}
    }

    if(FL_GPIO_IsActiveFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_3) == 0x01UL)
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_3);
		if(FL_GPIO_GetInputPin(GPIOA, FL_GPIO_PIN_15) == 0)
		{
			FlagStatusSet(&FlagGlobal, Flag_MagTim32Start);
			FlagStatusSet(&FlagGlobal, Flag_KeyAct);
			FL_LPTIM32_Enable(LPTIM32);
			MagTim32Cnt = 0;
			if(FlagStatusIs(FlagGlobal, Flag_Stat_PowerOn))
				{
					LEDOn;
					MF_LPUART0_Init();
					MF_LPUART0_Interrupt_Init();
				}
		}
		else
		if(FL_GPIO_GetInputPin(GPIOA, FL_GPIO_PIN_15) == 1)
		{
			FlagStatusClear(&FlagGlobal, Flag_MagTim32Start);

			if(MagTim32Cnt <= 50 )
				{
					if(FlagStatusIs(FlagGlobal, Flag_Stat_PowerOn))
						{
							FlagStatusSet(&FlagGlobal, Flag_WakeUpCnt);

						}
					LEDOff;
					FlagStatusClear(&FlagGlobal, Flag_KeyAct);
				}

			else
				if(MagTim32Cnt > 50 )
					{
						if(!FlagStatusIs(FlagGlobal, Flag_Stat_PowerOn))
							{
								FlagStatusSet(&FlagGlobal, Flag_Stat_PowerOn);
								FlagStatusSet(&FlagGlobal, Flag_PowerOnInit);
							}
						else
							if(FlagStatusIs(FlagGlobal, Flag_Stat_PowerOn))
								{
									FlagStatusClear(&FlagGlobal, Flag_Stat_PowerOn);
									FlagStatusSet(&FlagGlobal, Flag_PowerDownDeInit);
								}
					LEDOff;
					}
				MagTim32Cnt = 0;
//				FlagStatusClear(&FlagGlobal, Flag_KeyAct);
		}
    }





	if(FL_GPIO_IsActiveFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_5) == 0x01UL)
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_5);
		if(FL_GPIO_GetInputPin(GPIOB, FL_GPIO_PIN_6) == 0)
		{
			FlagStatusSet(&FlagGlobal, Flag_WakeUpCnt);
			FL_LPTIM32_Enable(LPTIM32);
		}
    }
}


