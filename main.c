#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include<stdio.h>
#include<stdlib.h>
#include "audio2.h"

/*
 * Guziczki
 * K0 -> A1
 * K1 -> A2
 * K2 -> A3
 *
 * Wyświetlacz
 * a -> E4
 * b -> E5
 * c -> E6
 * d -> E7
 * e -> E8
 * f -> E9
 * g -> E10
 * h -> E11
 *
 * DAC
 * IN -> A4
 * ADC1 -> A5
 *
 *
 *
 *
 *
 * */



int a = 0;
int b = 0;
int c = 0;
int d = 0;
int segment = 0;
int mode = 0;
int a1 = 0, b1 = 0, c1 = 0 , d1 = 0;
int counter_seg = -1;
int iter;
int ADC_Result, solution;
int on_off = 1;

volatile int segments[]={GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7,GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11};
volatile int i=0;
volatile int piny[] = {GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3};

uint16_t numbersReset [10] = {
		/* -0- */   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9,
		/* -1- */	GPIO_Pin_5 | GPIO_Pin_6,
		/* -2- */	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 ,
		/* -3- */	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 ,
		/* -4- */	GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_10,
		/* -5- */	GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 ,
		/* -6- */   GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10,
		/* -7- */	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6,
		/* -8- */   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10,
		/* -9- */	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10
};

uint16_t numbersSet [10] = {
		/* -0- */   GPIO_Pin_10 | GPIO_Pin_11,
		/* -1- */	GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11,
		/* -2- */	GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_11,
		/* -3- */	GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11,
		/* -4- */	GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_11,
		/* -5- */	GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_11,
		/* -6- */	GPIO_Pin_5 | GPIO_Pin_11,
		/* -7- */	GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11,
		/* -8- */   GPIO_Pin_11,
		/* -9- */	GPIO_Pin_8 | GPIO_Pin_11
};

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{

		if(iter==123200) iter=0;

		DAC_SetChannel1Data(DAC_Align_12b_R,rawAudio[iter]*ADC_Result/1000);
		++iter;


		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		if(segment == 0)
		{
			GPIO_SetBits(GPIOD, piny[0]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[2] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[a1]);
			GPIO_ResetBits(GPIOE, numbersReset[a1]);

		}
		if(segment == 1)
		{
			GPIO_SetBits(GPIOD, piny[1]);
			GPIO_ResetBits(GPIOD, piny[0] | piny[2] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[b1]);
			GPIO_ResetBits(GPIOE, numbersReset[b1]);
		}
		if(segment == 2)
		{
			GPIO_SetBits(GPIOD, piny[2]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[0] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[c1]);
			GPIO_ResetBits(GPIOE, numbersReset[c1]);
		}
		if(segment == 3)
		{
			GPIO_SetBits(GPIOD, piny[3]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[2] | piny[0]);

			GPIO_SetBits(GPIOE, numbersSet[d1]);
			GPIO_ResetBits(GPIOE, numbersReset[d1]);
		}
		segment++;
		if(segment == 4) segment = 0;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		if(segment == 0)
		{
			GPIO_SetBits(GPIOD, piny[0]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[2] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[a]);
			GPIO_ResetBits(GPIOE, numbersReset[a]);

		}
		if(segment == 1)
		{
			GPIO_SetBits(GPIOD, piny[1]);
			GPIO_ResetBits(GPIOD, piny[0] | piny[2] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[b]);
			GPIO_ResetBits(GPIOE, numbersReset[b]);
		}
		if(segment == 2)
		{
			GPIO_SetBits(GPIOD, piny[2]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[0] | piny[3]);

			GPIO_SetBits(GPIOE, numbersSet[c]);
			GPIO_ResetBits(GPIOE, numbersReset[c]);
		}
		if(segment == 3)
		{
			GPIO_SetBits(GPIOD, piny[3]);
			GPIO_ResetBits(GPIOD, piny[1] | piny[2] | piny[0]);

			GPIO_SetBits(GPIOE, numbersSet[d]);
			GPIO_ResetBits(GPIOE, numbersReset[d]);
		}
		segment++;
		if(segment == 4) segment = 0;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		d++;
		if(d==10) {d=0; c++;}
		if(c==6) {c=0; b++;}
		if(a<2 && b==10) {b=0; a++;}
		if(a==2 && b==3) {b=0; a++;}
		if(a==3) {a=0;}

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

void EXTI0_IRQHandler(void)
{
         	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
         	{
         		on_off = 1;
         		TIM_Cmd(TIM4, DISABLE);
         		a1=0; b1=0; c1=0; d1=0;

         		EXTI_ClearITPendingBit(EXTI_Line0);
   	   	}
}


int main(void)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//clock

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7 | GPIO_Pin_8 |  GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitTypeDef  GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure2);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
	TIM_TimeBaseStructure2.TIM_Period = 9999;
	TIM_TimeBaseStructure2.TIM_Prescaler = 20;
	TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure2.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure2);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure5;
	TIM_TimeBaseStructure5.TIM_Period = 9999;
	TIM_TimeBaseStructure5.TIM_Prescaler = 8399;
	TIM_TimeBaseStructure5.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure5.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure5);

	NVIC_InitTypeDef NVIC_InitStructure2;
	NVIC_InitStructure2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);

	NVIC_InitTypeDef NVIC_InitStructure5;
	NVIC_InitStructure5.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure5.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure5.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure5.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure5);

	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM5, ENABLE);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	GPIO_SetBits(GPIOE, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//set alarm

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure3;
	GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure3.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure3);

	//timer wyświetlający ustawianą godzinę

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure3;
	TIM_TimeBaseStructure3.TIM_Period = 9999;
	TIM_TimeBaseStructure3.TIM_Prescaler = 20;
	TIM_TimeBaseStructure3.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure3.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure3);

	NVIC_InitTypeDef NVIC_InitStructure3;
	NVIC_InitStructure3.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure3);

	TIM_Cmd(TIM3, DISABLE);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//plying alarm
	SystemInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	GPIO_InitTypeDef GPIO_InitStructure4;
	GPIO_InitStructure4.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure4.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure4);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure4;
	TIM_TimeBaseStructure4.TIM_Period = 62;
	TIM_TimeBaseStructure4.TIM_Prescaler = 83;
	TIM_TimeBaseStructure4.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure4.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure4);

	TIM_Cmd(TIM4, DISABLE);

	NVIC_InitTypeDef NVIC_InitStructure4;
	NVIC_InitStructure4.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure4.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure4.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure4.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure4);

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	//konfiguracja wszystkich ADC
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//konfiguracja danego pretwornika
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);
	ADC_Cmd(ADC1, ENABLE);

	DAC_InitTypeDef DAC_InitStructure;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DAC_Cmd(DAC_Channel_1, ENABLE);

	iter = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//wyłączenie alarmu

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	for(;;)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
		{
			if(mode == 0)
			{
				mode = 1;
				on_off = 0;
				TIM_Cmd(TIM2, DISABLE);
				TIM_Cmd(TIM3, ENABLE);
			}

			else if(mode == 1)
			{
				mode = 0;
				TIM_Cmd(TIM3, DISABLE);
				TIM_Cmd(TIM2, ENABLE);
			}
			for(int i=0 ; i<9979999; i++);
		}

		if((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0) && mode == 1)
		{
			counter_seg++;
			if(counter_seg==4) {counter_seg=0;}
			for(int i=0 ; i<9979999; i++);
		}

		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0 && mode == 1){
			if(counter_seg == 0)
			{
				a1++;
				if(a1==3) {a1=0;}

			}
			if(counter_seg == 1)
			{
				b1++;
				if(a1==2 && b1==4) {b1=0;}
				if(a1<2 && b1==10) {b1=0;}
			}
			if(counter_seg == 2)
			{
				c1++;
				if(c1==6) {c1=0;}

			}
			if(counter_seg == 3)
			{
				d1++;
				if(d1==10) {d1=0;}
			}
			for(int i=0 ; i<9979999; i++);
		}

		if(a==a1 && b==b1 && c==c1 && d==d1 && mode == 0 && on_off == 0)
		{
			TIM_Cmd(TIM4, ENABLE);
			ADC_SoftwareStartConv(ADC1);
			while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
			ADC_Result = ADC_GetConversionValue(ADC1);
			solution = (ADC_Result*2.95)/4095;
		}
	}
}
