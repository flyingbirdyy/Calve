
#include <math.h>
#include <time.h>
#include "GetSensors.h"
#include "GlobalVal.h"
#include "string.h"
#include "gd25q_driver.h"
#include "user_time.h"
#include "RS485Comm.h"
#include "control.h"
#include "user_uart.h"
#include "IMU.h"
#include "globaldef.h"
#include "globaltyp.h"
#include "lora.h"
#include "kalman.h"
#include "flashdata.h"

/*----------------------------------------------------------------------
函 数 名:   FlagStatusIs
功能描述:   检查flagstatus状态
建立时间：  
更改时间：  NONE
输入参数：FlagGlobal
输出参数:   NONE
返 回 值：  TRUE : FALSE
----------------------------------------------------------------------*/
uint8_t FlagStatusIs(uint16_t status, uint16_t flagstatus)
{
    return ((status & flagstatus) ? TRUE : FALSE);
}



/*----------------------------------------------------------------------
函 数 名:  FlagStatusSet
功能描述:      设置flagstatus状态
建立时间：  
更改时间：  NONE
输入参数：  mode
输出参数: FlagGlobal
返 回 值：  NONE
----------------------------------------------------------------------*/
void FlagStatusSet(uint16_t *status, uint16_t flagstatus)
{
    *status |= flagstatus;
}


/*----------------------------------------------------------------------
函 数 名:  FlagStatusSet
功能描述:      设置flagstatus状态
建立时间：  
更改时间：  NONE
输入参数：  mode
输出参数: FlagGlobal
返 回 值：  NONE
----------------------------------------------------------------------*/
void FlagStatusClear(uint16_t *status, uint16_t flagstatus)
{
    *status &= ~flagstatus;
}



//float Retain_Two_Decimals(float num)
//{
//	int data;
//	float abc;
//
//	data = num * 100;
//
//	abc = (float)data;
//	
//	abc /=100;
//	return abc;
//
//}
//
//
//float Retain_One_Decimals(float num)
//{
//	int data;
//
//	data = num * 10;
//
//	return (float)data/10.0;
//
//}


//debug lysq 0515
void SysSleep(void)
{
	

//	FlagStatusClear(&FlagGlobal, Flag_1stFlashProcess);

	if((!FlagStatusIs(FlagGlobal, Flag_MotionDetect) &&	
		!FlagStatusIs(FlagGlobal, Flag_WirlessCom) && 
		!FlagStatusIs(FlagGlobal, Flag_GetBatVoltage) && 
		!FlagStatusIs(FlagGlobal, Flag_GetG0)) &&
		!FlagStatusIs(FlagGlobal, Flag_MagTim32Start) &&
		!FlagStatusIs(FlagGlobal, Flag_WakeUpCnt) &&
		!FlagStatusIs(FlagGlobal, Flag_KeyAct) &&
		!FlagStatusIs(FlagGlobal, Flag_PowerOnInit) &&
		!FlagStatusIs(FlagGlobal, Flag_PowerDownDeInit) 
		)
		{

			DisablePeripheral();
			LEDOff;
//			FL_IWDT_EnableFreezeWhileSleep(IWDT);
			FL_RMU_PDR_Enable(RMU);      
		    FL_RMU_BOR_Disable(RMU);           
		    FL_CDIF_DisableCPUToVAO(CDIF);   
		    FL_PMU_SetLowPowerMode(PMU, FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP);

			__WFI(); 
			FL_RMU_PDR_Disable(RMU);   
			FL_RMU_BOR_Enable(RMU); 
			EnPeripheral();
//			FL_IWDT_DisableFreezeWhileSleep(IWDT);
			
		}

}


void SysSleepTest(void)
{

//	if((!FlagStatusIs(FlagGlobal, Flag_GetGPS) &&
//		!FlagStatusIs(FlagGlobal, Flag_UpdateData) &&
//		!FlagStatusIs(FlagGlobal, Flag_GetSensors) &&
//		!FlagStatusIs(FlagGlobal, Flag_GetGSense) &&
//		!FlagStatusIs(FlagGlobal, Flag_StoreFlashData) &&
////		!FlagStatusIs(FlagGlobal, Flag_WakeUp) &&
//		!FlagStatusIs(FlagGlobal, Flag_StoreFlashCfg) &&
//		!FlagStatusIs(FlagGlobal, Flag_PowerOnStart) && 
//		!FlagStatusIs(FlagGlobal, Flag_GetCalve)) || 
//		(FlagStatusIs(FlagGlobal, Flag_WakeUpCnt))
//		)
		{


			DisablePeripheral();


//			FL_IWDT_EnableFreezeWhileSleep(IWDT);
				
			FL_LPTIM32_Disable(LPTIM32);
			FL_RMU_PDR_Enable(RMU);      
		    FL_RMU_BOR_Disable(RMU); 
			FL_VREF_Disable(VREF);          
		    FL_CDIF_DisableCPUToVAO(CDIF);   
		    FL_PMU_SetLowPowerMode(PMU, FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP);

			__WFI(); 

			EnPeripheral();
//			MF_LPUART0_Init();
//			MF_LPUART1_Init();
//			MF_LPUART2_Init();
//			MF_ADC_Common_Init();
//			FL_DelayMs(10);
//			FL_IWDT_DisableFreezeWhileSleep(IWDT);
//			FL_IWDT_ReloadCounter(IWDT);


			
			
		}

}








uint16_t CRC_Modbus (uint8_t *ptr, uint16_t len)
{
	uint16_t i, j;
	volatile uint16_t crc = 0xffff, temp;

	for (i = 0; i < len; i++)
	{
		crc ^= *ptr;
		for (j = 0; j < 8; j++)
		{
			temp = crc & 1;
			crc >>= 1;
			if (temp)
			{
				crc ^= 0xA001;
			}
		}
		ptr++;
	}
	//crc = ((crc&0x00FF)<<8)|((crc&0xFF00)>>8);
	return crc;
}




//length需要转换的8bit字节数量
bool HEXtoASSCII(uint8_t *pHex, uint8_t *pAssc, uint16_t	length)
{
	uint8_t	nibble[2];
	
	uint8_t	buffer[2048];
	
	uint16_t	i=0;
	
	uint8_t		j=0;
	
	for(i=0;i<length;i++)
	{
		nibble[0] = (pHex[i] >> 4) & 0x0F;
		nibble[1] = pHex[i] & 0x0F;
		for(j=0;j<2;j++)
		{
			if(nibble[j] < 10) 
			{
				nibble[j] = nibble[j] + 0x30;
			}
			else
				if(nibble[j] < 16)
				{
					nibble[j] = nibble[j] - 10 + 'A';
				}
				else
				{
					return false;
				}
			
		}
		memcpy(buffer+i*2, nibble, 2);
	}
	buffer[2*length] = 0x00;
	memcpy(pAssc, buffer, 2*length);
	pAssc[2*length] = 0x00;
	return true;
}




uint8_t HexToBcd(uint8_t hexData)
{
	uint8_t bcdData;
	bcdData = ((hexData / 10) << 4) + (hexData % 10);
	return bcdData;
}

int BCDtoDecimal(char bcd) 
{
    return (bcd & 0xF); // 取最低4位并返回对应的十进制值
}

//转换成10进制，如0x82->82
uint8_t BcdToHex(uint8_t bcdData)
{	
	uint8_t hexData;	
	hexData = (bcdData >> 4) * 10 + (bcdData & 0x0F);
	return hexData;
}



bool ASCIItoHEXByte(uint8_t *pAssc, uint8_t *pHex, uint8_t length)
{

//	uint8_t nibble = 0;
	uint8_t i = 0;
	uint8_t j = 0;
//	uint8_t	k = 0;
	uint8_t	data[4];

	for(i=0;i<length;i++)
	{
		if (*pAssc <= 'F' && *pAssc >= 'A')
		{
			data[i] = *pAssc - 'A' + 10;
		}
		else 
			if(*pAssc <= 'f' && *pAssc >= 'a')
			{
				data[i] = *pAssc - 'a' + 10;
			}
			
		else 
			if(*pAssc >= '0' && *pAssc <= '9')
			{
				data[i] = *pAssc - '0';
			}
			
		else
			return false;
		pAssc++;
	}

	i = length;
	*pHex = 0;
	for(j=0;j<length;j++)
	{
		*pHex += (data[j] * pow(10, i-1));
		i--;
	}
			
	return true;
}


void ASCIItoBCD(char *asc, uint8_t *bcd, uint8_t len)
{
	uint8_t hexdata;
	ASCIItoHEXByte((uint8_t *)asc, &hexdata, 2);
	*bcd = HexToBcd(hexdata);
}


uint8_t BCD_ADD(uint8_t bcd1, uint8_t bcd2) //BCD + BCD = BCD
{
    uint8_t sum, carry;
 
    // 提取低4位
    sum = (bcd1 & 0x0F) + (bcd2 & 0x0F);
    carry = (bcd1 >> 4) + (bcd2 >> 4);
 
    // 如果低位和大于9，则进位需要加6
    if (sum > 9) 
	{
        sum -= 10;
        carry++;
    }
 
    // 将结果合并
    return (carry << 4) | sum;
}




//void ASCIItoBCD(uint8_t *bcd, char *asc, uint8_t len)
//{
//    uint8_t c = 0;
//    uint8_t index = 0;
//    uint8_t i = 0;
//
//    len >>= 1;
//
//    for (i = 0; i < len; i++) {
//        //first BCD  
//        if (*asc >= 'A' && *asc <= 'F') 
//		{
//            index = *asc - 'A';
//            c = ascii2bcd2[index] << 4;
//        }
//        else if (*asc >= '0' && *asc <= '9') {
//            index = *asc - '0';
//            c = ascii2bcd1[index] << 4;
//        }
//        asc++;
//
//        //second BCD  
//        if (*asc >= 'A' && *asc <= 'F') {
//            index = *asc - 'A';
//            c |= ascii2bcd2[index];
//        }
//        else if (*asc >= '0' && *asc <= '9') {
//            index = *asc - '0';
//            c |= ascii2bcd1[index];
//        }
//        asc++;
//
//        *bcd++ = c;
//    }
//
//    return 0;
//}
//UINT32 BCD2ASC(unsigned char *asc, const unsigned char *bcd, UINT32 len)
//{
//    unsigned char c = 0;
//    unsigned char i;
//
//
//    for (i = 0; i < len; i++) {
//        //first BCD  
//        c = *bcd >> 4;
//        *asc++ = bcd2ascii[c];
//
//
//        //second  
//        c = *bcd & 0x0f;
//        *asc++ = bcd2ascii[c];
//        bcd++;
//    }
//
//
//    return 0;
//}




uint16_t FormatData(char *dstdata, char *sourcedatabuf)
{
//	uint16_t			i = 0;
//	uint16_t			j = 0;
//	uint16_t 			datalength = 0;
//
//	uint8_t 			tempbuf[4] = {0};//, tempbuf1[9] = {0};
//
//	uint16_t 			cnt = 0;
//
//	s_btf				float32;
//	s_bti16 			int16;
//	uint8_t 			assicbuf[2];

	uint16_t			length = 0;

	uint8_t	nibble[2];
	
	uint16_t	i=0;
	
	uint8_t		j=0;
	
	while(*(sourcedatabuf+i) != 0)
	{
		nibble[0] = (sourcedatabuf[i] >> 4) & 0x0F;
		nibble[1] = sourcedatabuf[i] & 0x0F;
		for(j=0;j<2;j++)
		{
			length++;
			if(nibble[j] < 10) 
			{
				nibble[j] = nibble[j] + 0x30;
			}
			else
				if(nibble[j] < 16)
				{
					nibble[j] = nibble[j] - 10 + 'A';
				}
				else
				{
					return false;
				}
			
		}
		memcpy(dstdata+i*2, nibble, 2);
		i++;
	}
//	buffer[2*length] = 0x00;
//	memcpy(pAssc, buffer, 2*length);
	return length;


}



void RestoreDevPara(void)
{
	DevPara.CfgHead = 0x88;
	DevPara.RF_Chan = 0x50;
	DevPara.addr = 0x0002;
	strcpy((char *)&DevPara.Key, "830116");
}




void ReadDevPara(CfgParaTyp *cfg, uint8_t length)
{

	FL_DelayMs(100);
	GD25Q16_Read((uint8_t *)cfg, Flash_DfgData_StartAddr, length);
	StoreData();

}




void OpenTask(void)
{

	FlagStatusSet(&FlagGlobal, Flag_GetG0);
	FlagStatusSet(&FlagGlobal, Flag_GetBatVoltage);
	FlagStatusSet(&FlagGlobal, Flag_WakeUpCnt);

	FL_LPTIM32_Enable(LPTIM32);
	ModeSet(SleepMode);
//	ModeSet(NormalMode);//debug 20240917

}


void CloseTask(void)
{
	FlagStatusClear(&FlagGlobal, Flag_GetG0);
	FlagStatusClear(&FlagGlobal, Flag_GetBatVoltage);
	FlagStatusClear(&FlagGlobal, Flag_WakeUpCnt);
	FlagStatusClear(&FlagGlobal, Flag_MotionDetect);
	FlagStatusClear(&FlagGlobal, Flag_WirlessCom);
	FL_LPTIM32_Disable(LPTIM32);
	FL_RTCA_Disable(RTCA);
	ModeSet(SleepMode);
}



void EnPeripheral(void)
{

	FL_LPUART_EnableTX(LPUART0);
	FL_LPUART_EnableRX(LPUART0);
	FL_LPUART_ClearFlag_FrameError(LPUART0);
	FL_LPUART_ClearFlag_RXBuffFull(LPUART0);
	FL_LPUART_ClearFlag_RXBuffOverflow(LPUART0);
	FL_SPI_Enable(SPI0);


	FL_LPUART_EnableTX(LPUART2);
	FL_LPUART_EnableRX(LPUART2);
	FL_LPUART_ClearFlag_FrameError(LPUART2);
	FL_LPUART_ClearFlag_RXBuffFull(LPUART2);
	FL_LPUART_ClearFlag_RXBuffOverflow(LPUART2);
	FL_SPI_Enable(SPI2);
	
//	FL_RTCA_Enable(RTCA);
//	FL_VREF_Disable(VREF);

	FL_LPTIM32_Enable(LPTIM32);
	

	ModeSet(SleepMode);
	FL_DelayMs(100);
	GetRFChan((uint8_t *)&DevPara.RF_Chan);
	FL_DelayMs(100);
	ModeSet(SleepMode);

	

}


void DeInitPeripheral(void)
{

	FL_LPUART_DeInit(LPUART0);
	FL_LPUART_DeInit(LPUART2);

	FL_SPI_DeInit(SPI0);
	FL_SPI_DeInit(SPI2);

	FL_ADC_DeInit(ADC);

	FL_RTCA_DeInit(RTCA);
}


void DisablePeripheral(void)
{
	
	FL_LPUART_DisableTX(LPUART0);
	FL_LPUART_DisableRX(LPUART0);
	FL_LPUART_DeInit(LPUART0);

//	FL_LPUART_DisableTX(LPUART2);
//	FL_LPUART_DisableRX(LPUART2);

	FL_SPI_Disable(SPI0);
	FL_SPI_Disable(SPI2);
	FL_ADC_Disable( ADC);

//	FL_RTCA_Disable(RTCA);
	FL_LPTIM32_Disable(LPTIM32);
	ModeSet(SleepMode);
}



void DevInit(void)
{
//	uint8_t uidbuf[12];
//	uint8_t decryptuid[12];
//	uint8_t encryptuid[12];
	uint8_t i;
	uint8_t devid;
	EnPeripheral();
        
	for(i=0;i<2;i++)
		{
			lsm6dsm_device_id_get(&devid);
			if(devid == 0x6A)
				{
					LEDOff;
				}
	//			LEDOn;
				FL_DelayMs(50);
		}
	lsm6dsmHiInit();
	OpenTask();
	KalmanInit();

}


void DevDeInit(void)
{
	lsm6dsmDeInit();
	CloseTask();
	DeInitPeripheral();
	
}


void ConfigDev(void)
{
	
	if(FlagStatusIs(FlagCommStatus, Stat_LP0_Receive_Complete))
		{
			ProcessPkt((uint8_t *)&Lp2Rev.Buffer);
			FlagStatusClear(&FlagCommStatus, Stat_RS485_Receive_Complete);
		}
}









void SetSerialNo(uint8_t *data)
{
	strncpy((char *)&DevPara.SerialNo, (char *)(data+3), 12);
	FlagStatusSet(&FlagGlobal, Flag_StoreFlashData);
}



//void ReadIMEI(void)
//{
//	uint16_t crc;
//	uint8_t	txbuf[20] = {0xCF, 0x17, 0x12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//	strncpy((char *)((&txbuf)+3), (char *)&DevPara.IMEI, 15);

//	crc = CRC_Modbus(txbuf, 17);
//	txbuf[17] = (uint8_t)(crc>>8);
//	txbuf[18] = (uint8_t)(crc);
//	SendData(txbuf, sizeof(txbuf));
//}




//void SetWaterPressureTH(uint8_t *data)
//{
//	uint8_t i;
//	s_btf datatemp;
//		
//	data += 3;
//	for(i=0;i<4;i++)
//		{
//			datatemp.byte[i] = *(data++);
//		}
//	DevPara.AlarmThreshold.WaterPresureThreshold_Lo = datatemp.float32;
//	for(i=0;i<4;i++)
//	{
//		datatemp.byte[i] = *(data++);
//	}
//	DevPara.AlarmThreshold.WaterPresureThreshold_Hi = datatemp.float32;
//	FlagStatusSet(&FlagGlobal, Flag_StoreFlashCfg);
//}


//void SetTiltAngleTH(uint8_t *data)
//{
//	DevPara.AlarmThreshold.TiltAngleThreshold = *(data+3);
//	FlagStatusSet(&FlagGlobal, Flag_StoreFlashCfg);
//}


//void SetTempTH(uint8_t *data)
//{
//	DevPara.AlarmThreshold.WaterTempThreshold = *(data+3);
//	FlagStatusSet(&FlagGlobal, Flag_StoreFlashCfg);
//}

//void SetFrozenTime(uint8_t *data)
//{
//	DevPara.FrozenTime = *(data+3);
//	FlagStatusSet(&FlagGlobal, Flag_StoreFlashCfg);
//}


//void SetupdateTime(uint8_t *data)
//{
//	DevPara.UpdateTime = *(data+3);
//	FlagStatusSet(&FlagGlobal, Flag_StoreFlashCfg);
//}


//void ReadGateBatt(void)
//{
//	uint16_t crc;
//	uint8_t	txbuf[9] = {0xCF, 0x7, 0x18, 0, 0, 0, 0, 0, 0};
//	uint16_t timeout = 0;
//	uint8_t statuserr = 0;
//	uint8_t i;
//	s_btf datatemp;
//	
////	StartADC(ADCBuffer, ADCLength);

//	GetRef(ADCBuffer);
//	GetBatVol(ADCBuffer);

//	if(statuserr == 0)
//		{
//			ADCDataProcess(ADCBuffer);
//			datatemp.float32 = UpdateData.StationBatVol;
//			for(i=0;i<4;i++)
//				{
//					*(txbuf+3+i)= datatemp.byte[i];
//				}

//			crc = CRC_Modbus(txbuf, 7);
//			txbuf[7] = (uint8_t)(crc>>8);
//			txbuf[8] = (uint8_t)(crc);
//			SendData(txbuf, sizeof(txbuf));
//		}
//}


void UID_ReadFlash(uint8_t *puid)
{
	FL_DelayMs(100);
	GD25Q16_Read(puid, UID_Addr, 12);
}

void UID_WriteFlash(uint8_t *puid)
{
	FL_DelayMs(100);
	GD25QXX_Write(puid, UID_Addr, 12);
}


void UID_ReadMCU(uint8_t *puid)
{
	uint8_t i;
	for(i=0;i<12;i++)
		{
			*(puid + i) = *(UID +i);
		}
}


void UID_En_Decrypt(uint8_t *pdbuf, uint8_t *psbuf, uint8_t *key)
{
    uint8_t i;
    for (i = 0; i<12; i++)
    	{
			pdbuf[i] = (psbuf[i] ^ key[i % 6]);
    	}
        
}





void Delayus(uint32_t us)
{
	uint16_t num;
	uint16_t i;
	
	for(num = 0; num < us;num++)
	{
		i = 11;
		while(i!=0)
		{
			i--;
		}
		
	}
}

void Delayms(uint32_t ms)
{
	uint16_t num;

	
	for(num = 0; num < ms; num++)
	{
		Delayus(10);
	}
}

