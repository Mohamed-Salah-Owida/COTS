/*
 * SPI_Reg.h
 *
 *  Created on: Mar 14, 2025
 *      Author: moham
 */

#ifndef SPI_REG_H_
#define SPI_REG_H_


#define	SPCR				*((volatile uint8*)0X2D)			/*SPI control register*/
#define SPCR_SPIE               7								/*SPI Interrupt Enable*/
#define SPCR_SPE 		      	6								/*SPI enable*/
#define SPCR_DORD               5								/*SPI Data Order Bit*/
#define SPCR_MSTR               4								/*Master & Slave bit*/
#define SPCR_CPOL               3								/*SPI clock polarity bit*/
#define SPCR_CPHA               2								/*SPI clock Phase Bit*/
#define SPCR_SPR1               1								/*Prescaler bit 1*/
#define SPCR_SPR0				0								/*Prescaler bit 0*/

#define SPSR				*((volatile uint8*)0X2E)			/*SPI status register*/
#define SPSR_SPIF				7								/*SPI interrupt flag*/
#define SPSR_WCOL				6								/*Write Collision Flag*/
#define SPSR_SPI2X				0								/*Prescaler bit 2*/


#define SPDR				*((volatile uint8*)0X2F)			/*SPI Data register*/



#endif /* SPI_REG_H_ */
