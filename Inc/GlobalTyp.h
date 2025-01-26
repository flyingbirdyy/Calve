#ifndef GLOBALTYP_H
#define	GLOBALTYP_H

#include "main.h"
#include "kalman.h"



typedef enum
{
	SleepState,
	WakeupState
}WakeUpTyp;





typedef struct
{
	uint16_t					addr;
	uint8_t						ValveBatVal;
	int32_t						valvedegree;
}UpdateDataTyp;



typedef struct
{
	uint32_t					LineStartAddr;
	uint32_t					LineNextStartAddr;
	FL_RTCA_InitTypeDef			StartTime;
	uint32_t					LineEndAddr;
	FL_RTCA_InitTypeDef			EndTime;
	uint32_t					pktcnt;
}FlashDataAddrTyp;


typedef struct
{
	float			WaterPresureThreshold_Lo;
	float			WaterPresureThreshold_Hi;
	uint8_t			TiltAngleThreshold;
	uint8_t			WaterTempThreshold;
}AlarmThresholdTyp;


typedef struct
{
	uint8_t					CfgHead;
	uint8_t					RF_Chan;
	uint8_t					SerialNo[8];
	uint8_t					Key[6];
	uint16_t				addr;
}CfgParaTyp;





typedef struct
{
	int16_t xraw;
	int16_t yraw;
	int16_t zraw;
}XLRwaTyp;



typedef struct
{
	XLRwaTyp	XLRwa;
	float	xmg0;
	float	ymg0;
	float	zmg0;
}XLStructTyp;




typedef struct
{
	int16_t xraw;
	int16_t yraw;
	int16_t zraw;
}GryRwaTyp;



typedef struct
{
	GryRwaTyp	GryRwa[DryDatalebgth];
	float	xrrate0;
	float	yrrate0;
	float	zrrate0;
	float	xrrate;
	float	yrrate;
	float	zrrate;
	float	rate0;
	float	rate;
	float	angle;
	float	xangle;
	float	yangle;
	float	zangle;
	float	accxangle;
	float  accyangle;
	float  acczangle;
	float	xanglenofilter;
	float	yanglenofilter;
	float	zanglenofilter;
	uint16_t	nextpoint;
	uint16_t	startpoint;
}GryStructTyp;




typedef struct
{
	uint8_t  Buffer[250];
	uint8_t  length;
	uint8_t	 bufcnt;
	uint8_t  timcnt;
	uint8_t  newpkt;
}UartBufferTyp;


typedef struct
{
	int16_t		XLRaw;
	int16_t		YLRaw;
	int16_t		ZLRaw;
	float		XL0mg;
	float		YL0mg;
	float		ZL0mg;
}GCCTyp;


typedef struct
{
	int16_t		GYXRaw;
	int16_t		GYYRaw;
	int16_t		GYZRaw;
	float		GYX0Rud;
	float		GYY0Rud;
	float		GYZ0Rud;
}GRYTyp;





typedef union
{
  uint8_t  byte[4];
  float    float32;
}s_btf;

typedef union
{
  uint8_t       byte[4];
  uint32_t      uint32;
}s_btui32;


typedef union
{
  uint8_t       byte[2];
  uint16_t      uint16;
}s_btui16;


typedef union
{
  uint8_t       byte[2];
  int16_t       int16;
}s_bti16;


#endif

