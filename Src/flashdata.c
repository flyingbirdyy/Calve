#include "flashdata.h"
#include "gd25q_driver.h"
#include "control.h"
#include "GlobalDef.h"
#include "user_time.h"




//void CheckStoreFlashData(void)
//{
//	FL_RTCA_InitTypeDef		gettime;
//	UpdateDataTyp			readbuf;
//	RTCA_GetRTCA(&gettime);
//
//	uint32_t addr;
//
//	uint32_t i = 0;
//	
//	while()
//	{
//		addr = FlashDataAddr.LineStartAddr + i*sizeof(UpdateData);
//
//		if(addr>Flash_Data_EndAddr)
//		{
//			addr = Flash_Data_StartAddr + (addr - Flash_Data_EndAddr) - 1;
//
//		}
//		
//		GD25Q16_Read((uint8_t *)&readbuf, addr, sizeof(UpdateData));
//		
//		if(calculateDaysDiff(&gettime, UpdateData.Time)>365)
//		{
//			FlashDataAddr.LineStartAddr = addr + sizeof(UpdateData);
//			FlashDataAddr.pktcnt--;
//		}
//		else
//			{
//				Flash_Data_StartAddr = addr;
//				break;
//			}
//		i++;
//
//		if(i>0xFFFFFFFFFFFF)
//		{
//			break;  //should report err lysq
//		}
//	}
//}
//



//void UpdateDataIndex(void)
//{
//	GD25QXX_Write((uint8_t *)&FlashDataAddr, Flash_DataIndex, sizeof(FlashDataAddr));
//}




//void CheckStoreFlashData(void)
//{
//	FL_RTCA_InitTypeDef		gettime;
//	UpdateDataTyp			readbuf;
//	RTCA_GetRTCA(&gettime);
//
//	uint32_t addr;
//
//	uint32_t i = 0;
//
//
//	if(FlashDataAddr.LineStartAddr != FlashDataAddr.LineEndAddr)
//	{
//		GD25Q16_Read((uint8_t *)&readbuf, FlashDataAddr.LineStartAddr, sizeof(readbuf));
//		if(calculateDaysDiff(&gettime, readbuf.Time)>365*2)
//		{
//			FlashDataAddr.LineStartAddr = addr + sizeof(UpdateData);
//			FlashDataAddr.pktcnt--;
//		}
//
//	}
//	
//	
//	}
//}












void StoreData(void)
{
	if(FlagStatusIs(FlagGlobal, Flag_StoreFlashData))
	{
		FlagStatusClear(&FlagGlobal, Flag_StoreFlashData);
		GD25_Wakeup();
		FL_DelayMs(100);
		WritePktFlash((uint8_t *)&DevPara, Flash_DfgData_StartAddr, sizeof(DevPara));
		GD25_Sleep();
	}
	
}




//根据就地址预测flash中的下一个地址
//uint32_t MoveFlashAddr(uint32_t oldaddr)
//{
//	uint32_t addrnext = oldaddr;
//	if(((oldaddr <= Flash_Data_EndAddr) && (Flash_Data_EndAddr - oldaddr < (sizeof(UpdateData) - 1))) || (oldaddr > Flash_Data_EndAddr))
//	{
//		addrnext = oldaddr + sizeof(UpdateData);
//		addrnext = Flash_Data_StartAddr + (addrnext - Flash_Data_EndAddr) - 1;
//	}
//	return addrnext;
//}
//



//void StoreData(void)
//{
//	uint32_t	addr, addrnext;
//	
//	if(FlagStatusIs(FlagGlobal, Flag_StoreFlashData))
//	{
//		FlagStatusClear(&FlagGlobal, Flag_StoreFlashData);
//		UpdateData.Flag_updated = Updating;
//		FlashDataAddr.pktcnt++;
//		if(FlashDataAddr.LineStartAddr >= Flash_Data_StartAddr)
//		{
//			addr = FlashDataAddr.LineEndAddr + sizeof(UpdateData);
//			addr = MoveFlashAddr(addr);
//
//			if(addr > FlashDataAddr.LineStartAddr)
//			{
//				FlashDataAddr.LineStartAddr = MoveFlashAddr(FlashDataAddr.LineStartAddr + sizeof(UpdateData));
//			}
//
//			WritePktFlash((uint8_t *)&UpdateData, addr, sizeof(UpdateData));
//			FlashDataAddr.EndTime = UpdateData.Time;
//			FlashDataAddr.LineEndAddr = addr;
//
//		}
//		else
//		{
//			FlashDataAddr.LineStartAddr = Flash_Data_StartAddr;
//			FlashDataAddr.LineEndAddr = FlashDataAddr.LineStartAddr;
//			FlashDataAddr.StartTime = UpdateData.Time;
//			WritePktFlash((uint8_t *)&UpdateData, FlashDataAddr.LineStartAddr, sizeof(UpdateData));
//		}
//		UpdateDataIndex();
//	}
//	if(FlagStatusIs(FlagGlobal, Flag_StoreFlashCfg))
//		{
//			WritePktFlash((uint8_t *)&DevPara, Flash_DfgData_StartAddr, sizeof(DevPara));
//			FlagStatusClear(&FlagGlobal, Flag_StoreFlashCfg);
//		}
//}
//


//void StoreData(void)
//{
//	uint32_t	addr, addrnext;
//	FL_RTCA_InitTypeDef		time;
//
//	
//	if(FlagStatusIs(FlagGlobal, Flag_StoreFlashData) &&
//		!FlagStatusIs(FlagGlobal, Flag_GetGPS) &&
//		!FlagStatusIs(FlagGlobal, Flag_GetSensors) &&
//		!FlagStatusIs(FlagGlobal, Flag_GetGSense) &&
//		!FlagStatusIs(FlagGlobal, Flag_GetCalve)
//		)
//	{
//		V3V3On;
//		FL_DelayMs(100);
//		FlagStatusClear(&FlagGlobal, Flag_StoreFlashData);
//		UpdateData.Flag_updated = Updating;
//		FlashDataAddr.pktcnt++;
//		RTCA_GetRTCA(&time);
//		 UpdateData.Time.year =  BcdToHex(time.year);
//		 UpdateData.Time.month =  BcdToHex(time.month);
//		 UpdateData.Time.day =  BcdToHex(time.day);
//		 UpdateData.Time.hour =  BcdToHex(time.hour);
//		 UpdateData.Time.minute =  BcdToHex(time.minute);
//		 UpdateData.Time.second =  BcdToHex(time.second);
////		addr = FlashDataAddr.LineStartAddr + sizeof(UpdateData) - 1;
//		if(FlashDataAddr.LineNextStartAddr != 0)
//			{
//				FlashDataAddr.LineStartAddr = FlashDataAddr.LineNextStartAddr;
//			}
//
//		addr = FlashDataAddr.LineStartAddr + sizeof(UpdateData) - 1;
//		if(addr > Flash_Data_EndAddr)
//			{
//				FlashDataAddr.LineStartAddr = Flash_Data_StartAddr;
//			}
//		else
//			{
//				FlashDataAddr.LineEndAddr = FlashDataAddr.LineStartAddr + sizeof(UpdateData) - 1;
//				
//			}
//		GD25QXX_Write((uint8_t *)&UpdateData, FlashDataAddr.LineStartAddr, sizeof(UpdateData));
//		FlashDataAddr.LineNextStartAddr = FlashDataAddr.LineStartAddr + sizeof(UpdateData);
//		if(FlashDataAddr.LineNextStartAddr > Flash_Data_EndAddr)
//			{
//				FlashDataAddr.LineStartAddr = Flash_Data_StartAddr;
//			}
//
//		UpdateDataIndex();
//	}
//	if(FlagStatusIs(FlagGlobal, Flag_StoreFlashCfg))
//		{
//			GD25QXX_Write((uint8_t *)&DevPara, Flash_DfgData_StartAddr, sizeof(DevPara));
//			FlagStatusClear(&FlagGlobal, Flag_StoreFlashCfg);
//		}
//}


//void CfgFlashProc(void)
//{
//	if(FlagStatusIs(FlagGlobal, Flag_StoreFlashCfg))
//		{
//			GD25QXX_Write((uint8_t *)&DevPara, Flash_DfgData_StartAddr, sizeof(DevPara));
//			FlagStatusClear(&FlagGlobal, Flag_StoreFlashCfg);
//		}
//}



