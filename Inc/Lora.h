#ifndef LORA_H
#define	LORA_H


#include "main.h"
#include "globaldef.h"
#include "globaltyp.h"








typedef enum
{
  NormalMode       ,
  WakeUpMode       ,
  LowPowerMode     ,
  SleepMode        ,
} LoraModeTyp;



typedef enum
{
  B1200			       	,
  B2400			       	,
  B4800					,
  B9600			        ,
  B19200				,
  B38400				,
  B57600				,
  B115200				,
} LoraUartBaudTyp;


typedef enum
{
  B1K			       	,
  B2K			       	,
  B5K					,
  B8K			        ,
  B10K					,
  B15K					,
  B20K					,
  B25K					,
} LoraAirBaudTyp;



typedef struct
{
	uint8_t		Head		:8;
	uint8_t		AddH		:8;
	uint8_t		AddL		:8;
	uint8_t		Sped_AirBaud	:3;
	uint8_t		Sped_UartBaud	:3;
	uint8_t		Sped_Parity	:2;
	uint8_t		Chan;
	uint8_t		Opt;
}LoraParaTyp;



void ModeSet(LoraModeTyp loramode);
void LoraParaGet(void);
void SetAddr(uint16_t addr);
uint8_t SetAirChan(uint8_t chan);  //0x50H      433mHz, 0x00~0xFF, 425~450.5MHz
uint8_t SetAirBaud(LoraAirBaudTyp baud);
uint8_t SetUartBaud(LoraUartBaudTyp baud);
void LoraReset(void);
void Update_Lora(void);
void LoraRxPrce(UartBufferTyp *rxdata);
void TransmitData(uint8_t *data, uint8_t length);
void ConfigWirlessModule(UartBufferTyp *data);
void GetRFChan(uint8_t *data);






#endif




