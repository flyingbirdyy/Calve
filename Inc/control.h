#ifndef CONTROL_H
#define	CONTROL_H


#include "main.h"
#include "globalval.h"
#include "globaldef.h"
#include "globaltyp.h"



uint16_t CRC_Modbus (uint8_t *ptr, uint16_t len);

uint16_t FormatData(char *dstdata, char *sourcedatabuf);
void AlarmCheck(void);
void ConfigDev(void);
void SysSleep(void);
void FlagStatusClear(uint16_t *status, uint16_t flagstatus);
void FlagStatusSet(uint16_t *status, uint16_t flagstatus);
uint8_t FlagStatusIs(uint16_t status, uint16_t flagstatus);
void CalCalveTimeComplete(void);
void CalveDataProcess(uint8_t *data);
void SetCalvStartPoint(uint8_t *data);
void SetCalvEndPoint(uint8_t *data);
void ReadCalvBatt(void);

//void ReadIMEI(void);
void SetupdateTime(uint8_t *data);
void DevInit(void);
uint8_t HexToBcd(uint8_t hexData);
//void ProcessSensors(void);
void ASCIItoBCD(char *asc, uint8_t *bcd, uint8_t len);
uint8_t BCD_ADD(uint8_t bcd1, uint8_t bcd2);
void OpenTask(void);
void RestoreDevPara(void);
void ReadDevPara(CfgParaTyp *cfg, uint8_t length);
uint8_t BcdToHex(uint8_t bcdData);
void SysSleepTest(void);
void DisablePeripheral(void);
void EnPeripheral(void);
void UID_ReadFlash(uint8_t *puid);
void UID_WriteFlash(uint8_t *puid);
void UID_ReadMCU(uint8_t *puid);
void UID_En_Decrypt(uint8_t *pdbuf, uint8_t *psbuf, uint8_t *key);
//float Retain_Two_Decimals(float num);
//float Retain_One_Decimals(float num);
void SetSerialNo(uint8_t *data);
void Delayms(uint32_t ms);
void Delayus(uint32_t us);
void DevDeInit(void);
void DeInitPeripheral(void);



#endif
