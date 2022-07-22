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

void DHT11Process(void);


void UserInit()
{
    HAL_TIM_Base_Start_IT(&htim2);
    //HAL_TIM_Base_Stop_IT(&htim2);
    HAL_ADCEx_Calibration_Start(&hadc1);
//    HAL_ADC_Start_IT(&hadc2);
//    HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adcValue,3);
}
/*
    buffer[0] - bit0:Left button
                bit1: Right button
                bit2:Middle button
    
    buffer[1] - Cursor movement X axis [-127 - 127]
    buffer[2] - Cursor movememt Y axis [-127 - 127]
    buffer[3] - Wheel vertical movememt [-127 - 127]
    */
    
//    uint8_t buffer[4] = {0};
void run(void)
{
    //uint8_t uR[100] = {0};
    /*uint8_t i = 0;
    for(i=0; i<150; i++)
    {
      buffer[1] = 5;
      buffer[2] = 5 ;
      USBD_HID_SendReport(&hUsbDeviceFS,buffer,4);
      
      HAL_Delay(500); 
    }

    */
//    printf("this is LED\n");
    
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//    HAL_Delay(500);

//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//    HAL_Delay(100);
//    
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//    HAL_Delay(50);

//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//    HAL_Delay(100);
//    
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
//    HAL_Delay(200);
    
    if(Time1msCount > 1000)
    {
        Time1msCount = 0;
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    }
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
//    printf("文件: %s 行: %d 函数: %s\n",__FILE__,__LINE__,__FUNCTION__);
    
    
//    HAL_UART_Receive(&huart1,uR,100,100);
//    printf("USART接收到的数据:%s\n",uR);
    
    if(DHT11Count >= 2000)
    {
        DHT11Count = 0;
        //DHT11Process();   
    }
    //光敏传感器采集
    LightSensorProcess();
}

/*  串口打印重写*/
int fputc(int ch,FILE *f)
{
    HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,1000);
    return ch;
}
