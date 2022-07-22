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

uint16_t LSValue = 0,count = 0;
uint16_t adcValue[3] = {0};

void LightSensorProcess(void);
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
//    count ++;
//    LSValue = (uint16_t)HAL_ADC_GetValue(&hadc2);
//    printf("传感器的值: %d\n",LSValue);
//    if(count > 1000)
//    {
////        HAL_ADC_Stop_IT(&hadc2);
//    }
////      printf("传感器的值位: %d,%d\n",adcValue[0],adcValue[1]);
////    memset(adcValue,0,sizeof(adcValue));
//    //HAL_ADC_Stop_DMA(&hadc1);
//}

void MuitChNotI(void)
{
    int i = 0;
    uint32_t result[3] = {0};
    for(i=0;i<3;i++)
    {
        HAL_ADC_Start(&hadc1);
        //HAL_ADC_Start_IT(&hadc2);
        HAL_ADC_PollForConversion(&hadc1,100);
        result[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
        
    }
    HAL_ADC_Stop(&hadc1);
    for(i=0;i<3;i++)
    {
        printf("通道%d的值: %d\n",i,result[i]);
    }
}

void DMA_ADCProcess()
{
    memset(adcValue,0,3);
    HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adcValue,3);
    for(int i=0;i<3;i++)
    {
        printf("通道%d的值为%d\n",i+1,adcValue[i]);
    }
}
void LightSensorProcess(void)
{
    //MuitChNotI();
    DMA_ADCProcess();
    //printf("通道的值: %d\n",LSValue);
    //HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adcValue,2);   
//    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13))
//    {
//        printf("光照达不到阈值\n");
//    }
//    else{
//         printf("光照达到阈值\n");
//    }
    

}
