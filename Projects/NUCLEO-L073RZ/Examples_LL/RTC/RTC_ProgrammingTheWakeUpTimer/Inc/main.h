/**
  ******************************************************************************
  * @file    Examples_LL/RTC/RTC_ProgrammingTheWakeUpTimer/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_system.h"
#include "stm32l0xx_ll_utils.h"
#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_exti.h"
#include "stm32l0xx_ll_rtc.h"
#include "stm32l0xx_ll_usart.h"
#include "stm32l0xx_ll_pwr.h"
#include "stm32l0xx_ll_cortex.h"
#include "string.h"
#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Define used to enable time-out management*/
#define USE_TIMEOUT       0

#define RTC_ERROR_NONE    0
#define RTC_ERROR_TIMEOUT 1

/**
  * @brief LED2 
  */

#define LED2_PIN                           LL_GPIO_PIN_5
#define LED2_GPIO_PORT                     GPIOA
#define LED2_GPIO_CLK_ENABLE()             LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA)

/**
  * @brief Toggle periods for various blinking modes
  */

#define LED_BLINK_FAST  200
#define LED_BLINK_SLOW 500
#define LED_BLINK_ERROR 1000


/**
  * @brief Key push-button
  */
#define USER_BUTTON_PIN                         LL_GPIO_PIN_13
#define USER_BUTTON_GPIO_PORT                   GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()           LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC)   
#define USER_BUTTON_EXTI_LINE                   LL_EXTI_LINE_13
#define USER_BUTTON_EXTI_IRQn                   EXTI4_15_IRQn
#define USER_BUTTON_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(USER_BUTTON_EXTI_LINE)   
#define USER_BUTTON_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(USER_BUTTON_EXTI_LINE)   
#define USER_BUTTON_SYSCFG_SET_EXTI()           do {                                                                     \
                                                  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                  \
                                                  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);  \
                                                } while(0)
#define USER_BUTTON_IRQHANDLER                  EXTI4_15_IRQHandler

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
/* IRQ Handler treatment.*/
void UserButton_Callback(void); 
void USART_CharReception_Callback(void);
void USART_CharTransmitComplete_Callback(void);
void RTC_Wakup_Treatement(void);

#endif /* __MAIN_H */
