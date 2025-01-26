#include "main.h"
#include "GlobalDef.h"
#include "GlobalTyp.h"
#include "lsm6dsm_reg.h"




uint16_t		FlagGlobal = 0;
uint16_t		FlagCommStatus = 0;
uint16_t		FlagErrorStat = 0;




uint8_t			MagTim32Cnt = 0;
uint16_t		WakeUpCnt = 0;





//uint16_t		CalvePowerSatus = 0;//¿ª¹Ø»ú×´Ì¬




uint16_t		ADCBuffer[ADCLength];


uint8_t  		FlashBuffer[4096] = {0};

//uint8_t  		Lp0Buffer[200] = {0};
//uint8_t			Lp0Buffercnt = 0;
uint8_t  		Lp2Buffer[200] = {0};
//uint8_t			Lp2Buffercnt = 0;

UartBufferTyp	Lp0Rev, Lp2Rev;


XLStructTyp		XYZXLRaw;
uint16_t		XLCnt = 0;
//GryRwaTyp		XYZGryRaw[GryLength];
GryStructTyp		XYZGyRaw;
float			XLX0=0, XLY0=0, XLZ0=0;
int16_t			GyX0=0, GyY0=0, GyZ0=0;


int16_t			Gravity_mg = 0;

uint8_t			DyDiscardCnt = 0;



UpdateDataTyp		UpdateData;
FlashDataAddrTyp	FlashDataAddr;
//BlkUartRcv 			BlkUartRcv;
CfgParaTyp			DevPara;
stmdev_ctx_t 		Dev_ctx;








