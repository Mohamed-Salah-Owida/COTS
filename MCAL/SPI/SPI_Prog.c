/*
 * SPI_Prog.c
 *
 *  Created on: Mar 14, 2025
 *      Author: moham
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "SPI_Prv.h"
#include "SPI_Reg.h"
#include "SPI_Cfg.h"
#include "SPI_Interface.h"


void SPI_voidInit(void)
{

#if  SPI_MASTER_SLAVE_SELECT == SPI_MASTER
	SET_BIT(SPCR,SPCR_MSTR);

	/*SCK  Pin 7 in PortB*/
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN7, DIO_u8PIN_OUTPUT);

	/*MISO Pin 6 in PortB  must is  input*/
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN6, DIO_u8PIN_INPUT);

	/*MOSI Pin 5 in PortB  must output is master */
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN5, DIO_u8PIN_OUTPUT);

	/*SS   Pin 7 in PortB  must is  input pull up or Vcc   (done need to change the master) */
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN4, DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN4, DIO_u8PINHIGH);

#elif SPI_MASTER_SLAVE_SELECT == SPI_SLAVE
	CLR_BIT(SPCR , SPCR_MSTR) ;
	/*SCK Pin 7 in PortB*/
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN7, DIO_u8PIN_INPUT);

	/*MISO Pin 6 in PortB  must is  input*/
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN6, DIO_u8PIN_OUTPUT);

	/*MOSI Pin 5 in PortB  must input is slave */
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN5, DIO_u8PIN_INPUT);

	/*SS   Pin 7 in PortB  must is input */
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN4, DIO_u8PIN_INPUT);

#else
#error "wrong SPI_MASTER_SLAVE_SELECT configuration"
#endif




	/*SPI Interrupt Enable PIE*/
#if SPI_INT_MODE == INT_DISABLED
	CLR_BIT(SPCR , SPCR_SPIE) ;
#elif SPI_INT_MODE == INT_ENABLED
	SET_BIT(SPCR , SPCR_SPIE) ;
#else
#error "wrong SPI_INTERRUPT_ENABLE_MODE configuration"
#endif


	/*Data Order MODE */
#if SPI_DATA_ORDER == LSB_FIRST
	SET_BIT(SPCR , SPCR_DORD) ;
#elif SPI_DATA_ORDER == MSB_FIRST
	CLR_BIT(SPCR, SPCR_DORD) ;
#else
#error "wrong SPI_DATA_ORDER configuration"
#endif



	/*Clock Polarity ( Rising & Falling Leading Edge )*/
#if SPI_CLK_POLARITY == SPI_RISING_LEADING_FALLING_TRAILING
	CLR_BIT(SPCR, SPCR_CPOL) ;
#elif SPI_CLK_POLARITY == SPI_FALLING_LEADING_RISING_TRAILING
	SET_BIT(SPCR , SPCR_CPOL) ;
#else
#error "wrong SPI_CLOCK_POLARITY configuration"
#endif




	/*Clock Phase ( Setup & Sample )*/
#if SPI_CLK_PHASE == SAMPLE_LEADING_SETUP_TRAILING
	CLR_BIT(SPCR , SPCR_CPHA) ;

#elif SPI_CLK_PHASE == SETUP_LEADING_SAMPLE_TRAILING
	SET_BIT(SPCR , SPCR_CPHA) ;
#else
#error "wrong SPI_CLOCK_PHASE configuration"
#endif




	/*Clock Rate Selection*/
#if SPI_CLOCK_RATE == FREQ_DIVIDED_BY_2
	CLR_BIT(SPCR , SPCR_SPR0) ;
	CLR_BIT(SPCR , SPCR_SPR1) ;
	SET_BIT(SPSR , SPSR_SPI2X) ;
#elif SPI_CLOCK_RATE == FREQ_DIVIDED_BY_4
	CLR_BIT(SPCR  , SPCR_SPR0) ;
	CLR_BIT(SPCR  , SPCR_SPR1) ;
	CLR_BIT(SPSR  , SPSR_SPI2X) ;
#elif SPI_CLOCK_RATE == FREQ_DIVIDED_BY_8
	SET_BIT(SPCR , SPCR_SPR0) ;
	CLR_BIT(SPCR , SPCR_SPR1) ;
	SET_BIT(SPSR , SPSR_SPI2X) ;
#elif SPI_CLOCK_RATE == FREQ_DIVIDED_BY_16
	SET_BIT(SPCR , SPCR_SPR0) ;
	CLR_BIT(SPCR , SPCR_SPR1) ;
	CLR_BIT(SPSR , SPSR_SPI2X) ;
#elif SPI_CLOCK_RATE == FREQ_DIVIDED_BY_32
	CLR_BIT(SPCR , SPCR_SPR0) ;
	SET_BIT(SPCR , SPCR_SPR1) ;
	SET_BIT(SPSR , SPSR_SPI2X) ;
#elif SPI_CLOCK_RATE == FREQ_DIVIDED_BY_64
	CLR_BIT(SPCR , SPCR_SPR0) ;
	SET_BIT(SPCR , SPCR_SPR1) ;
	CLR_BIT(SPSR , SPSR_SPI2X) ;
#elif SPI_CLOCK_RATE == FREQ_DIVIDED_BY_128
	SET_BIT(SPCR , SPCR_SPR0) ;
	SET_BIT(SPCR , SPCR_SPR1) ;
	CLR_BIT(SPSR , SPSR_SPI2X) ;
#else
#error "wrong SPI_CLOCK_RATE configuration"
#endif






	/*SPI Enable Peripheral*/
#if SPI_ENABLE_MODE == SPI_DISABLED
	CLR_BIT(SPCR , SPCR_SPE) ;
#elif SPI_ENABLE_MODE == SPI_ENABLED
	SET_BIT(SPCR, SPCR_SPE) ;
#else
#error "wrong SPI_ENABLE_MODE configuration"
#endif


}


uint8 SPI_u8Tranceive(uint8 Copy_u8Data)
{

	/*Sending the data to the send register*/
	SPDR = Copy_u8Data;

	/*Waiting for sending/reception completion*/
	while ((GET_BIT(SPSR, SPSR_SPIF)) != 1);



	/*Returning the data*/
	return SPDR;
}
