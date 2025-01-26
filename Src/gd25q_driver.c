
#include "gd25q_driver.h"
#include "main.h"
#include "GlobalDef.h "
#include "GlobalVal.h"


FlashshStatusTypDef									FlashPktInfo = {0};


//void GD_Init(void){
//
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
//    RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO  | 
//                            RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI0, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//    SPI_InitTypeDef SPI_InitStructure;
//
//
//		/* Configure SPI0 pins: SCK(PA5) and MOSI (PA7)----*/
//        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5  | GPIO_Pin_7;
//        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
//        GPIO_Init(GPIOA, &GPIO_InitStructure);
//        
//		/*MISO Stupid logic (Input pull up)*/
//		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//        
//        /* Configure PA4 as CS (Chip select)  -------------------------------*/
//        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;//
//        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
//        GPIO_Init(GPIOA, &GPIO_InitStructure);              
//        GPIOA->BSRR=GPIO_Pin_4;          
//
//
//              
//        /* SPI0 Configuration ----------------------------------------------------*/
//
//          SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//          SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//          SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//          //If CPOL is reset, the SCK pin has a low-level idle state.
//          SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//          SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//          SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//          SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//          SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
//          SPI_InitStructure.SPI_CRCPolynomial = 8;
//          SPI_Init(SPI0, &SPI_InitStructure);   
//          
//          /* Enable SPI0 */
//          SPI_Cmd(SPI0, ENABLE);
//
////GPIOA->BSRR=GPIO_Pin_11;//WP
////GPIOA->BSRR=GPIO_Pin_12;//HOLD
//
//}


//Chip deselect
void cd(void)
{
	FL_GPIO_SetOutputPin(GPIOB, FL_GPIO_PIN_8);
}
//Chip select
void cs(void)
{
	FL_GPIO_ResetOutputPin(GPIOB, FL_GPIO_PIN_8);
}
//receive dummy
uint8_t receive_dummy(void)
{

	FL_DelayMsStart(500);

	for(;;)
		{
			if(FL_DelayEnd() || FL_SPI_IsActiveFlag_RXBuffFull(SPI0))
				{
					break;
				}
		}
//	while(!FL_SPI_IsActiveFlag_RXBuffFull(SPI0) && !FL_DelayEnd());
    return FL_SPI_ReadRXBuff(SPI0); 
}
//send dummy
void send_dummy(void)
{

    FL_SPI_WriteTXBuff(SPI0,0x00);
	FL_DelayMsStart(500);

	for(;;)
		{
			if(FL_DelayEnd() || FL_SPI_IsActiveFlag_TXBuffEmpty(SPI0))
				{
					break;
				}
		}


	
//	while(!FL_SPI_IsActiveFlag_TXBuffEmpty(SPI0) && !FL_DelayEnd());
}


uint8_t GD_SendCommand1Anwer1(uint8_t command)
{
	uint8_t result=0; 

	
	cs();
	FL_SPI_WriteTXBuff(SPI0,command);
	FL_DelayMsStart(500);


	for(;;)
		{
			if(FL_DelayEnd() || FL_SPI_IsActiveFlag_TXBuffEmpty(SPI0))
				{
					break;
				}
		}


	
//	while(!FL_SPI_IsActiveFlag_TXBuffEmpty(SPI0) && !FL_DelayEnd());
     
     
	 //receive dummy
     receive_dummy();     
     
     //send dummy
     send_dummy();

     //receive data
	FL_DelayMsStart(500);

	 for(;;)
		 {
			 if(FL_DelayEnd() || FL_SPI_IsActiveFlag_RXBuffFull(SPI0))
				 {
					 break;
				 }
		 }

	
//     while(!FL_SPI_IsActiveFlag_RXBuffFull(SPI0) && !FL_DelayEnd());
     result = FL_SPI_ReadRXBuff(SPI0);

     cd();
	 return result;
}

void GD_SendCommand(uint8_t command)
{
     cs();
	 //send command
	 FL_SPI_WriteTXBuff(SPI0,command);   
	FL_DelayMsStart(500);

	 for(;;)
		 {
			 if(FL_DelayEnd() || FL_SPI_IsActiveFlag_TXBuffEmpty(SPI0))
				 {
					 break;
				 }
		 }

	
//     while(!FL_SPI_IsActiveFlag_TXBuffEmpty(SPI0) && !FL_DelayEnd());
     
     cd();  
}

void GD_WriteEnable(void)
{
	GD_SendCommand(0x06);
}

uint8_t GD_GetStatus1(void)
{
	return GD_SendCommand1Anwer1(0x05);
}
uint8_t GD_GetStatus2(void)
{
	return GD_SendCommand1Anwer1(0x35);
}
//uint8_t GD_GetStatus3(void)
//{
//	return GD_SendCommand1Anwer1(0x15);
//}

uint8_t GD_WriteStatus1(void)
{
	return GD_SendCommand1Anwer1(0x05);
}
uint8_t GD_WriteStatus2(void)
{
	return GD_SendCommand1Anwer1(0x35);
}
//uint8_t GD_WriteStatus3(void)
//{
//	return GD_SendCommand1Anwer1(0x15);
//}


uint16_t GD25Q_ReadID(void)
{
	uint8_t     getdata[2] = {0};
	uint16_t	returndata = 0;
	uint8_t i=0;
	
	cs();
	GD_SendCommand(0x90);
	send_dummy();
	send_dummy();
	send_dummy();

	for(i=0;i<2;i++)
	{
		getdata[i] = receive_dummy();

	}
	returndata = getdata[0];
	returndata |= getdata[1];
	return returndata;
}

/**	
	*??3?¡êoSPIx_ReadWriteByte
	*¨º?¨¨?¡êoTxData ¨°aD¡ä¨¨?¦Ì?¡Á??¨²
	*¨º?3?¡êo
	*¡¤¦Ì??¡êo?¨¢¨¨?¦Ì?¦Ì?¡Á??¨²
	*1|?¨¹¡êo?¨¢D¡ä¨°???¡Á??¨²
	*?¦Ì?¡Â¡êo
**/
uint8_t SPIx_ReadWriteByte(SPI_Type *handle, uint8_t TxData)
{		
    FL_SPI_WriteTXBuff(handle,TxData);

//	while (!FL_SPI_IsActiveFlag_TXBuffEmpty(handle));
//	while (!FL_SPI_IsActiveFlag_RXBuffFull(handle));
	
	FL_DelayMsStart(1000);

	for(;;)
		{
			if(FL_DelayEnd() || FL_SPI_IsActiveFlag_TXBuffEmpty(handle))
				{
					break;
				}
		}


//	while ((!FL_SPI_IsActiveFlag_TXBuffEmpty(handle)) && (!FL_DelayEnd()));
	FL_DelayMsStart(1000);

	for(;;)
		{
			if(FL_DelayEnd() || FL_SPI_IsActiveFlag_RXBuffFull(handle))
				{
					break;
				}
		}


	
//	while ((!FL_SPI_IsActiveFlag_RXBuffFull(handle))  && (!FL_DelayEnd()));
    return FL_SPI_ReadRXBuff(handle);
	
//	return RxData;				    
}

/**
	*??3?¡êoSPI_Flash_Read
	*¨º?¨¨?¡êoReadAddr ?a¨º??¨¢¨¨?¦Ì?¦Ì??¡¤(24bit)
		   NumByteToRead ¨°a?¨¢¨¨?¦Ì?¡Á??¨²¨ºy(¡Á?¡ä¨®65535)
	*¨º?3?: pBuffer ???¨°¦Ì?¨ºy¡Á¨¦
	*¡¤¦Ì??¡êo?T
	*1|?¨¹¡êo?¨²???¡§¦Ì??¡¤?a¨º??¨¢¨¨????¡§3¡è?¨¨¦Ì?¨ºy?Y		   
	*?¦Ì?¡Â¡êo
**/
void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{ 
 	uint16_t i;    
	cs();                           //¨º1?¨¹?¡Â?t   
    SPIx_ReadWriteByte(SPI0, GD25Q_ReadData);         //¡¤¡é?¨ª?¨¢¨¨??¨¹¨¢?   
    SPIx_ReadWriteByte(SPI0, (uint8_t)((ReadAddr)>>16));  //¡¤¡é?¨ª24bit¦Ì??¡¤    
    SPIx_ReadWriteByte(SPI0, (uint8_t)((ReadAddr)>>8));   
    SPIx_ReadWriteByte(SPI0, (uint8_t)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
		{ 
        pBuffer[i]=SPIx_ReadWriteByte(SPI0, 0XFF);   //?-?¡¤?¨¢¨ºy  
    }
	cd();                           //¨¨???????     	      
}

//?¨¢¨¨?SPI_FLASH¦Ì?¡Á¡ä¨¬???¡ä??¡Â
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:??¨¨?0,¡Á¡ä¨¬???¡ä??¡Â¡À¡ê?¡è??,??o?WP¨º1¨®?
//TB,BP2,BP1,BP0:FLASH??¨®¨°D¡ä¡À¡ê?¡è¨¦¨¨??
//WEL:D¡ä¨º1?¨¹???¡§
//BUSY:?|¡À¨º????(1,?|;0,???D)
//??¨¨?:0x00
uint8_t SPI_Flash_ReadSR(void)   
{  
	uint8_t byte=0;   
	cs();                            //¨º1?¨¹?¡Â?t   
	SPIx_ReadWriteByte(SPI0, GD25Q_ReadStatusReg1);    //¡¤¡é?¨ª?¨¢¨¨?¡Á¡ä¨¬???¡ä??¡Â?¨¹¨¢?    
	byte=SPIx_ReadWriteByte(SPI0, 0Xff);             //?¨¢¨¨?¨°???¡Á??¨²  
	cd();                            //¨¨???????     
	return byte;   
} 

//¦Ì¨¨¡äy???D
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // ¦Ì¨¨¡äyBUSY??????
}
 
//SPI_FLASHD¡ä¨º1?¨¹	
//??WEL????   
void SPI_FLASH_Write_Enable(void)   
{
	cs();                            //¨º1?¨¹?¡Â?t   
    SPIx_ReadWriteByte(SPI0, GD25Q_WriteEnable);      //¡¤¡é?¨ªD¡ä¨º1?¨¹  
	cd();                            //¨¨???????     	      
} 

/**
	*??3?¡êoSPI_Flash_Erase_Chip
	*¨º?¨¨?¡êo?T
	*¨º?3?¡êo?T
	*¡¤¦Ì??¡êo?T
	*1|?¨¹¡êo2¨¢3y????D???????2¨¢3y¨º¡À??:
		   GD25X16:25s 
		   GD25X32:40s 
		   GD25X64:40s 
		   ¦Ì¨¨¡äy¨º¡À??3?3¡è...
	*?¦Ì?¡Â¡êo2¨¢3y¨º¡À??¨¤¡ä?¡ä¨®¨²¨º?2¨¢¡ê?¨®D¡äy?¨¦?¡è

**/
void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_FLASH_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
  	cs();                            //¨º1?¨¹?¡Â?t   
    SPIx_ReadWriteByte(SPI0, GD25Q_ChipErase);        //¡¤¡é?¨ª??2¨¢3y?¨¹¨¢?  
		cd();                          //¨¨???????     	      
		SPI_Flash_Wait_Busy();   				   //¦Ì¨¨¡äyD???2¨¢3y?¨¢¨º?
} 

//2¨¢3y¨°???¨¦¨¨??
//Dst_Addr:¨¦¨¨??¦Ì??¡¤ ?¨´?Y¨º¦Ì?¨º¨¨Y¨¢?¨¦¨¨??
//2¨¢3y¨°???¨¦???¦Ì?¡Á?¨¦¨´¨º¡À??:150ms
void GD25QXX_Erase_Sector(uint32_t sector_no)   //sector_no: sector number
{  
	//?¨¤¨º¨®falsh2¨¢3y?¨¦??,2a¨º?¨®?   
// 	printf("fe:%x\r\n",Dst_Addr);	  
  	sector_no*=4096;
    SPI_FLASH_Write_Enable();                  //SET WEL 	 
    SPI_Flash_Wait_Busy();   
		cs();                             //¨º1?¨¹?¡Â?t   
    SPIx_ReadWriteByte(SPI0, GD25Q_SectorErase);      //¡¤¡é?¨ª¨¦¨¨??2¨¢3y??¨¢? 
    SPIx_ReadWriteByte(SPI0, (uint8_t)((sector_no)>>16));  //¡¤¡é?¨ª24bit¦Ì??¡¤    
    SPIx_ReadWriteByte(SPI0, (uint8_t)((sector_no)>>8));   
    SPIx_ReadWriteByte(SPI0, (uint8_t)sector_no);  
	  cd();                             //¨¨???????     	      
		SPI_Flash_Wait_Busy();  				   //¦Ì¨¨¡äy2¨¢3y¨ª¨º3¨¦
}  
/**
	*??3?¡êoSPI_Flash_Write_Page
	*¨º?¨¨?¡êoWriteAddr ?a¨º?D¡ä¨¨?¦Ì?¦Ì??¡¤
	       NumByteToWrite ¨°aD¡ä¨¨?¦Ì?¡Á??¨²¨ºy(¡Á?¡ä¨®256)¡ê???¨ºy2?¨®|??3?1y??¨°3¦Ì?¨º¡ê¨®¨¤¡Á??¨²¨ºy¡ê?¡ê?¡ê?
	*¨º?3?¡êopBuffer ¨ºy?Y¡ä?¡ä¡é??
	*¡¤¦Ì??¡êo?T
	*1|?¨¹¡êo?¨²???¡§¦Ì??¡¤?a¨º?D¡ä¨¨?¡Á?¡ä¨®256¡Á??¨²¦Ì?¨ºy?Y
	*?¦Ì?¡Â¡êoSPI?¨²¨°?¨°3(0~65535)?¨²D¡ä¨¨?¨¦¨´¨®¨²256??¡Á??¨²¦Ì?¨ºy?Y
**/	 					
void SPI_Flash_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
 	  uint16_t i;  
    SPI_FLASH_Write_Enable();                  //SET WEL 
  	cs();                            //¨º1?¨¹?¡Â?t   
    SPIx_ReadWriteByte(SPI0, GD25Q_PageProgram);      //¡¤¡é?¨ªD¡ä¨°3?¨¹¨¢?   
    SPIx_ReadWriteByte(SPI0, (uint8_t)((WriteAddr)>>16)); //¡¤¡é?¨ª24bit¦Ì??¡¤    
    SPIx_ReadWriteByte(SPI0, (uint8_t)((WriteAddr)>>8));   
    SPIx_ReadWriteByte(SPI0, (uint8_t)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++) SPIx_ReadWriteByte(SPI0, pBuffer[i]);//?-?¡¤D¡ä¨ºy  
	  cd();                           //¨¨??????? 
	  SPI_Flash_Wait_Busy();					   //¦Ì¨¨¡äyD¡ä¨¨??¨¢¨º?
} 

/**
	*??3?¡êoSPI_Flash_ReadID
	*1|?¨¹¡êo?¨¢¨¨?D???ID  W25X16¦Ì?ID:0XEF14
**/
uint16_t SPI_Flash_ReadID(void)
{
	uint16_t Temp = 0;	  
	cs();
	SPIx_ReadWriteByte(SPI0, GD25Q_ManufactDeviceID);     /*¡¤¡é?¨ª?¨¢¨¨?ID?¨¹¨¢?*/	    
	SPIx_ReadWriteByte(SPI0, 0x00); 	    
	SPIx_ReadWriteByte(SPI0, 0x00); 	    
	SPIx_ReadWriteByte(SPI0, 0x00); 	 			   
	Temp|=SPIx_ReadWriteByte(SPI0, 0xFF)<<8;  
	Temp|=SPIx_ReadWriteByte(SPI0, 0xFF);	 
	cd();				    
	return Temp;
}




//void GD25Q16_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)
//{
////	uint8_t	readbuf1[NumByteToRead] = {0
//	uint8_t	readbuf1[4096] = {0};
//	uint8_t cnt1 = 0;
//	uint8_t cnt2 = 0;
//	uint8_t i, j = 0;
//
//	if(Flash_Data_EndAddr - ReadAddr < NumByteToRead - 1)
//	{
//		SPI_Flash_Read(pBuffer, ReadAddr, Flash_Data_EndAddr - ReadAddr + 1);
//		cnt1 = Flash_Data_EndAddr - ReadAddr + 1;
//		cnt2 = NumByteToRead - (Flash_Data_EndAddr - ReadAddr + 1);
//		SPI_Flash_Read(readbuf1, Flash_Data_StartAddr, cnt2);
//		for(i=cnt1-1; i<cnt2 ; i++, j++)
//		{
//			*(pBuffer+i) = readbuf1[j];
//		}
//
//	}
//	else
//		{
//			SPI_Flash_Read(pBuffer,ReadAddr, NumByteToRead);
//		}
// 	
//}


uint8_t GD25Q16_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)
{
//	uint8_t	readbuf1[NumByteToRead] = {0
//	uint8_t	readbuf1[4096] = {0};
//	uint8_t cnt1 = 0;
//	uint8_t cnt2 = 0;
//	uint8_t i, j = 0;

	if(Flash_Data_EndAddr - ReadAddr < NumByteToRead - 1)
	{

		return 1;
	}
	else
		{
			SPI_Flash_Read(pBuffer,ReadAddr, NumByteToRead);
			return 0;
		}
 	
}




//?T?¨¬?¨¦D¡äSPI FLASH 
//¡À?D?¨¨¡¤¡À¡ê?¨´D¡ä¦Ì?¦Ì??¡¤¡¤??¡ì?¨²¦Ì?¨ºy?Y¨¨?2??a0XFF,¡¤??¨°?¨²¡¤?0XFF¡ä|D¡ä¨¨?¦Ì?¨ºy?Y??¨º¡ì¡ã¨¹!
//??¨®D¡Á??¡¥??¨°31|?¨¹ 
//?¨²???¡§¦Ì??¡¤?a¨º?D¡ä¨¨????¡§3¡è?¨¨¦Ì?¨ºy?Y,¦Ì?¨º?¨°a¨¨¡¤¡À¡ê¦Ì??¡¤2?????!
//pBuffer:¨ºy?Y¡ä?¡ä¡é??
//WriteAddr:?a¨º?D¡ä¨¨?¦Ì?¦Ì??¡¤(24bit)
//NumByteToWrite:¨°aD¡ä¨¨?¦Ì?¡Á??¨²¨ºy(¡Á?¡ä¨®65535)
//CHECK OK
void GD25QXX_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 			 		 
	uint16_t pageremain;	   
	pageremain=256-WriteAddr%256; //¦Ì£¤¨°3¨º¡ê¨®¨¤¦Ì?¡Á??¨²¨ºy		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//2?¡ä¨®¨®¨²256??¡Á??¨²
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//D¡ä¨¨??¨¢¨º?¨¢?
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //??¨¨£¤¨°??-D¡ä¨¨?¨¢?¦Ì?¡Á??¨²¨ºy
			if(NumByteToWrite>256)pageremain=256; //¨°?¡ä??¨¦¨°?D¡ä¨¨?256??¡Á??¨²
			else pageremain=NumByteToWrite; 	  //2?1?256??¡Á??¨²¨¢?
		}
	}    
} 


//D¡äSPI FLASH  
//?¨²???¡§¦Ì??¡¤?a¨º?D¡ä¨¨????¡§3¡è?¨¨¦Ì?¨ºy?Y
//??o¡¥¨ºy¡ä?2¨¢3y2¨´¡Á¡Â!
//pBuffer:¨ºy?Y¡ä?¡ä¡é??
//WriteAddr:?a¨º?D¡ä¨¨?¦Ì?¦Ì??¡¤(24bit)						
//NumByteToWrite:¨°aD¡ä¨¨?¦Ì?¡Á??¨²¨ºy(¡Á?¡ä¨®65535)   
		 
void GD25QXX_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    
//	uint8_t *GD25QXX_BUF;
	
	
//  GD25QXX_BUF=FlashBuffer;	     
 	secpos=WriteAddr/4096;//¨¦¨¨??¦Ì??¡¤  
	secoff=WriteAddr%4096;//?¨²¨¦¨¨???¨²¦Ì???¨°?
	secremain=4096-secoff;//¨¦¨¨??¨º¡ê¨®¨¤????¡ä¨®D?   
 	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//2a¨º?¨®?
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//2?¡ä¨®¨®¨²4096??¡Á??¨²
	while(1) 
	{	
		GD25Q16_Read(FlashBuffer,secpos*4096,4096);//?¨¢3?????¨¦¨¨??¦Ì??¨²¨¨Y
		for(i=0;i<secremain;i++)//D¡ê?¨¦¨ºy?Y
		{
			if(FlashBuffer[secoff+i]!=0XFF)
			{
				break;//D¨¨¨°a2¨¢3y  	
			}
		}
		if(i<secremain)//D¨¨¨°a2¨¢3y
		{
			GD25QXX_Erase_Sector(secpos);		//2¨¢3y?a??¨¦¨¨??
			for(i=0;i<secremain;i++)	   		//?¡ä??
			{
				FlashBuffer[i+secoff]=pBuffer[i];	  
			}
			GD25QXX_Write_NoCheck(FlashBuffer,secpos*4096,4096);//D¡ä¨¨?????¨¦¨¨??  

		}
		else 
			{
				GD25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//D¡ä¨°??-2¨¢3y¨¢?¦Ì?,?¡À?¨®D¡ä¨¨?¨¦¨¨??¨º¡ê¨®¨¤????. 	
			}
		if(NumByteToWrite==secremain)
		{
			break;//D¡ä¨¨??¨¢¨º?¨¢?
		}
		else//D¡ä¨¨??¡ä?¨¢¨º?
		{
			secpos++;//¨¦¨¨??¦Ì??¡¤??1
			secoff=0;//??¨°??????a0 	 

		   	pBuffer += secremain;  				//??????¨°?
			WriteAddr += secremain;				//D¡ä¦Ì??¡¤??¨°?	   
		   	NumByteToWrite-=secremain;			//¡Á??¨²¨ºy¦ÌY??
			if(NumByteToWrite>4096)
			{
				secremain = 4096;//??¨°???¨¦¨¨???1¨º?D¡ä2?¨ª¨º
			}
			else 
				secremain = NumByteToWrite;		//??¨°???¨¦¨¨???¨¦¨°?D¡ä¨ª¨º¨¢?
		}	 
	};	 
}
uint8_t GD25Q16_Init(void)
{
	
	//GD25Q16_Configuration();		  /* SPI¨°y???????¡ã3?¨º??¡¥ */
	//test_dat = 0x0;
	//test_dat = SPI_Flash_ReadID();
	if(SPI_Flash_ReadID()==GD25Q_DeviceID)
	//if(test_dat == W25Q16_ID)
	{
		return 0;
	}
	else
  return 1;
}








//void GD25QXX_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr, uint16_t size)
//{
//	uint8_t readbuf[4096];
//
//	uint32_t end_addr, current_size, current_addr;
//
//	volatile uint16_t i;  
//	volatile uint16_t	sectorNo;
//	volatile uint16_t	addrbuf;
//	
//
//	current_addr = 0;
//
//	while (current_addr <= WriteAddr)
//	{
//		current_addr += GD25Q128_PAGE_SIZE;
//	}
//	current_size = current_addr - WriteAddr;
//
//	if (current_size > size)
//	{
//		current_size = size;
//	}
//
//	current_addr = WriteAddr;
//	end_addr = WriteAddr + size;
//
//	do
//	{
//
//		sectorNo = current_addr/GD25Q128_Sector_SIZE;
//		GD25Q16_Read(readbuf, sectorNo*GD25Q128_Sector_SIZE, GD25Q128_Sector_SIZE);
//		addrbuf = current_addr%GD25Q128_Sector_SIZE;
//		for(i=addrbuf;i<current_size;i++)
//		{
//			readbuf[i] = *(pBuffer+i);
//		}
//
//		GD25QXX_Erase_Sector(sectorNo);
//
//
//		SPI_FLASH_Write_Enable();				   //SET WEL 
//		cs();							 //¨º1?¨¹?¡Â?t	 
//		SPIx_ReadWriteByte(SPI0, GD25Q_PageProgram);		//¡¤¡é?¨ªD¡ä¨°3?¨¹¨¢?	
//		SPIx_ReadWriteByte(SPI0, (uint8_t)((sectorNo*GD25Q128_Sector_SIZE)>>16)); //¡¤¡é?¨ª24bit¦Ì??¡¤	
//		SPIx_ReadWriteByte(SPI0, (uint8_t)((sectorNo*GD25Q128_Sector_SIZE)>>8));	 
//		SPIx_ReadWriteByte(SPI0, (uint8_t)(sectorNo*GD25Q128_Sector_SIZE));   
//		for(i=0;i<GD25Q128_Sector_SIZE;i++) SPIx_ReadWriteByte(SPI0, readbuf[i]);//?-?¡¤D¡ä¨ºy	
//		  cd(); 						  //¨¨??????? 
//		  SPI_Flash_Wait_Busy();	
//
//		current_addr += current_size;
//		pBuffer += current_size;
//		current_size = ((current_addr + GD25Q128_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : GD25Q128_PAGE_SIZE;
//	} while (current_addr < end_addr);
//}





void GD25_Sleep(void)
{
  
	cs();                           //¨º1?¨¹?¡Â?t   
    SPIx_ReadWriteByte(SPI0, GD25Q_PowerDown);         //¡¤¡é?¨ª?¨¢¨¨??¨¹¨¢?   
	cd();  

}


void GD25_Wakeup(void)
{
	cs();                           //¨º1?¨¹?¡Â?t   
    SPIx_ReadWriteByte(SPI0, GD25Q_ReleasePowerDown);         //¡¤¡é?¨ª?¨¢¨¨??¨¹¨¢?   
	cd(); 

}



//void WritePktFlash(uint8_t *pbuf, FlashDataAddrTyp *flashaddr, uint16_t length)
void WritePktFlash(uint8_t *pbuf, uint32_t flashaddr, uint16_t length)

{
	uint32_t addr;
//lysq need to improve
//	GD25QXX_Write(pbuf, flashaddr->LineStartAddr+length, length);
//	GD25QXX_Write(pbuf, flashaddr, length);
//	flashaddr->LineStartAddr += length;
//	flashaddr->pktcnt++;

//	if(flashaddr->LineStartAddr > Flash_Data_EndAddr)
//	{
//		addr = Flash_Data_StartAddr + (addr - Flash_Data_EndAddr) - 1;
//	}
}




