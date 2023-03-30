/*
 *  adc.h
 *  Created on: Oct 4, 2022
 *  Author: Ahmed Desoky
 *  Description:
 *  			AVR ATmega32/L ADC Driver
 *  			#Doesn't Support Auto Trigerring  Mode
 *  			#Although Auto Trigerring could be added
 */
#ifndef ADC_H_
#define ADC_H_
/*==================================INCLUDES=============================================*/
#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h> /*in case of Interrupt mode*/
/*==============================ENUMS & STRUCTURES=======================================*/
typedef enum /*This enum to Choose ADC Pre-scaler 2,4,8,16,32,64,128*/
{
	N2,N4,N8,N16,N32,N64,N128
}ADC_Prescaler;
/*---------------------------------------------------------------------------------------*/
typedef enum /*This enum to Choose ADC VREF (AREF Pin-AVCC Pin-INTERNAL_VREF Pin)*/
{
	AREF,AVCC,INTERNAL_VREF
}ADC_ReferenceVoltage;
/*---------------------------------------------------------------------------------------*/
typedef struct /*Structure that contains ADC Configuration*/
{
	ADC_ReferenceVoltage ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;
/*===========================DEFINITIONS & CONFIGURATIONS================================*/
#define ADC_MAXIMUM_VALUE 1023
#define ADC_REF_VOLT_VALUE 2.56
#define ADC_CONVERSION_COMPLETE_MODE 0 /*0 = Polling Mode - 1 = Interrupt Mode*/
/*=================================FUNCTIONS DECLARATIONS================================*/
/*Functions Description in .c file*/
void ADC_init(const ADC_ConfigType *Config_Ptr);
#if(ADC_CONVERSION_COMPLETE_MODE==0)
uint16 ADC_readChannel(uint8 ch_num);
#endif
#if(ADC_CONVERSION_COMPLETE_MODE==1)
void ADC_readChannel(uint8 a_chNum);
#endif
#endif /* ADC_H_ */
