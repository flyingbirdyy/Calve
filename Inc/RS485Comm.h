#ifndef RS485COMM_H
#define	RS485COMM_H

#include "main.h"


//void SendData(uint8_t *data, uint8_t length);
//void SendGetCalveDataCmd(void);
void ProcessPkt(uint8_t *data);
void ProcessPktUID(UartBufferTyp *data);

#endif
