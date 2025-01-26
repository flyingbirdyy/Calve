

#ifndef GETSENSORS_H
#define	GETSENSORS_H

#include "main.h"




//void StartADC(uint16_t *adcbuf, uint8_t length);
void GetVoltage(void);
void GetRef(uint16_t *databuff);
void GetBatVol(uint16_t *databuff);


#endif



