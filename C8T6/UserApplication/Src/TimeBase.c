/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : System.c
  * @brief          : System program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "MyApplication.h"

uint16_t Time1msCount = 0;
uint16_t DHT11Count = 0;
//1ms定时回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   if(htim->Instance == TIM2)
  {
    if(Time1msCount < 0xffff)
    {
        Time1msCount ++;
    }
    if(DHT11Count < 2000)
    {
        DHT11Count ++;
    }
  }
      
}
