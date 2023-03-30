/*
 *  uart.h
 *  Created on: Oct 17, 2022
 *  Author: Ahmed Desoky
 *  Description:
 *  			AVR ATmega32/L SPI Driver
 *  			#Full Configurable
 *  			#Supports only polling (no interrupts)
 */
#ifndef SPI_H_
#define SPI_H_
/*==================================INCLUDES=============================================*/
#include <avr/io.h> /*Registers are not updated in in the atmega32_registers.h file*/
#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"
/*==============================ENUMS & STRUCTURES=======================================*/
typedef enum
{
	F2,F4,F8,F16,F32,F64,F128
}SPI_MASTER_CLOCK_PRESCALER_SELECTION;
/*===========================DEFINITIONS & CONFIGURATIONS================================*/
#define SPI_SEND_OR_RECEIVE_READY 0x10 /*pre-agreement value to be sent and received*/
/*=================================FUNCTIONS DECLARATIONS================================*/
/*Functions Description in .c file*/
void SPI_initMaster(SPI_MASTER_CLOCK_PRESCALER_SELECTION SPI_MASTER_CLOCK_PRESCALER);
void SPI_initSlave(SPI_MASTER_CLOCK_PRESCALER_SELECTION SPI_MASTER_CLOCK_PRESCALER);
uint8 SPI_sendReceiveByte(uint8 data);
void SPI_sendString(const char* string);
void SPI_receiveString(char* string);
#endif /* SPI_H_ */
