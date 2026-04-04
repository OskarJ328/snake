/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#define row4_Pin GPIO_PIN_10
#define row4_GPIO_Port GPIOB
#define row1_Pin GPIO_PIN_7
#define row1_GPIO_Port GPIOC
#define row3_Pin GPIO_PIN_8
#define row3_GPIO_Port GPIOA
#define row2_Pin GPIO_PIN_9
#define row2_GPIO_Port GPIOA
#define column4_Pin GPIO_PIN_10
#define column4_GPIO_Port GPIOA
#define column3_Pin GPIO_PIN_3
#define column3_GPIO_Port GPIOB
#define column1_Pin GPIO_PIN_4
#define column1_GPIO_Port GPIOB
#define column2_Pin GPIO_PIN_5
#define column2_GPIO_Port GPIOB
#define matrix_CS_Pin GPIO_PIN_6
#define matrix_CS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
