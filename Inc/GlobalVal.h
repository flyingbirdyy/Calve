

#ifndef GLOBALVAL_H
#define	GLOBALVAL_H

#include "main.h"
#include "globaldef.h"
#include "globaltyp.h"
#include "LSM6DSM_REG.H"



extern uint16_t			FlagCommStatus;
extern uint16_t			FlagGlobal;
extern uint16_t			FlagErrorStat;



extern uint16_t			ADCBuffer[ADCLength];
extern uint8_t			GPSRevBuf[500];
extern uint8_t			NBRevBuf[500];
extern uint8_t			CalveRevBuf[100];
extern uint8_t			FlashBuffer[4096];
extern uint8_t			LPUARTBuf[200];

extern uint8_t  		Lp2Buffer[200];


extern uint16_t			GPSRevBufCnt;
extern uint16_t			NBRevBufCnt;
extern uint16_t			CalveRevBufCnt;
extern uint8_t			CalveTimeoutCnt;
extern uint16_t			GPSWaiteTimeoutCnt;

extern uint8_t			MagTim32Cnt;

extern uint16_t			WakeUpCnt;

extern UpdateDataTyp		UpdateData;
extern FlashDataAddrTyp		FlashDataAddr;
//extern BlkUartRcv 			BlkUartRcv;
extern CfgParaTyp			DevPara;
extern stmdev_ctx_t 		Dev_ctx;
extern XLStructTyp		  	XYZXLRaw;
//extern GryRwaTyp		XYZGryRaw[GryLength];
extern GryStructTyp		XYZGyRaw;
//extern uint16_t			XLCnt;
//extern uint16_t			GryCnt;
extern float			XLX0, XLY0, XLZ0;
extern int16_t			GyX0, GyY0, GyZ0;
//extern float			NewAngle;



extern	float				P[2][2];
extern  uint8_t			DyDiscardCnt;
extern int16_t			Gravity_mg;
extern UartBufferTyp	Lp0Rev;
extern UartBufferTyp    Lp2Rev;
#endif