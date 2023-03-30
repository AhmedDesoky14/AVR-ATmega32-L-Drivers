/*
 *  uart.c
 *  Created on: Oct 17, 2022
 *  Author: Ahmed Desoky
 *  Description:
 *  			AVR ATmega32/L SPI Driver
 *  			#Full Configurable
 *  			#Supports only polling (no interrupts)
 */
/*==================================INCLUDES=============================================*/
#include "spi.h"
/*=============================FUNCTIONS DEFINITIONS=====================================*/
/* Description:
 * 					Function to initalize the SPI as Master
 * [No Inputs]:		SPI Master Clock Pre-scaler to setup the frequency
 *
 * [No Returns]:
 */
void SPI_initMaster(SPI_MASTER_CLOCK_PRESCALER_SELECTION SPI_MASTER_CLOCK_PRESCALER)
{
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_OUTPUT); /*_SS PIN OUPUT*/
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT); /*MOSI PIN OUPUT*/
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_INPUT);  /*MISO PIN INPUT*/
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT); /*SCK PIN OUPUT*/
	/*Always MSB will be transmitted and received first*/
	/*DORD=0*/
	SET_BIT(SPCR,MSTR); /*Enable Master Mode*/
	/*Always clock start from 0 and always sample at the rising edge*/
	/*CPOl & CHPHA = 0*/
	/*Always Interrupt Module is off*/
	switch(SPI_MASTER_CLOCK_PRESCALER)
	{
		case F2:
			SET_BIT(SPSR,SPI2X);
			break;
		case F4:
			/*Don't set any bit*/
			break;
		case F8:
			SET_BIT(SPSR,SPI2X);
			SET_BIT(SPCR,SPR0);
			break;
		case F16:
			SET_BIT(SPCR,SPR0);
			break;
		case F32:
			SET_BIT(SPSR,SPI2X);
			SET_BIT(SPCR,SPR1);
			break;
		case F64:
			SET_BIT(SPSR,SPI2X);
			SET_BIT(SPCR,SPR1);
			SET_BIT(SPCR,SPR0);
			break;
		case F128:
			SET_BIT(SPCR,SPR1);
			SET_BIT(SPCR,SPR0);
			break;
	}
	SET_BIT(SPCR,SPE); /*Enable SPI*/
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * 					Function to initalize the SPI as Slave
 * [No Inputs]:		SPI Master Clock Pre-scaler to setup the frequency
 *
 * [No Returns]:
 */
void SPI_initSlave(SPI_MASTER_CLOCK_PRESCALER_SELECTION SPI_MASTER_CLOCK_PRESCALER)
{
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_INPUT); /*_SS PIN INPUT*/
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_INPUT); /*MOSI PIN INPUT*/
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_OUTPUT);  /*MISO PIN OUPUT*/
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_INPUT); /*SCK PIN INPUT*/
	/*Always MSB will be transmitted and received first*/
	/*DORD=0*/
	/*MSTR=0 - Slave*/
	switch(SPI_MASTER_CLOCK_PRESCALER)
	{
		case F2:
			SET_BIT(SPSR,SPI2X);
			break;
		case F4:
			/*Don't set any bit*/
			break;
		case F8:
			SET_BIT(SPSR,SPI2X);
			SET_BIT(SPCR,SPR0);
			break;
		case F16:
			SET_BIT(SPCR,SPR0);
			break;
		case F32:
			SET_BIT(SPSR,SPI2X);
			SET_BIT(SPCR,SPR1);
			break;
		case F64:
			SET_BIT(SPSR,SPI2X);
			SET_BIT(SPCR,SPR1);
			SET_BIT(SPCR,SPR0);
			break;
		case F128:
			SET_BIT(SPCR,SPR1);
			SET_BIT(SPCR,SPR0);
			break;
	}
	SET_BIT(SPCR,SPE); /*Enable SPI*/

}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * 					Function that load the data needed to be transmitted (if useful)
 * 					and keep polling on the SPI Flag until it's set to be informed that
 * 					byte exchanging is done (receive and transmit the byte)
 * 					then return the received byte (if useful)
 * [Inputs]:		the data needed to be transmitted wether it's used or not
 *
 * [Returns]:		the data needed to be received wether it's used or not
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
	SPDR = data; /*load data to the SPI Data Register*/
	while(BIT_IS_CLEAR(SPSR,SPIF)){}; /*while flag != 0 - transmission is not complete yet*/
	return SPDR; /*return the received data from SPI Data Register*/
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * 					Function to transmit a string character by character using SPI_sendReceiveByte function
 * [Inputs]:		pointer to the string wanted to be transmitted
 *
 * [No Returns]:
 */
void SPI_sendString(const char* string)
{
	uint8 counter=0;
	uint8 readdata; /*usused data variable to just hold the received byte*/
	/*transmit the string character by character*/
	while(string[counter] != '\0')
	{
		readdata = SPI_sendReceiveByte(string[counter]);
		counter++;
	}
}
/*----------------------------------------------------------------------------------------*/
/* Description:
 * 					Function to receive a string character by character using SPI_sendReceiveByte function
 * [Inputs]:		pointer to the string wanted to be received to store it in the address of the pointer
 *
 * [No Returns]:
 */
void SPI_receiveString(char* string)
{
	uint8 counter=0;
	uint8 defaultdata = 0xFF; /*usused data variable to send any random byte*/
	string[counter] = SPI_sendReceiveByte(defaultdata);
	/*receive the string character by character*/
	/*===========================This loop is Re-configurable=============================*/
	/*'#' is pre-agreement character chosen between the transimitter and the receiver*/
	/*to tell the end of the string*/
	while(string[counter] != '#')
	{
		counter++;
		string[counter] = SPI_sendReceiveByte(defaultdata);
	}
	string[counter] = '\0';
}
