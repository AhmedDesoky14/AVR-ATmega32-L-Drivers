/*
 *  watchdogtimer.h
 *  Created on: Nov 9, 2022
 *  Author: Ahmed Desoky
 *  Description:
 *  				Atmega32/L Watch dog timer Driver
 */
#ifndef WATCHDOGTIMER_H_
#define WATCHDOGTIMER_H_
/*==================================INCLUDES=============================================*/
#include <avr/io.h>
#include <util/delay.h>
/*==============================Configuration Note=======================================*/
/*	to re-configure this driver go to line 31 in the .c file
 */
/*====================================ENUMS==============================================*/
typedef enum
{	  /*case*/	/*Vcc=3*/		/*Vcc=5*/
		K16,	/*17.1ms*/		/*16.3ms*/
		K32,	/*34.3ms*/		/*32.5ms*/
		K64,	/*68.5ms*/		/*65ms*/
		K128,	/*0.14s*/		/*0.13s*/
		K256,	/*0.27s*/		/*0.26s*/
		K512,	/*0.55s*/		/*0.52s*/
		K1024,	/*1.1s*/		/*1s*/
		K2048	/*2.2s*/		/*2.1s*/
}WATCH_DOG_TIMER_PRESCALER;
/*=================================FUNCTIONS DECLARATIONS================================*/
/*Functions Description in .c file*/
void WDT_ON(WATCH_DOG_TIMER_PRESCALER Watch_Dog_Time);
void WDT_OFF(void);
#endif /* WATCHDOGTIMER_H_ */
