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
  
  
uint8_t Rh_byte1 = 0xFF, Rh_byte2 = 0xFF, Temp_byte1 = 0xFF, Temp_byte2 = 0xFF,Sum = 0xFF;
uint16_t RH= 0xFFFF, TEMP= 0xFFFF;

float Temperature = 0xFFFF;
float Humidity = 0xFFFF;
uint8_t Presence = 0;


void Delay_us (uint16_t time)
{
	/* change your code here for the delay in microseconds */    
	__HAL_TIM_SET_COUNTER(&htim3, 0);
    HAL_TIM_Base_Start(&htim3);
	while ((__HAL_TIM_GET_COUNTER(&htim3))<time){};
    HAL_TIM_Base_Stop(&htim3);

}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DHT11_Start (void)
{
	Set_Pin_Output (GPIOB, GPIO_PIN_12);  // set the pin as output
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_12,GPIO_PIN_RESET);   // pull the pin low
	Delay_us (18000);   // wait for 18ms
    HAL_GPIO_WritePin (GPIOB, GPIO_PIN_12, GPIO_PIN_SET);   // pull the pin high
	Delay_us (20);   // wait for 20us
	Set_Pin_Input(GPIOB, GPIO_PIN_12);    // set as input
}

uint8_t DHT11_Check_Response (void)
{
	uint8_t Response = 0;
	Delay_us (40);
    uint8_t timeCount = 0;
	if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)))
	{
		Delay_us (80);
		if ((HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12))){
            Response = 1;
        }
		else {
            Response = 0;
        }
	}
    //Delay_us (87);
//    do{
//        timeCount ++;
//    }while ((HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12))&&(timeCount != 0));   // wait for the pin to go low
    while ((HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)));
	return Response;
}

uint8_t DHT11_Read (void)
{
	uint8_t i,j,count=0;
	for (j=0;j<8;j++)
	{
		while (!HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)){};   // wait for the pin to go high
        printf("此时电平:%d\n",HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12));
		Delay_us (40);   // wait for 40 us
		if (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)))   // if the pin is low
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else i|= (1<<(7-j));  // if the pin is high, write 1
//        do{
//            count++;
//        }while ((HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12))&&(count != 0));  // wait for the pin to go low
        printf("第%d次的temp=%d\n",j,i);
        while ((HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)));
	}
	return i;
}


//void DHT11_Start(void)
//{
//    Set_Pin_Output(GPIOB,GPIO_PIN_12);
//    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
//    HAL_Delay(18);//keep low 18000us
//    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
//    Delay_us(30);
//    Set_Pin_Input(GPIOB,GPIO_PIN_12);
//}

//uint8_t DHT11_Check_Response()
//{
//    uint8_t Respone = 0, TimeOut = 0;
//    
//	//Delay_us (40);
//    while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)); //等待低电平
//    
//    Delay_us(100);
//    printf("此时电平:%d\n",HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12));
//    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)==1)
//    {
//        Respone = 1; //回应结束，准备接收数据
//    }else {
//        Respone = 0;
//    }
//    return Respone;
//}

//uint8_t DHT11_Read(){
//    uint8_t i,temp = 0;
//    for(i=0;i<8;i++){
//        while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12));//等待外设输入高电平
//        Delay_us(40);
//        printf("DHT11发送数据低电平状态\n");
//        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)){//输入的是1
//            temp  += 1<<(7-i);           
//        }else{
//           temp &= ~(1<<(7-i));
//        }
//        printf("第%d次的temp=%d\n",i,temp);
//        while ((HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12)));
//    }
//    return temp;
//    
//}

void DHT11Process(void){
    
    DHT11_Start();
    Presence = DHT11_Check_Response();
    printf("响应结果:%d\n",Presence);
    if(Presence == 0)
    {
        return;
    }
    Rh_byte1 = DHT11_Read ();
    Rh_byte2 = DHT11_Read ();
    Temp_byte1 = DHT11_Read ();
    Temp_byte2 = DHT11_Read ();
    Sum = DHT11_Read();
    printf("湿度高8位:%d\r\n", Rh_byte1);
    printf("湿度低8位:%d\r\n", Rh_byte2);
    printf("温度高8位:%d\r\n", Temp_byte1);
    printf("温度低8位:%d\r\n", Temp_byte2);
    printf("校验位:%d\r\n", Sum);
    if(Sum != (uint8_t)(Rh_byte1+Rh_byte2+Temp_byte1+Temp_byte2)){
        
        return;
    }
    TEMP = Temp_byte1*10+Temp_byte2;
    RH = Rh_byte1*10+Rh_byte2;
    Temperature = (float) TEMP/10;
    Humidity = (float) RH/10;
    printf("湿度高8位:%d\r\n", Rh_byte1);
    printf("湿度低8位:%d\r\n", Rh_byte2);
    printf("温度高8位:%d\r\n", Temp_byte1);
    printf("温度低8位:%d\r\n", Temp_byte2);
    printf("校验位:%d\r\n", Sum);

    printf("湿度:%.1f   温度:%.1f\n",Humidity, Temperature);
}

