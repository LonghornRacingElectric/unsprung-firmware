/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_R_Pin GPIO_PIN_0
#define LED_R_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_1
#define LED_G_GPIO_Port GPIOA
#define LED_B_Pin GPIO_PIN_2
#define LED_B_GPIO_Port GPIOA
#define SPI_CS_IMU_Pin GPIO_PIN_1
#define SPI_CS_IMU_GPIO_Port GPIOB
#define SPI_CS_EEPROM_Pin GPIO_PIN_10
#define SPI_CS_EEPROM_GPIO_Port GPIOB
#define SPI_CS_WS1_Pin GPIO_PIN_12
#define SPI_CS_WS1_GPIO_Port GPIOB
#define Calib_Button_Pin GPIO_PIN_12
#define Calib_Button_GPIO_Port GPIOA
#define SPI_CS_WS2_Pin GPIO_PIN_15
#define SPI_CS_WS2_GPIO_Port GPIOA
#define BOOT0_Shorted_Dont_Use_Pin GPIO_PIN_7
#define BOOT0_Shorted_Dont_Use_GPIO_Port GPIOB
#define BOOT0_Dont_Use_Pin GPIO_PIN_3
#define BOOT0_Dont_Use_GPIO_Port GPIOH

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
