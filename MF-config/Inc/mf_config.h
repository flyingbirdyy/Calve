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


/* USER CODE BEGIN Header */ 

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MF_CONFIG_H
#define __MF_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"


/* Exported functions prototypes ---------------------------------------------*/
void MF_Clock_Init(void);
void MF_Config_Init(void);
void Error_Handler(void);
void MF_CMU_XTLF_Init(void);
void MF_CMU_FOUT0_Init(void);
void MF_GPIO_Init(void);
void MF_ADC_Common_Init(void);
void MF_ADC_Sampling_Init(void);
void MF_EXTI_Common_Init(void);
void MF_EXTI_Line1_Init(void);
void MF_EXTI_Line2_Init(void);
void MF_EXTI_Line3_Init(void);
void MF_LPTIM32_TimerBase_Init(void);
void MF_LPTIM32_Interrupt_Init(void);
void MF_LPUART0_Init(void);
void MF_LPUART0_Interrupt_Init(void);
void MF_LPUART2_Init(void);
void MF_LPUART2_Interrupt_Init(void);
void MF_RTCA_Init(void);
void MF_RTCA_Interrupt_Init(void);
void MF_SPI0_Init(void);
void MF_SPI2_Init(void);
void MF_SWD_IO_Init(void);
void MF_PowerUp_Config_Init(void);


/* Private defines -----------------------------------------------------------*/

#ifndef NVIC_PRIORITYGROUP_0

#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif


#ifdef __cplusplus
}
#endif

#endif /* __MF_CONFIG_H */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
