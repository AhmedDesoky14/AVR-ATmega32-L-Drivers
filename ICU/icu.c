/*
 *  icu.c
 *  Created on: Oct 7, 2022
 *  Author: Ahmed Desoky
 *  Description:
 *  			AVR ATmega32/L ICU Driver
 *  			#Supports Noise Canceler Configuration
 */
/*==================================INCLUDES=============================================*/
#include "icu.h"
/*===============================GLOBAL VARIABLES========================================*/
/*callback function pointer - Locked into File scope only - volatile*/
static volatile void (*g_callBackFunction_Ptr)(void) = NULL_PTR;
/*=====================================ISRs==============================================*/
ISR(TIMER1_CAPT_vect) /*ISR of ICU*/
{
	if(g_callBackFunction_Ptr != NULL_PTR) /*If callback function pointer doesn't equal NULL*/
	{
		(*g_callBackFunction_Ptr)(); /*callback the function using the function pointer*/
	}
}
/*=============================FUNCTIONS DEFINITIONS=====================================*/
/* Description:
 * Function to initialize the ICU
 * [Inputs]:
 *			pointer to structure of type ICU Configuration
 *			Contains Noise Canceler Option, ICU_Clock & ICU first edge type detection
 *			Predefined in the Main Application
 * [No Return]
 */
void ICU_init(const ICU_CONFIG_STRUCT *Config_Ptr)
{
	CLEAR_BIT(DDRD,PD6); /*Set ICP1 Pin as input pin*/
	TCCR1A = 0x0C; /*Setting only FOC1A & FOC1B Bits to operate in non-pwm mode (normal mode)*/
	/*clear clock bits and resetting it with the chosen clock*/
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->ICU_clock);
	switch(Config_Ptr->ICU_clock)
	if(Config_Ptr->Noise_Canceler==Noise_Canceler_ON)
		SET_BIT(TCCR1B,ICNC1); /*Enable Noise Canceler*/
	SET_BIT(TCCR1B,(Config_Ptr->Edge_Type)<<(ICES1)); /*set detecting Edge type start*/
	TCNT1 = 0; /*reset timer to zero */
	ICR1 = 0; /*reset Input Capture Register to zero*/
	SET_BIT(TIMSK,TICIE1); /*Enable Input Capture Interrupt*/
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * Function to initialize set the callback function
 * [Inputs]:
 *			pointer to function which is passed from the main APP to the Driver to be called in the ISR
 * [No Return]
 */
void ICU_setCallBackFunction(void(*a_FunctionPtr)(void))
{
	g_callBackFunction_Ptr = a_FunctionPtr;
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * Function to reset the counter/timer
 * [No Inputs]:
 * [No Return]
 */
void ICU_resetTimer(void)
{
	TCNT1 = 0; /*reset timer to zero */
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * Function to get the input capture register value
 * [No Inputs]
 * [Returns]:
 * 				Input Capture Register value
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1; /*return Input Capture Register*/
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * Function to set the next detection edge to respond
 * [Inputs]:
 * 				EdgeType
 * [No Return]
 */
void ICU_setEdgeDetectionType(const ICU_EDGE_TYPE a_edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<ICES1); /*Put the value of edge type in its bit*/
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * Function to terminate the ICU
 * [No Input]
 * [No Return]
 */
void ICU_DeInit(void)
{
	TCCR1A = 0; /*clear the register*/
	TCCR1B &= 0x20; /*clear the register*/
	TCNT1 = 0; /*Clear counter*/
	ICR1 = 0; /*Clear ICU Register*/
	CLEAR_BIT(TIMSK,TICIE1); /*Disable Input Capture Interrupt*/
}
