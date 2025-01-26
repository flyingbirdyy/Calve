/**
******************************************************************************
* @file           : mf_config.c
* @brief          : MCU FUNCTION CONFIG               
******************************************************************************
* @attention
*
* Copyright (c) [2021] [Fudan Microelectronics]
* THIS SOFTWARE is licensed under Mulan PSL v2.
* can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
* See the Mulan PSL v2 for more details.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "mf_config.h"
#include "control.h"
/* Private function prototypes -----------------------------------------------*/

 
/**
  * @brief  GPIO Initialization function
  * @param  void
  * @retval None
  */
void MF_GPIO_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    /* PA1 OUTPUT (Ref_Vol_Out) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_1;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* PB2 OUTPUT (M0) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_2;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB3 OUTPUT (M1) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_3;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//    /* PB6 OUTPUT (AUX) */ 
//    GPIO_InitStruct.pin = FL_GPIO_PIN_6;
//    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
//    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
//    GPIO_InitStruct.pull = FL_DISABLE;
//    GPIO_InitStruct.remapPin = FL_DISABLE;
//    GPIO_InitStruct.analogSwitch = FL_DISABLE;
//    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);







    /* PB8 OUTPUT (FLASH_CS) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PC0 OUTPUT (LED) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_0;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);




    /* PC7 OUTPUT (IMU_CS) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_7;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);    
		
	FL_GPIO_SetOutputPin(GPIOC, FL_GPIO_PIN_7);
		
}
 
/**
  * @brief  CMU_XTLF Initialization function
  * @param  void
  * @retval None
  */
void MF_CMU_XTLF_Init(void)
{
    FL_VAO_XTLF_InitTypeDef    XTLF_InitStruct;

    XTLF_InitStruct.driveMode = FL_VAO_XTLF_DRIVE_LEVEL_3;
    XTLF_InitStruct.workingCurrentMode = FL_VAO_XTLF_WORK_CURRENT_450NA;

    FL_VAO_XTLF_Init(VAO, &XTLF_InitStruct);    
}
 
/**
  * @brief  CMU_FOUT0 Initialization function
  * @param  void
  * @retval None
  */
void MF_IWDT_Init(void)
{
    FL_IWDT_InitTypeDef    IWDT_InitStruct;

    IWDT_InitStruct.iwdtWindows = 0;
    IWDT_InitStruct.overflowPeriod = FL_IWDT_PERIOD_8000MS;

    FL_IWDT_Init(IWDT, &IWDT_InitStruct);    
}
 
/**
  * @brief  PMU Initialization function
  * @param  void
  * @retval None
  */
void MF_PMU_Init(void)
{
    FL_PMU_SleepInitTypeDef    PMU_InitStruct;

    PMU_InitStruct.powerMode = FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP;
    PMU_InitStruct.deepSleep = FL_PMU_SLEEP_MODE_DEEP;
    PMU_InitStruct.LDOLowPowerMode = FL_PMU_LDO_LPM_ENABLE;
//    PMU_InitStruct.deepSleep = FL_PMU_SLEEP_MODE_NORMAL;
//    PMU_InitStruct.LDOLowPowerMode = FL_PMU_LDO_LPM_DISABLE;

    PMU_InitStruct.wakeupFrequency = FL_PMU_RCHF_WAKEUP_FREQ_16MHZ;
    PMU_InitStruct.wakeupDelay = FL_PMU_WAKEUP_DELAY_0US;
    PMU_InitStruct.coreVoltageScaling = FL_ENABLE;

    FL_PMU_Sleep_Init(PMU, &PMU_InitStruct);    
}
 
/**
  * @brief  ADC_Common Initialization function
  * @param  void
  * @retval None
  */
void MF_ADC_Common_Init(void)
{
    FL_ADC_CommonInitTypeDef    Common_InitStruct;

    Common_InitStruct.clockSource = FL_ADC_CLK_SOURCE_APBCLK;
    Common_InitStruct.clockPrescaler = FL_ADC_CLK_PSC_DIV1;
    Common_InitStruct.referenceSource = FL_ADC_REF_SOURCE_VDDA;
    Common_InitStruct.bitWidth = FL_ADC_BIT_WIDTH_12B;

    FL_ADC_CommonInit(&Common_InitStruct);    
}
 
/**
  * @brief  ADC_Sampling Initialization function
  * @param  void
  * @retval None
  */
void MF_ADC_Sampling_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_ADC_InitTypeDef    Sampling_InitStruct;

    /* PA0 ADC_IN5 (Ref_Vol) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_0;
    GPIO_InitStruct.mode = FL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    Sampling_InitStruct.conversionMode = FL_ADC_CONV_MODE_SINGLE;
    Sampling_InitStruct.autoMode = FL_ADC_SINGLE_CONV_MODE_AUTO;
    Sampling_InitStruct.waitMode = FL_ENABLE;
    Sampling_InitStruct.overrunMode = FL_ENABLE;
    Sampling_InitStruct.scanDirection = FL_ADC_SEQ_SCAN_DIR_FORWARD;
    Sampling_InitStruct.externalTrigConv = FL_ADC_TRIGGER_EDGE_NONE;
    Sampling_InitStruct.triggerSource = FL_DISABLE;
    Sampling_InitStruct.fastChannelTime = FL_ADC_FAST_CH_SAMPLING_TIME_2_ADCCLK;
    Sampling_InitStruct.lowChannelTime = FL_ADC_SLOW_CH_SAMPLING_TIME_512_ADCCLK;
    Sampling_InitStruct.oversamplingMode = FL_ENABLE;
    Sampling_InitStruct.overSampingMultiplier = FL_ADC_OVERSAMPLING_MUL_16X;
    Sampling_InitStruct.oversamplingShift = FL_ADC_OVERSAMPLING_SHIFT_4B;

    FL_ADC_Init(ADC, &Sampling_InitStruct);

    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_EXTERNAL_CH5);    
}
 
/**
  * @brief  EXTI_Common Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Common_Init(void)
{
    FL_EXTI_CommonInitTypeDef    Common_InitStruct;

    Common_InitStruct.clockSource = FL_CMU_EXTI_CLK_SOURCE_HCLK;

    FL_EXTI_CommonInit(&Common_InitStruct);    
}
 
/**
  * @brief  EXTI_Line1 Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Line1_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_EXTI_InitTypeDef    EXTI_InitStruct;

    /* PA4 EXTI1_Select0 (IMU_INT1) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_4;
    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    EXTI_InitStruct.filter = FL_DISABLE;
    EXTI_InitStruct.input = FL_GPIO_EXTI_INPUT_GROUP0;
    EXTI_InitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_RISING;

    FL_EXTI_Init(FL_GPIO_EXTI_LINE_1, &EXTI_InitStruct);    
}
 
/**
  * @brief  EXTI_Line2 Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Line2_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_EXTI_InitTypeDef    EXTI_InitStruct;

    /* PA8 EXTI2_Select0 (IMU_INT2) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    EXTI_InitStruct.filter = FL_DISABLE;
    EXTI_InitStruct.input = FL_GPIO_EXTI_INPUT_GROUP0;
    EXTI_InitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_RISING;

    FL_EXTI_Init(FL_GPIO_EXTI_LINE_2, &EXTI_InitStruct);    
}
 
/**
  * @brief  EXTI_Line3 Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Line3_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_EXTI_InitTypeDef    EXTI_InitStruct;

    /* PA15 EXTI3_Select3 (Key_Power) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_15;
    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_ENABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    EXTI_InitStruct.filter = FL_DISABLE;
    EXTI_InitStruct.input = FL_GPIO_EXTI_INPUT_GROUP3;
    EXTI_InitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_BOTH;

    FL_EXTI_Init(FL_GPIO_EXTI_LINE_3, &EXTI_InitStruct);    
}



/**
  * @brief  EXTI_Line5 Initialization function
  * @param  void
  * @retval None
  */
void MF_EXTI_Line5_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_EXTI_InitTypeDef    EXTI_InitStruct;

    /* PB6 EXTI5_Select2 (AUX) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_6;
    GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_ENABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    EXTI_InitStruct.filter = FL_DISABLE;
    EXTI_InitStruct.input = FL_GPIO_EXTI_INPUT_GROUP2;
    EXTI_InitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_FALLING;

    FL_EXTI_Init(FL_GPIO_EXTI_LINE_5, &EXTI_InitStruct);    
}




/**
  * @brief  LPTIM32_TimerBase Initialization function
  * @param  void
  * @retval None
  */
void MF_LPTIM32_TimerBase_Init(void)
{
    FL_LPTIM32_InitTypeDef    TimerBase_InitStruct;

    TimerBase_InitStruct.clockSource = FL_CMU_LPTIM32_CLK_SOURCE_APBCLK;
    TimerBase_InitStruct.prescalerClockSource = FL_LPTIM32_CLK_SOURCE_INTERNAL;
    TimerBase_InitStruct.prescaler = FL_LPTIM32_PSC_DIV16;
    TimerBase_InitStruct.autoReload = 99999;
    TimerBase_InitStruct.mode = FL_LPTIM32_OPERATION_MODE_NORMAL;
    TimerBase_InitStruct.onePulseMode = FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS;
    TimerBase_InitStruct.triggerEdge = FL_LPTIM32_ETR_TRIGGER_EDGE_RISING;
    TimerBase_InitStruct.countEdge = FL_LPTIM32_ETR_COUNT_EDGE_RISING;

    FL_LPTIM32_Init(LPTIM32, &TimerBase_InitStruct);    
}
 
/**
  * @brief  LPTIM32 Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_LPTIM32_Interrupt_Init(void)
{
    FL_LPTIM32_ClearFlag_Update(LPTIM32);
    FL_LPTIM32_EnableIT_Update(LPTIM32);  
}
 
/**
  * @brief  LPUART0 Initialization function
  * @param  void
  * @retval None
  */
void MF_LPUART0_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_LPUART_InitTypeDef    LPUART0_InitStruct;

    /* PA2 LPUART0_RX */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_2;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_ENABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* PA3 LPUART0_TX */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_3;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_ENABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LPUART0_InitStruct.baudRate = FL_LPUART_BAUDRATE_9600;
    LPUART0_InitStruct.dataWidth = FL_LPUART_DATA_WIDTH_8B;
    LPUART0_InitStruct.stopBits = FL_LPUART_STOP_BIT_WIDTH_1B;
    LPUART0_InitStruct.parity = FL_LPUART_PARITY_NONE;
    LPUART0_InitStruct.transferDirection = FL_LPUART_DIRECTION_NONE;
    LPUART0_InitStruct.clockSrc = FL_CMU_LPUART_CLK_SOURCE_LSCLK;

    FL_LPUART_Init(LPUART0, &LPUART0_InitStruct);    
}
 
/**
  * @brief  LPUART0 Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_LPUART0_Interrupt_Init(void)
{
    FL_LPUART_ClearFlag_RXBuffFull(LPUART0);
    FL_LPUART_EnableIT_RXBuffFull(LPUART0);  
}
 
/**
  * @brief  LPUART2 Initialization function
  * @param  void
  * @retval None
  */
void MF_LPUART2_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_LPUART_InitTypeDef    LPUART2_InitStruct;

    /* PB4 LPUART2_RX (TXD_L) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_4;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB5 LPUART2_TX (RXD_L) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_5;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    LPUART2_InitStruct.baudRate = FL_LPUART_BAUDRATE_9600;
    LPUART2_InitStruct.dataWidth = FL_LPUART_DATA_WIDTH_8B;
    LPUART2_InitStruct.stopBits = FL_LPUART_STOP_BIT_WIDTH_1B;
    LPUART2_InitStruct.parity = FL_LPUART_PARITY_NONE;
    LPUART2_InitStruct.transferDirection = FL_LPUART_DIRECTION_NONE;
    LPUART2_InitStruct.clockSrc = FL_CMU_LPUART_CLK_SOURCE_LSCLK;

    FL_LPUART_Init(LPUART2, &LPUART2_InitStruct);    
}
 
/**
  * @brief  LPUART2 Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_LPUART2_Interrupt_Init(void)
{
    FL_LPUART_ClearFlag_RXBuffFull(LPUART2);
    FL_LPUART_EnableIT_RXBuffFull(LPUART2);  
}
 
/**
  * @brief  RTCA Initialization function
  * @param  void
  * @retval None
  */
void MF_RTCA_Init(void)
{
    FL_RTCA_InitTypeDef    RTCA_InitStruct;

    RTCA_InitStruct.year = 0x21;
    RTCA_InitStruct.month = 0x1;
    RTCA_InitStruct.day = 0x1;
    RTCA_InitStruct.week = 0x5;
    RTCA_InitStruct.hour = 0x0;
    RTCA_InitStruct.minute = 0x0;
    RTCA_InitStruct.second = 0x0;

    FL_RTCA_Init(RTCA, &RTCA_InitStruct);    
}
 
/**
  * @brief  RTCA Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_RTCA_Interrupt_Init(void)
{
    FL_RTCA_ClearFlag_Hour(RTCA);
    FL_RTCA_EnableIT_Hour(RTCA);  

//	FL_RTCA_ClearFlag_Second(RTCA);
//    FL_RTCA_EnableIT_Second(RTCA);  
}
 
/**
  * @brief  SPI0 Initialization function
  * @param  void
  * @retval None
  */
void MF_SPI0_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_SPI_InitTypeDef    SPI0_InitStruct;

    /* PB9 SPI0_SCK (FLASH_CLK) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_9;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB10 SPI0_MISO (FLASH_DO) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_10;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_ENABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB11 SPI0_MOSI (FLASH_DI) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    SPI0_InitStruct.softControl = FL_DISABLE;
    SPI0_InitStruct.mode = FL_SPI_WORK_MODE_MASTER;
    SPI0_InitStruct.baudRate = FL_SPI_BAUDRATE_DIV2;
    SPI0_InitStruct.bitOrder = FL_SPI_BIT_ORDER_MSB_FIRST;
    SPI0_InitStruct.dataWidth = FL_SPI_DATA_WIDTH_8B;
    SPI0_InitStruct.clockPhase = FL_SPI_PHASE_EDGE1;
    SPI0_InitStruct.transferMode = FL_SPI_TRANSFER_MODE_FULL_DUPLEX;
    SPI0_InitStruct.clockPolarity = FL_SPI_POLARITY_NORMAL;

    FL_SPI_Init(SPI0, &SPI0_InitStruct);    
}
 
/**
  * @brief  SPI2 Initialization function
  * @param  void
  * @retval None
  */
void MF_SPI2_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_SPI_InitTypeDef    SPI2_InitStruct;

    /* PC8 SPI2_SCK (IMU_CLK) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* PC9 SPI2_MISO (IMU_SDO) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_9;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* PC10 SPI2_MOSI (IMU_SDA) */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_10;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    SPI2_InitStruct.softControl = FL_DISABLE;
    SPI2_InitStruct.mode = FL_SPI_WORK_MODE_MASTER;
    SPI2_InitStruct.baudRate = FL_SPI_BAUDRATE_DIV4;
    SPI2_InitStruct.bitOrder = FL_SPI_BIT_ORDER_MSB_FIRST;
    SPI2_InitStruct.dataWidth = FL_SPI_DATA_WIDTH_8B;
    SPI2_InitStruct.clockPhase = FL_SPI_PHASE_EDGE2;
    SPI2_InitStruct.transferMode = FL_SPI_TRANSFER_MODE_FULL_DUPLEX;
    SPI2_InitStruct.clockPolarity = FL_SPI_POLARITY_INVERT;

    FL_SPI_Init(SPI2, &SPI2_InitStruct);    
}
 
/**
  * @brief  SWD_IO Initialization function
  * @param  void
  * @retval None
  */
void MF_SWD_IO_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    /* PD7 SWD_SWCLK */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_7;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* PD8 SWD_SWDIO */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    
}
 
/**
  * @brief  NVIC Initialization function
  * @param  void
  * @retval None
  */
void MF_NVIC_Init(void)
{
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    InterruptConfigStruct.preemptPriority = 0x00;
    FL_NVIC_Init(&InterruptConfigStruct, RTCx_IRQn);
	
	InterruptConfigStruct.preemptPriority = 0x02;
    FL_NVIC_Init(&InterruptConfigStruct, LPUARTx_IRQn);

    InterruptConfigStruct.preemptPriority = 0x01;
    FL_NVIC_Init(&InterruptConfigStruct, LPTIMx_IRQn);

    InterruptConfigStruct.preemptPriority = 0x02;
    FL_NVIC_Init(&InterruptConfigStruct, GPIO_IRQn);    
}

/**
  * @brief  HFDET_IRQHandler
  * @param  void
  * @retval None
  */
void HFDET_IRQHandler(void)
{
    //停振�?测中断处�?
    if((FL_CMU_IsEnabledIT_XTHFFail() == 0x01UL)
        && (FL_CMU_IsActiveFlag_XTHFFail() == 0x01UL))
    {
        FL_CMU_ClearFlag_XTHFFail();
         /*应用处理逻辑*/
    }
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /* Initial CDIF */
    FL_CDIF_EnableCPUToVAO(CDIF);
    FL_CDIF_EnableVAOToCPU(CDIF);

    /* Initial RTCA Adjust Value */
    FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_RTCA);
    FL_RTCA_WriteAdjustValue(RTCA, 0);
    FL_CMU_DisableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_RTCA);

    /* Initial RTCB Adjust Value */
    FL_RTCB_WriteAdjustValue(RTCB, 0);

    /* Initial XTLF */
    MF_CMU_XTLF_Init();
    FL_VAO_XTLF_Enable(VAO);
    FL_DelayMs(1000);

    /* Initial Low Speed Clock */
    FL_CMU_SetLSCLKClockSource(FL_CMU_LSCLK_CLK_SOURCE_XTLF);
    FL_CMU_EnableLSCLKAutoSwitch();

    /* Initial RCHF */
    FL_CMU_RCHF_WriteTrimValue(RCHF16M_TRIM);
    FL_CMU_RCHF_SetFrequency(FL_CMU_RCHF_FREQUENCY_16MHZ);
    FL_CMU_RCHF_Enable();

    /* Initial System Clock */
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);    /* 设置FLASH读等待为 0 个周�? */
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_RCHF);    /* 设置系统主时钟为 RCHF */
    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);

    /* Initial CDIF Clock Prescaler */
    FL_CDIF_SetPrescaler(CDIF, FL_CDIF_PSC_DIV2);

    SystemCoreClockUpdate();

    /* Initial Clock Output */
 //   MF_CMU_FOUT0_Init();

 
}





void MF_Config_Init(void)
{
    /* Initial IWDT */
//    MF_IWDT_Init();  //debug lysq 20240602

    /* Initial GPIO */
    MF_GPIO_Init();

    /* Initial PMU */
    MF_PMU_Init();

    /* Initial ADC */
    MF_ADC_Common_Init();
    MF_ADC_Sampling_Init();

    /* Initial EXTI */
    MF_EXTI_Common_Init();
    MF_EXTI_Line1_Init();
    MF_EXTI_Line2_Init();
    MF_EXTI_Line3_Init();

    /* Initial LPTIM32 */
    MF_LPTIM32_TimerBase_Init();
    MF_LPTIM32_Interrupt_Init();

    /* Initial LPUART0 */
    MF_LPUART0_Init();
    MF_LPUART0_Interrupt_Init();

    /* Initial LPUART2 */
    MF_LPUART2_Init();
    MF_LPUART2_Interrupt_Init();

    /* Initial RTCA */
    MF_RTCA_Init();
    MF_RTCA_Interrupt_Init();
//	FL_RTCA_Enable(RTCA);

    /* Initial SPI0 */
    MF_SPI0_Init();

    /* Initial SPI2 */
    MF_SPI2_Init();

    /* Initial SWD */
    MF_SWD_IO_Init();

	MF_NVIC_Init();

//	MF_CMU_FOUT0_Init();
}





void MF_PowerUp_Config_Init(void)
{
    /* Initial IWDT */
//    MF_IWDT_Init();

    /* Initial GPIO */
    MF_GPIO_Init();


    /* Initial PMU */
    MF_PMU_Init();

    /* Initial EXTI */
    MF_EXTI_Common_Init();
    MF_EXTI_Line3_Init();
	
    /* Initial LPTIM32 */
    MF_LPTIM32_TimerBase_Init();
    MF_LPTIM32_Interrupt_Init();
	
    /* Initial LPUART0 */
    MF_LPUART0_Init();
    MF_LPUART0_Interrupt_Init();

    /* Initial LPUART2 */
    MF_LPUART2_Init();
    MF_LPUART2_Interrupt_Init();


    /* Initial RTCA */
//    MF_RTCA_Init();
//    MF_RTCA_Interrupt_Init();
//	FL_RTCA_Enable(RTCA);

    /* Initial SPI0 */
    MF_SPI0_Init();

    /* Initial SPI2 */
    MF_SPI2_Init();

    /* Initial SWD */
    MF_SWD_IO_Init();

	MF_NVIC_Init();

//	LEDOn;
//	FL_DelayMs(2000);
//	LEDOff;

	FL_VREF_Disable(VREF); 
//	MF_CMU_FOUT0_Init();
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 

}
#endif /* USE_FULL_ASSERT */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
