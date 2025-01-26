#ifndef GLOBALDEF_H
#define	GLOBALDEF_H

#define debug


#define Flag_WakeUpCnt												0x0001
#define	Flag_MotionDetect											0x0002
#define	Flag_GryReady												0x0004
#define	Flag_GetBatVoltage											0x0008
#define Flag_DecryptFail											0x0010
#define Flag_KeyAct													0x0020
#define Flag_PowerOnInit											0x0040
#define Flag_MagTim32Start											0x0080
//#define	Flag_StatTimout												0x0100
//#define Flag_StoreFlashCfg											0x0200
#define	Flag_Stat_PowerOn											0x0400   //true status of power on, false status of power down.
#define Flag_PowerDownDeInit										0x0800
#define Flag_WirlessCom												0x1000
#define Flag_GetG0													0x2000
#define Flag_InitDy													0x4000
#define Flag_StoreFlashData											0x8000


//#define	Stat_PowerDown												0x0000000000000000
//#define	Stat_PowerOn												0x0000000000000001  //0: pown down   1: power on
//#define Stat_PowerRun												0x0000000000000010


#define Stat_LP0_Start_RevTimout									0x0001
#define Stat_LP2_Start_RevTimout									0x0002
#define Stat_LP0_Receive_Complete									0x0004
#define Stat_LP2_Receive_Complete									0x0008





#define	Stat_RS485_Receive_Complete									0x0001
#define	Stat_RS485_Start_RevTimout									0x0002
#define	RS485_RevTimout												5U					//x100ms





#define Err_IMU_Fail												0x0001
#define Err_Z_Flat													0x0002

#define IMUDataLength												64






#define ADCLength													(uint8_t)1

#define	RefRaw														(uint8_t)0
//#define BatRaw														(uint8_t)2

#define RefVol														1.25
#define BatFul														3.6
#define BatEmpt														3.0



//#define Flash_Data_StartAddr										0x1000
#define Flash_Data_EndAddr											0x7FFFFF
#define Flash_DfgData_StartAddr										0x0000
#define UID_Addr													0x0700
#define	Flash_Bootloader											0x0800

//#define Flash_DfgData_EndAddr										0x0FFF


#define TIMEOUT_VAL     											(0xFFFFFFFFUL)


#define VCC3On														FL_GPIO_SetOutputPin(GPIOA, FL_GPIO_PIN_7)
#define VCC3Off														FL_GPIO_ResetOutputPin(GPIOA, FL_GPIO_PIN_7)



#define LEDOn														FL_GPIO_SetOutputPin(GPIOC, FL_GPIO_PIN_0)
#define LEDOff														FL_GPIO_ResetOutputPin(GPIOC, FL_GPIO_PIN_0)
#define TogLED														FL_GPIO_ToggleOutputPin(GPIOC, FL_GPIO_PIN_0)
																	

#define REFOn														FL_GPIO_SetOutputPin(GPIOA, FL_GPIO_PIN_1)
#define REFOff														FL_GPIO_ResetOutputPin(GPIOA, FL_GPIO_PIN_1)


#define GCS_Hi														FL_GPIO_SetOutputPin(GPIOC, FL_GPIO_PIN_7)	
#define GCS_Lo														FL_GPIO_ResetOutputPin(GPIOC, FL_GPIO_PIN_7)



#define	Updated														(uint8_t)0
#define	Updating													(uint8_t)1

#define StatTimout													(uint8_t)300//0.5min


#define UID           												((uint32_t *)0x1FFFFA10)





#define HAL_OK														0
#define HAL_TIMEOUT													1
#define TRUE														1
#define FALSE														0






#endif

