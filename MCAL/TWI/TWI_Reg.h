/*
 * TWI_Reg.h
 *
 *  Created on: Apr 30, 2025
 *      Author: moham
 */

#ifndef TWI_REG_H_
#define TWI_REG_H_


#define TWBR     		*((volatile uint8 *)0x20)		/*TWI BIT RATE REGISTER*/
#define TWBR_TWBR0		0							/*TWBR Register Bit0 Rate Register*/
#define TWBR_TWBR1		1                           /*TWBR Register Bit1 Rate Register*/
#define TWBR_TWBR2		2                           /*TWBR Register Bit2 Rate Register*/
#define TWBR_TWBR3		3                           /*TWBR Register Bit3 Rate Register*/
#define TWBR_TWBR4		4                           /*TWBR Register Bit4 Rate Register*/
#define TWBR_TWBR5		5                           /*TWBR Register Bit5 Rate Register*/
#define TWBR_TWBR6		6                           /*TWBR Register Bit6 Rate Register*/
#define TWBR_TWBR7		7                           /*TWBR Register Bit7 Rate Register*/


#define TWCR    		*((volatile uint8 *)0x56)		/*TWI Control Register*/
#define TWCR_TWIE    	0                           /*TWI Interrupt Enable*/
#define TWCR_TWEN    	2                           /*TWI Enable Bit*/
#define TWCR_TWWC    	3                           /*TWI STOP Condition Bit*/
#define TWCR_TWSTO   	4                           /*TWI STOP Condition Bit*/
#define TWCR_TWSTA   	5                           /*TWI START Condition Bit*/
#define TWCR_TWEA    	6                           /*TWI Enable Acknowledge Bit*/
#define TWCR_TWINT   	7							/*TWI Interrupt Flag*/




#define TWSR		*((volatile uint8 *)0x21)		/*TWI STATUS REGISTER*/
#define TWSR_TWPS0		0							/*PRESCALER BIT0*/
#define TWSR_TWPS1		1							/*PRESCALER BIT1*/
#define TWSR_TWS3		2							/*TWI Bit3 Status*/
#define TWSR_TWS4		4							/*TWI Bit4 Status*/
#define TWSR_TWS5		5							/*TWI Bit5 Status*/
#define TWSR_TWS6		6							/*TWI Bit6 Status*/
#define TWSR_TWS7		7							/*TWI Bit7 Status*/



#define TWDR		*((volatile uint8 *)0x23)		/*TWI Data Register*/


#define TWAR     		*((volatile uint8 *)0x22)		/*TWI ADDRESS REGISTER*/
#define TWAR_TWGCE		0							/*TWI General Call Recognition Enable Bit*/
#define TWAR_TWA0		1							/*TWI (Slave) Address Bit0 Register*/
#define TWAR_TWA1       2                           /*TWI (Slave) Address Bit1 Register*/
#define TWAR_TWA2       3                           /*TWI (Slave) Address Bit2 Register*/
#define TWAR_TWA3       4                           /*TWI (Slave) Address Bit3 Register*/
#define TWAR_TWA4       5                           /*TWI (Slave) Address Bit4 Register*/
#define TWAR_TWA5       6                           /*TWI (Slave) Address Bit5 Register*/
#define TWAR_TWA6       7                           /*TWI (Slave) Address Bit6 Register*/





#endif /* TWI_REG_H_ */
