/**
  @page SPI_FullDuplex_ComDMA SPI Full Duplex DMA example

  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    SPI/SPI_FullDuplex_ComDMA/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the SPI Full Duplex DMA example.
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
  @endverbatim

@par Example Description 

Data buffer transmission/reception between two boards via SPI using DMA.

   _________________________                        _________________________
  |           ______________|                      |______________           |
  |          |SPI2          |                      |          SPI2|          |
  |          |              |                      |              |          |
  |          |     CLK(PB13)|______________________|(PB13)CLK     |          |
  |          |              |                      |              |          |
  |          |    MISO(PB14)|______________________|(PB14)MISO    |          |
  |          |              |                      |              |          |
  |          |    MOSI(PB15)|______________________|(PB15)MOSI    |          |
  |          |              |                      |              |          |
  |          |______________|                      |______________|          |
  |      __                 |                      |      __                 |
  |     |__|                |                      |     |__|                |
  |     USER                |                      |     USER                |
  |                      GND|______________________|GND                      |
  |                         |                      |                         |
  |_STM32L0 ________________|                      |_STM32L0 ________________|

This example guides you through the different configuration steps by mean of HAL API 
to ensure SPI Data buffer transmission and reception with DMA.

HAL architecture allows user to easily change code to move to Polling or IT 
mode. To see others communication modes please check following examples:
SPI\SPI_FullDuplex_ComPolling
SPI\SPI_FullDuplex_ComIT

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 2 MHz.

The SPI peripheral configuration is ensured by the HAL_SPI_Init() function.
This later is calling the HAL_SPI_MspInit()function which core is implementing
the configuration of the needed SPI resources according to the used hardware (CLOCK, 
GPIO, DMA and NVIC). You may update this function to change SPI configuration.

The SPI communication is then initiated.
The HAL_SPI_TransmitReceive_DMA() function allows the reception and the 
transmission of a predefined data buffer at the same time (Full Duplex Mode). 
The user can choose between Master and Slave through "#define MASTER_BOARD"
in the "main.c" file.
If the Master board is used, the "#define MASTER_BOARD" must be uncommented.
If the Slave board is used the "#define MASTER_BOARD" must be commented.

For this example the aTxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step after the user press the User Key, SPI Master starts the 
communication by sending aTxBuffer and receiving aRxBuffer through 
HAL_SPI_TransmitReceive_DMA(), at the same time SPI Slave transmits aTxBuffer 
and receives aRxBuffer through HAL_SPI_TransmitReceive_DMA(). 
The end of this step is monitored through the HAL_SPI_GetState() function
result.
Finally, aRxBuffer and aTxBuffer are compared through Buffercmp() in order to 
check buffers correctness.  

LED2 can be used to monitor the transfer status:
 - LED2 turns ON on master board waiting user button to be pressed.
 - LED2 turns OFF on master board waiting the transmission process is complete.
 - LED2 turns ON when the transmission/reception process is correct.

 @note SPIx instance used and associated resources can be updated in "main.h"
       file depending hardware configuration used.

 @note You need to perform a reset on Slave board, then perform it on Master board
       to have the correct behaviour of this example.


@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The example needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - SPI/SPI_FullDuplex_ComDMA/Inc/stm32l0xx_hal_conf.h    HAL configuration file
  - SPI/SPI_FullDuplex_ComDMA/Inc/stm32l0xx_it.h          Interrupt handlers header file
  - SPI/SPI_FullDuplex_ComDMA/Inc/main.h                  Header for main.c module  
  - SPI/SPI_FullDuplex_ComDMA/Src/stm32l0xx_it.c          Interrupt handlers
  - SPI/SPI_FullDuplex_ComDMA/Src/main.c                  Main program
  - SPI/SPI_FullDuplex_ComDMA/Src/stm32l0xx_hal_msp.c     HAL MSP module
  - SPI/SPI_FullDuplex_ComDMA/Src/system_stm32l0xx.c      STM32L0xx system source file


@par Hardware and Software environment 

  - This example runs on STM32L051xx, STM32L052xx, STM32L053xx STM32L062xx and 
    STM32L063xx device lines RevZ
    
  - This example has been tested with STM32L053R8-Nucleo RevC and can be
    easily tailored to any other supported device and development board.

  - STM32L053R8-Nucleo RevC Set-up
    - Connect Master board PB13 (pin 30 in CN10 connector) to Slave Board PB13
    - Connect Master board PB14 (pin 28 in CN10 connector) to Slave Board PB14
    - Connect Master board PB15 (pin 26 in CN10 connector) to Slave Board PB15
    - Connect Master board GND  to Slave Board GND
    - SB35 ON
    - SB44 OFF
    - SB28 ON
    - SB39 OFF
    - SB25 ON
    - SB36 OFF


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
    o Uncomment "#define MASTER_BOARD" and load the project in Master Board
    o Comment "#define MASTER_BOARD" and load the project in Slave Board
 - Run the example


 */
 