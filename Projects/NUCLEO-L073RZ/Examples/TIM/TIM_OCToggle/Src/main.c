/**
  ******************************************************************************
  * @file    TIM/TIM_OCToggle/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to configure the Timer to generate four different 
  *          signals with four different frequencies.
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
#include "main.h"

/** @addtogroup STM32L0xx_HAL_Examples
  * @{
  */

/** @addtogroup TIM_OCToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t uhCCR1_Val = 5384;
__IO uint32_t uhCCR2_Val = 2692;
__IO uint32_t uhCCR3_Val = 1346;
__IO uint32_t uhCCR4_Val = 673;

uint32_t uhCapture = 0;

/* Timer handler declaration */
TIM_HandleTypeDef    TimHandle;

/* Timer Output Compare Configuration Structure declaration */
TIM_OC_InitTypeDef sConfig;

/* Counter Prescaler value */
uint32_t uwPrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32L0xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 2 MHz */
  SystemClock_Config();

  /* Configure LED2 */
  BSP_LED_Init(LED2);


   /*##-1- Configure the TIM peripheral #######################################*/
  /* ---------------------------------------------------------------------------
  TIM2 Configuration: Output Compare Toggle Mode:

  To get TIM2 counter clock at 2.1 MHz, the prescaler is computed as follows:
  Prescaler = (TIM2CLK / TIM2 counter clock) - 1
  Prescaler = (SystemCoreClock /2100000) - 1

  CC1 update rate = TIM2 counter clock / uhCCR1_Val
                  = 2.1 MHz/5384 = 390 Hz
  ==> So the TIM2 Channel 1 generates a periodic signal with a frequency equal
      to 195 Hz.

  CC2 update rate = TIM2 counter clock / uhCCR2_Val
                  = 2.1 MHz/2692 = 780 Hz
  ==> So the TIM2 Channel 2 generates a periodic signal with a frequency equal
      to 390 Hz.

  CC3 update rate = TIM2 counter clock / uhCCR3_Val
                  = 2.1 MHz/1346 = 1560 Hz
  ==> So the TIM2 Channel 3 generates a periodic signal with a frequency equal
      to 780 Hz.

  CC4 update rate = TIM2 counter clock / uhCCR4_Val
                  = 2.1 MHz/673 = 3120 Hz
  ==> So the TIM2 Channel 4 generates a periodic signal with a frequency equal
      to 1560 Hz.


  --------------------------------------------------------------------------- */



  /* Compute the prescaler value to have TIM2 counter clock equal to 2.1 MHz */
  uwPrescalerValue = 0;
  
  TimHandle.Instance = TIM2;
  
  TimHandle.Init.Period        = 65535;
  TimHandle.Init.Prescaler     = uwPrescalerValue;
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;
  if(HAL_TIM_OC_Init(&TimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /*##-2- Configure the Output Compare channels ##############################*/ 
  /* Common configuration for all channels */
  sConfig.OCMode     = TIM_OCMODE_TOGGLE;
  sConfig.OCPolarity = TIM_OCPOLARITY_LOW;

  /* Output Compare Toggle Mode configuration: Channel1 */
  sConfig.Pulse = uhCCR1_Val;  
  if(HAL_TIM_OC_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }
  
  /* Output Compare Toggle Mode configuration: Channel2 */
  sConfig.Pulse = uhCCR2_Val;
  if(HAL_TIM_OC_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }
  
  /* Output Compare Toggle Mode configuration: Channel3 */
  sConfig.Pulse = uhCCR3_Val;
  if(HAL_TIM_OC_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }
  
  /* Output Compare Toggle Mode configuration: Channel4 */
  sConfig.Pulse = uhCCR4_Val;
  if(HAL_TIM_OC_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_4) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }

  /*##-3- Start signals generation #######################################*/ 
  /* Start channel 1 in Output compare mode */
  if(HAL_TIM_OC_Start_IT(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  /* Start channel 2 in Output compare mode */
  if(HAL_TIM_OC_Start_IT(&TimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  /* Start channel 3 in Output compare mode */
  if(HAL_TIM_OC_Start_IT(&TimHandle, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  /* Start channel 4 in Output compare mode */
  if(HAL_TIM_OC_Start_IT(&TimHandle, TIM_CHANNEL_4) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }

  while (1)
  {}
}

/**
  * @brief  Output Compare callback in non blocking mode 
  * @param  htim : TIM OC handle
  * @retval None
  */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* TIM2_CH1 toggling with frequency = 195 Hz */
  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
  {
    uhCapture = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
    /* Set the Capture Compare Register value */
    __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_1, (uhCapture + uhCCR1_Val));
  }
  
  /* TIM2_CH2 toggling with frequency = 390 Hz */
  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
  {
    uhCapture = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
    /* Set the Capture Compare Register value */
    __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_2, (uhCapture + uhCCR2_Val));   
  }
  
  /* TIM2_CH3 toggling with frequency = 780 Hz */
  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
  {
    uhCapture = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
    /* Set the Capture Compare Register value */
    __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_3, (uhCapture + uhCCR3_Val));
  }
  
  /* TIM2_CH4 toggling with frequency = 1560 Hz */
  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
  {
    uhCapture = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
    /* Set the Capture Compare Register value */
    __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_4, (uhCapture + uhCCR4_Val));
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = MSI
  *            SYSCLK(Hz)                     = 2000000
  *            HCLK(Hz)                       = 2000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            Flash Latency(WS)              = 0
  *            Main regulator output voltage  = Scale3 mode
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  
  /* Enable MSI Oscillator */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.MSICalibrationValue=0x00;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
  
  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */
