/**
  ******************************************************************************
  * @file    TIM/TIM_DMABurst/Src/stm32l0xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  *         
  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]


  @endverbatim
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief TIM MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - DMA configuration for transmission request by peripheral
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  static DMA_HandleTypeDef  hdma_tim;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIM2 clock enable */
  __HAL_RCC_TIM2_CLK_ENABLE();
    
  /* Enable GPIO TIM2_Channel3 (PORTB) Clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* Enable DMA1 clock */
  __HAL_RCC_DMA1_CLK_ENABLE();
  
  /*##-2- Configure peripheral GPIO ##########################################*/
  /* Configure TIM2_Channel3 in output, push-pull & alternate function mode */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  /*##-3- Configure the DMA stream ###########################################*/
  /* Set the parameters to be configured */
  hdma_tim.Init.Request = DMA_REQUEST_8;
  hdma_tim.Instance = DMA1_Channel2;  
  hdma_tim.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_tim.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_tim.Init.MemInc = DMA_MINC_ENABLE;
  hdma_tim.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_tim.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_tim.Init.Mode = DMA_NORMAL;
  hdma_tim.Init.Priority = DMA_PRIORITY_HIGH;


  /* Link hdma_tim to hdma[TIM_DMA_ID_CC3] (channel3) */
  __HAL_LINKDMA(htim, hdma[TIM_DMA_ID_UPDATE], hdma_tim);
  
  /* Initialize TIMx DMA handle */
  HAL_DMA_Init(htim->hdma[TIM_DMA_ID_UPDATE]);
  
  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt */
   HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
}

/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
  /* NOTE : This function is eventually modified by the user */

}

/**
  * @brief  DeInitializes the Global MSP.
  * @param  None  
  * @retval None
  */
void HAL_MspDeInit(void)
{
  /* NOTE : This function is eventually modified by the user */

}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
