#ifndef IMU_H
#define	IMU_H


#include "main.h"
#include "globaldef.h"
#include "globaltyp.h"



//int32_t platform_write(SPI_Type *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
//int32_t platform_read(SPI_Type *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

void getangle();
void GetGsense0(void);
void GetGsense(void);
float GetAngle(float newAngle, float newRate, float dt);
void lsm6dsmDeInit(void);
void GetAcc(XLRwaTyp *xlraw);
void GetGry(GryRwaTyp *grywaw);
void GetDryrate0(void);
void lsm6dsmActInit(void);
void lsm6dsmHiInit(void);
void lsm6dsmACCInit(void);
void lsm6dsmDRYInit(void);

#endif



