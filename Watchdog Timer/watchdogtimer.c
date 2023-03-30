/*
 *  watchdogtimer.c
 *  Created on: Nov 9, 2022
 *  Author: Ahmed Desoky
 *  Description:
 *  				Atmega32/L Watch dog timer Driver
 */
/*==================================INCLUDES=============================================*/
#include "watchdogtimer.h"
/*=============================FUNCTIONS DEFINITIONS=====================================*/
/* Description:
 *				 Function to Enable watch dog timer
 * [Inputs]:
 * 				 Timer clock to be adjusted of type of enumeration WATCH_DOG_TIMER_PRESCALER
 * [No Return]:
 */
void WDT_ON(WATCH_DOG_TIMER_PRESCALER Watch_Dog_Time)
{
	WDTCR = Watch_Dog_Time;	/*Adjust the clock*/
	WDTCR |= (1<<WDE);		/*Enable watch dog timer*/
}
/*-----------------------------------------------------------------------------------------------*/
/* Description:
 *				 Function to disable watch dog timer
 * [No Inputs]:
 * [No Return]:
 */
void WDT_OFF(void)
{
	WDTCR = (1<<WDE) | (1<<WDTOE);	/*Enable WDTOE to be able to disable Watch dog Enable*/
	_delay_us(3); //wait 3 clocks then disable the watch dog timer /*Depending on the target freq*/
	WDTCR = 0; /*Disable the watch dog timer in the way the data sheet clarified*/
}
