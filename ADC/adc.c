/*
 *  adc.c
 *  Created on: Oct 4, 2022
 *  Author: Ahmed Desoky
 *  Description:
 *  			AVR ATmega32/L ADC Driver
 *  			#Doesn't Support Auto Trigerring  Mode
 *  			#Although Auto Trigerring could be added
 */
/*==================================INCLUDES=============================================*/
#include "adc.h"
#if(ADC_CONVERSION_COMPLETE_MODE==1)
/*===============================GLOBAL VARIABLES========================================*/
volatile uint16 g_adcValue;
/*=====================================ISRs==============================================*/
ISR(ADC_vect)
{
	g_adcValue = ADC;
}
#endif
/*=============================FUNCTIONS DEFINITIONS=====================================*/
/* Description:
 * Function to initialize the ADC
 * [Inputs]:
 * 			pointer to structure of type ADC Configuration
 * 			Contains VREF & ADC_Pre-scaler
 * 			Predefined in the Main Application
 * [No Return]
 */
void ADC_init(const ADC_ConfigType *Config_Ptr)
{
	CLEAR_BIT(ADMUX,ADLAR); /*Normal Bits ordering*/
	ADMUX &= (0xE0);/*Select Channel 0 initially*/
	/*Selection of VREF according the function parameters*/
	switch(Config_Ptr->ref_volt)
	{
		case(AREF):
			ADMUX &= 0x3F; /*Clear VREF Selection*/ /*Selection of AREF*/
			break;
		case(AVCC):
			ADMUX &= 0x3F; /*Clear VREF Selection*/
			SET_BIT(ADMUX,REFS0); /*Selection of AVCC*/
			break;
		case(INTERNAL_VREF):
			ADMUX &= 0x3F; /*Clear VREF Selection*/
			SET_BIT(ADMUX,REFS0); /*Selection of Internal VREF*/
			SET_BIT(ADMUX,REFS1);
			break;
	}
	switch(Config_Ptr->prescaler)
	{
		case(N2): /*Set Pre-scaler into N=2*/
			ADCSRA &= 0xF8; /*Clear Pre-scaler Selection*/
			break;
		case(N4): /*Set Pre-scaler into N=4*/
			ADCSRA &= 0xF8; /*Clear Pre-scaler Selection*/
			SET_BIT(ADCSRA,ADPS1);
			break;
		case(N8): /*Set Pre-scaler into N=8*/
			ADCSRA &= 0xF8; /*Clear Pre-scaler Selection*/
			SET_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			break;
		case(N16): /*Set Pre-scaler into N=16*/
			ADCSRA &= 0xF8; /*Clear Pre-scaler Selection*/
			SET_BIT(ADCSRA,ADPS2);
			break;
		case(N32): /*Set Pre-scaler into N=32*/
			ADCSRA &= 0xF8; /*Clear Pre-scaler Selection*/
			SET_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS2);
			break;
		case(N64):
			ADCSRA &= 0xF8; /*Clear Pre-scaler Selection*/
			SET_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
		case(N128):
			ADCSRA &= 0xF8; /*Clear Pre-scaler Selection*/
			SET_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
	}
#if (ADC_CONVERSION_COMPLETE_MODE==0)
	CLEAR_BIT(ADCSRA,ADIE); /*Disable Interrupt Module*/
#elif (ADC_CONVERSION_COMPLETE_MODE==1)
	SET_BIT(ADCSRA,ADIE); /*Enable Interrupt Module*/
#endif
	SET_BIT(ADCSRA,ADEN);	/*Enable ADC*/
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * Function to read analog data from specified channel 1-->7
 * [Inputs]:
 * 			Channel Number
 * [Returns]:
 * 			Digital Value from the ADC (in case of polling mode)
 * 			ISR and store ADC Value in shared global variable called g_adcValue (in case of interrupt mode)
 * 		Note: We don't set the ADC port as input port using DDR Register
 */
#if(ADC_CONVERSION_COMPLETE_MODE==0)
uint16 ADC_readChannel(uint8 a_chNum)
{
	a_chNum &= 0x07; /**Input channel number must be from 0 --> 7*/
	ADMUX &= (0xE0); /*Clear first 5 bits of channel selection*/
	ADMUX |= (a_chNum); /*insert channel number to ADMUX REG*/
	SET_BIT(ADCSRA,ADSC); /*START CONVERSION*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /*(Polling) waiting until flag(ADIF)=1*/
	SET_BIT(ADCSRA,ADIF); /*Clear Flag (ADIF)*/
	return ADC; /*return ADC Register where data are converted*/
}
#endif
/*----------------------------------------------------------------------------------------*/
#if(ADC_CONVERSION_COMPLETE_MODE==1)
void ADC_readChannel(uint8 a_chNum)
{
	a_chNum &= 0x07; /**Input channel number must be from 0 --> 7*/
	ADMUX &= (0xE0); /*Clear first 5 bits of channel selection*/
	ADMUX |= (a_chNum); /*insert channel number to ADMUX REG*/
	SET_BIT(ADCSRA,ADSC); /*START CONVERSION*/
}
#endif
