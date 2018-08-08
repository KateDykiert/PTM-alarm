#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include<stdio.h>
#include<stdlib.h>

int a = 0;
int b = 0;
int c = 0;
int d = 0;
int segment = 0;
int mode = 0;
int a1 = 0, b1 = 0, c1 = 0 , d1 = 0;
int counter_seg = -1;


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

	for(;;)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
		{
			if(mode == 0)
			{
				mode = 1;
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
	}
}
