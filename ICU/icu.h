/*
 *  icu.h
 *  Created on: Oct 7, 2022
 *  Author: Ahmed Desoky
 *  Description:
 *  			AVR ATmega32/L ICU Driver
 *  			#Supports Noise Canceler Configuration
 */
#ifndef ICU_H_
#define ICU_H_
/*==================================INCLUDES=============================================*/
#include "std_types.h"
#include <avr/interrupt.h> /*For Interrupt*/
#include "common_macros.h"
//#include <avr/io.h>
#include "atmega32_registers.h" /*Driver Registers File*/
/*==============================ENUMS & STRUCTURES=======================================*/
typedef enum /*This enum to Choose ICU Clock Pre-scaler 1,8,64,256,1024 */
{					/*NO_CLOCK Stops the counter*/
	NO_CLOCK,F_CPU_CLOCK,F_CPU_N8,F_CPU_N64,F_CPU_N256,F_CPU_1024
}ICU_CLOCK_PRESCALER;
/*---------------------------------------------------------------------------------------*/
typedef enum /*This enum to Choose ICU edge type response */
{
	FALLING,RISING
}ICU_EDGE_TYPE;
/*---------------------------------------------------------------------------------------*/
typedef enum /*This enum to turn ICU noise canceler ON or OFF */
{
	Noise_Canceler_OFF,Noise_Canceler_ON
}ICU_NOISE_CANCELER;
/*---------------------------------------------------------------------------------------*/
typedef struct /*structure contains ICU Configuration*/
{
	ICU_CLOCK_PRESCALER ICU_clock;
	ICU_NOISE_CANCELER Noise_Canceler;
	ICU_EDGE_TYPE Edge_Type;
}ICU_CONFIG_STRUCT;
/*==============================FUNCTIONS DECLARATIONS===================================*/
/*Functions Description in .c file*/
void ICU_init(const ICU_CONFIG_STRUCT *Config_Ptr);
void ICU_setCallBackFunction(void(*a_FunctionPtr)(void));
void ICU_resetTimer(void);
uint16 ICU_getInputCaptureValue(void);
void ICU_setEdgeDetectionType(const ICU_EDGE_TYPE a_edgeType);
void ICU_DeInit(void);
#endif /* ICU_H_ */
