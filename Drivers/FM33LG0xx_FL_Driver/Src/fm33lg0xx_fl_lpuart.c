/**
  ****************************************************************************************************
  * @file    fm33lg0xx_fl_lpuart.c
  * @author  FMSH Application Team
  * @brief   Src file of LPUART FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"

/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @addtogroup LPUART
  * @{
  */

#ifdef FL_LPUART_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup LPUART_FL_Private_Macros
  * @{
  */
#define         IS_LPUART_INSTANCE(INSTANCE)               (((INSTANCE) == LPUART0)||\
                                                            ((INSTANCE) == LPUART1)||\
                                                             ((INSTANCE) == LPUART2))

#define         IS_FL_LPUART_CLKSRC(__VALUE__)             (((__VALUE__) == FL_CMU_LPUART_CLK_SOURCE_LSCLK)||\
                                                            ((__VALUE__) == FL_CMU_LPUART_CLK_SOURCE_RCHF)||\
                                                            ((__VALUE__) == FL_CMU_LPUART_CLK_SOURCE_RCLF))

#define         IS_FL_LPUART_BAUDRATE(__VALUE__)            (((__VALUE__) == FL_LPUART_BAUDRATE_300)||\
                                                             ((__VALUE__) == FL_LPUART_BAUDRATE_600)||\
                                                             ((__VALUE__) == FL_LPUART_BAUDRATE_1200)||\
                                                             ((__VALUE__) == FL_LPUART_BAUDRATE_2400)||\
                                                             ((__VALUE__) == FL_LPUART_BAUDRATE_4800)||\
                                                             ((__VALUE__) == FL_LPUART_BAUDRATE_9600))

#define         IS_FL_LPUART_DATAWIDTH(__VALUE__)           (((__VALUE__) == FL_LPUART_DATA_WIDTH_6B)||\
                                                             ((__VALUE__) == FL_LPUART_DATA_WIDTH_7B)||\
                                                             ((__VALUE__) == FL_LPUART_DATA_WIDTH_8B)||\
                                                             ((__VALUE__) == FL_LPUART_DATA_WIDTH_9B))

#define         IS_FL_LPUART_STOPBITS(__VALUE__)            (((__VALUE__) == FL_LPUART_STOP_BIT_WIDTH_1B)||\
                                                             ((__VALUE__) == FL_LPUART_STOP_BIT_WIDTH_2B))

#define         IS_FL_LPUART_PARITY(__VALUE__)              (((__VALUE__) == FL_LPUART_PARITY_NONE)||\
                                                             ((__VALUE__) == FL_LPUART_PARITY_EVEN)||\
                                                             ((__VALUE__) == FL_LPUART_PARITY_ODD))

#define         IS_FL_LPUART_DIRECTION(__VALUE__)           (((__VALUE__) == FL_LPUART_DIRECTION_NONE)||\
                                                             ((__VALUE__) == FL_LPUART_DIRECTION_RX)||\
                                                             ((__VALUE__) == FL_LPUART_DIRECTION_TX)||\
                                                             ((__VALUE__) == FL_LPUART_DIRECTION_TX_RX))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPUART_FL_EF_Init
  * @{
  */

/**
  * @brief    复位LPUART 外设
  * @param    外设入口地址
  * @retval    返回错误状态，可能值：
  *           -FL_PASS 外设寄存器值恢复复位�?
  *           -FL_FAIL 未成功执�?
  */
FL_ErrorStatus FL_LPUART_DeInit(LPUART_Type *LPUARTx)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口参数合法性断言 */
    assert_param(IS_LPUART_INSTANCE(LPUARTx));
    /* 外设复位使能 */
    FL_RMU_EnablePeripheralReset(RMU);
    if(LPUARTx == LPUART0)
    {
        /*复位LPUART*/
        FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPUART0);
        FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPUART0);
        /* 外设总线时钟关闭 */
        FL_CMU_IsEnabledGroup3BusClock(FL_CMU_GROUP3_BUSCLK_LPUART0);
        /* 外设工作时钟关闭 */
        FL_CMU_DisableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPUART0);
    }
    else
        if(LPUARTx == LPUART1)
        {
            /*复位LPUART*/
            FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPUART1);
            FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPUART1);
            /* 外设总线时钟关闭 */
            FL_CMU_IsEnabledGroup3BusClock(FL_CMU_GROUP3_BUSCLK_LPUART1);
            /* 外设工作时钟关闭 */
            FL_CMU_DisableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPUART1);
        }
        else
            if(LPUARTx == LPUART2)
            {
                /*复位LPUART*/
                FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPUART2);
                FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPUART2);
                /* 外设总线时钟关闭 */
                FL_CMU_IsEnabledGroup3BusClock(FL_CMU_GROUP3_BUSCLK_LPUART2);
                /* 外设工作时钟关闭 */
                FL_CMU_DisableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPUART2);
            }
            else
            {
                status = FL_FAIL;
            }
    /* 锁定外设复位功能 */
    FL_RMU_DisablePeripheralReset(RMU);
    return (status);
}

/**
  * @brief    根据需要功能配置LPUART寄存�?
  *
  * @note     波特率调制寄存器中的MCTL值，默认为工作时钟为32768Hz的频率下的调制值，用户如果外设工作时钟不是此前
  *          提则可能需要手动调整这个寄存器的值，以达到更好的通信效果�?
  * @param    LPUARTx  外设入口地址
  * @param     initStruct 指向一�?@ref FL_LPUART_InitTypeDef类型的结构体，它包含指定LPUART外设的配置信�?
  *
  * @retval    ErrorStatus枚举�?
  *            -FL_FAIL 配置过程发生错误
  *            -FL_PASS LPUART配置成功
  */
FL_ErrorStatus FL_LPUART_Init(LPUART_Type *LPUARTx, FL_LPUART_InitTypeDef *initStruct)
{
    FL_ErrorStatus status = FL_FAIL;
    uint16_t  MCTLVel;
    /* 参数合法性检�?*/
    assert_param(IS_LPUART_INSTANCE(LPUARTx));
    assert_param(IS_FL_LPUART_CLKSRC(initStruct->clockSrc));
    assert_param(IS_FL_LPUART_BAUDRATE(initStruct->baudRate));
    assert_param(IS_FL_LPUART_DATAWIDTH(initStruct->dataWidth));
    assert_param(IS_FL_LPUART_STOPBITS(initStruct->stopBits));
    assert_param(IS_FL_LPUART_PARITY(initStruct->parity));
    assert_param(IS_FL_LPUART_DIRECTION(initStruct->transferDirection));
    if(LPUARTx == LPUART0)
    {
        /*总线时钟使能*/
        FL_CMU_EnableGroup3BusClock(FL_CMU_GROUP3_BUSCLK_LPUART0);
        /*操作时钟使能*/
        FL_CMU_EnableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPUART0);
        /*时钟源选择*/
        FL_CMU_SetLPUART0ClockSource(initStruct->clockSrc << CMU_OPCCR1_LPUART0CKS_Pos);
    }
    else
        if(LPUARTx == LPUART1)
        {
            /*总线时钟使能*/
            FL_CMU_EnableGroup3BusClock(FL_CMU_GROUP3_BUSCLK_LPUART1);
            /*操作时钟使能*/
            FL_CMU_EnableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPUART1);
            /*时钟源选择*/
            FL_CMU_SetLPUART1ClockSource(initStruct->clockSrc << CMU_OPCCR1_LPUART1CKS_Pos);
        }
        else
        {
            /*总线时钟使能*/
            FL_CMU_EnableGroup3BusClock(FL_CMU_GROUP3_BUSCLK_LPUART2);
            /*操作时钟使能*/
            FL_CMU_EnableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPUART2);
            /*时钟源选择*/
            FL_CMU_SetLPUART2ClockSource(initStruct->clockSrc << CMU_OPCCR1_LPUART2CKS_Pos);
        }
    if(initStruct->clockSrc == FL_CMU_LPUART_CLK_SOURCE_RCLF)//RCLF时钟
    {
        FL_CMU_RCLF_SetPrescaler(FL_CMU_RCLF_PSC_DIV16);
        FL_CMU_RCLF_Enable();
        FL_LPUART_DisableBaudRateModulation(LPUARTx);
    }
    else
    {
        FL_LPUART_EnableBaudRateModulation(LPUARTx);
    }
    /*发送接收配�?*/
    if(initStruct->transferDirection & FL_LPUART_DIRECTION_TX)
    {
        do
        {
            FL_LPUART_EnableTX(LPUARTx);
        } while(FL_LPUART_IsEnabledTX(LPUARTx) != FL_SET);
    }
    if(initStruct->transferDirection & FL_LPUART_DIRECTION_RX)
    {
        do
        {
            FL_LPUART_EnableRX(LPUARTx);
        } while(FL_LPUART_IsEnabledRX(LPUARTx) != FL_SET);
    }
    /*配置波特�*/
    FL_LPUART_SetBaudRate(LPUARTx, initStruct->baudRate);
    /*配置停止�*/
    FL_LPUART_SetStopBitsWidth(LPUARTx, initStruct->stopBits);
    /*配置数据位宽*/
    FL_LPUART_SetDataWidth(LPUARTx, initStruct->dataWidth);
    /*配置波特�*/
    FL_LPUART_SetParity(LPUARTx, initStruct->parity);
    /*根据波特率配置MCTL�*/
    switch(initStruct->baudRate)
    {
        case FL_LPUART_BAUDRATE_9600:
            MCTLVel = 0x0552;
            break;
        case FL_LPUART_BAUDRATE_4800:
            MCTLVel = 0x1EFB;
            break;
        case FL_LPUART_BAUDRATE_2400:
            MCTLVel = 0x16DB;
            break;
        case FL_LPUART_BAUDRATE_1200:
            MCTLVel = 0x0492;
            break;
        case FL_LPUART_BAUDRATE_600:
            MCTLVel = 0x16D6;
            break;
        case FL_LPUART_BAUDRATE_300:
            MCTLVel = 0x0842;
            break;
        default:
            MCTLVel = 0x0552;
            break;
    }
    FL_LPUART_WriteBitModulation(LPUARTx, MCTLVel);
    status = FL_PASS;
    return status;
}

/**
  * @brief    initStruct 为默认配�?
  * @param     initStruct 指向需要将值设置为默认配置的结构体 @ref FL_LPUART_InitTypeDef structure
  *         结构�?
  * @retval    None
  */

void FL_LPUART_StructInit(FL_LPUART_InitTypeDef *initStruct)
{
    initStruct->baudRate            = FL_LPUART_BAUDRATE_9600;
    initStruct->dataWidth           = FL_LPUART_DATA_WIDTH_8B;
    initStruct->stopBits            = FL_LPUART_STOP_BIT_WIDTH_1B;
    initStruct->parity              = FL_LPUART_PARITY_NONE ;
    initStruct->transferDirection   = FL_LPUART_DIRECTION_TX_RX;
    initStruct->clockSrc            = FL_CMU_LPUART_CLK_SOURCE_LSCLK;
}

/**
  * @}
  */

#endif /* FL_LPUART_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/

