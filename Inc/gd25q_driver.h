


#ifndef GD25Q_DRIVER_H
#define GD25Q_DRIVER_H

#include "main.h"
#include "GlobalTyp.h"


#define GD25Q_WriteEnable		0x06
#define GD25Q_WriteDisable		0x04
#define GD25Q_ReadStatusReg1		0x05
#define GD25Q_ReadStatusReg2		0x35
#define GD25Q_ReadStatusReg3		0x15
#define GD25Q_WriteStatusReg1    0x01
#define GD25Q_WriteStatusReg2    0x31
#define GD25Q_WriteStatusReg3    0x11
#define GD25Q_WriteSREnable		0x50
#define GD25Q_ReadData			0x03
#define GD25Q_FastReadData		0x0B
#define GD25Q_FastReadDual		0x3B
#define GD25Q_FastReadQuadIO		0xEB
#define	GD25Q_FstReadQ_4Addr		0x6C
#define GD25Q_PageProgram		0x02
#define GD25Q_PageProgram_4Addr	0x34//0x02
#define GD25Q_BlockErase			0x52
#define GD25Q_SectorErase		0x20
#define GD25Q_ChipErase			0xC7
#define GD25Q_PowerDown			0xB9
#define GD25Q_ReleasePowerDown	0xAB
#define GD25Q_DeviceID			0xAB
#define GD25Q_ManufactDeviceID	0x90
#define GD25Q_JedecDeviceID		0x9F
#define GD25Q_Enable4ByteAddr    0xB7
#define GD25Q_Exit4ByteAddr      0xE9
#define GD25Q_SetReadParam		0xC0
#define GD25Q_EnterQPIMode       0x38
#define GD25Q_ExitQPIMode        0xFF
#define RESET_ENABLE_CMD		0x66
#define RESET_MEMORY_CMD		0x99
#define	GD25Q_FastReadQuadIO_4a	0x6C


#define GD25Q128_PAGE_SIZE       256U
#define GD25Q128_Sector_SIZE     4096U
#define PktstartAddr			 0U
#define PkeEndAddr				0xFFEFFF
#define DevParaStartAddr		0xFFF000






typedef struct
{
	uint32_t		pktaddr;
	uint32_t		pktcnt;
	uint16_t		pktlength;				

}FlashshStatusTypDef;




extern FlashshStatusTypDef									FlashPktInfo;





void GD_Init(void);
void GD_WritePage(uint32_t address, uint8_t* data);
void GD_ReadPage(uint32_t address, uint8_t* result);
void GD_WriteEnable();
uint8_t GD_GetStatusLow();
uint8_t GD_GetStatusHigh();
void GD25QXX_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr, uint16_t size);
void GD25_Sleep(void);
void GD25_Wakeup(void);
void GD25QXX_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);   
//void GD25Q16_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);
uint8_t GD25Q16_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);

//void WritePktFlash(uint8_t *pbuf, FlashDataAddrTyp *flashaddr, uint16_t length);
void WritePktFlash(uint8_t *pbuf, uint32_t flashaddr, uint16_t length);
void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);
void GD25QXX_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void GD25QXX_Erase_Sector(uint32_t Dst_Addr);
void GD25QXX_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
uint16_t SPI_Flash_ReadID(void);
uint8_t SPI_Flash_ReadSR(void);
uint8_t SPIx_ReadWriteByte(SPI_Type *handle, uint8_t TxData);


#endif /* __GD25QDRIVER_H*/   
