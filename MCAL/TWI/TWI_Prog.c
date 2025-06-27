/*
 * TWI_Prog.c
 *
 *  Created on: Apr 30, 2025
 *      Author: moham
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrorType.h"


#include "TWI_Reg.h"
#include "TWI_Interface.h"
#include "TWI_Prv.h"



/*if the master not addressed send 0 as an argument */
void TWI_voidMasterInit(uint8 Copy_u8Address)
{

	if (Copy_u8Address != 0)
	{
		TWAR = Copy_u8Address << 1u ;
	}
	else
	{
		/*nothing*/
	}


	/*Set SCL frequency to 400kHz with 16Mhz system frequency*/
	/*prescaler = 1 */

	CLR_BIT(TWSR, TWSR_TWPS0);
	CLR_BIT(TWSR, TWSR_TWPS1);
	TWBR = 12u;


	/* TWI Enable Acknowledge Bit*/
	SET_BIT(TWCR , TWCR_TWEA);

	/* TWI Enable Bit*/
	SET_BIT(TWCR,TWCR_TWEN);
}


void TWI_voidSlaveInit(uint8 Copy_u8Address)
{

	/*assign the slave address*/
	TWAR = Copy_u8Address<<1;


	/* TWI Enable Acknowledge Bit*/
	SET_BIT(TWCR , TWCR_TWEA);


	/* TWI Enable Bit*/
	SET_BIT(TWCR,TWCR_TWEN);

}


uint8  TWI_SendStartCondition(void)
{
	uint8 Local_ErrorState = OK ;


	/*Set Start Condition bit*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear The interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait until the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);


	/* Check if the START condition was acknowledged:
	 * - Mask TWSR (TWI Status Register) to extract status bits.
	 * - Compare against START_ACK (expected status after a successful START).
	 */
	if((TWSR & STATUS_BITS_MASK)  != START_ACK)
	{
		Local_ErrorState = NOK ; // Indicate failure if status doesn't match
	}


	return Local_ErrorState ;
}


uint8 TWI_SendRepeatedStart(void)
{
	uint8 Local_ErrorState = OK ;


	/*Set Start Condition bit*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear The interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait until the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);


	/* Check if the START condition was acknowledged:
	 * - Mask TWSR (TWI Status Register) to extract status bits.
	 * - Compare against START_ACK (expected status after a successful START).
	 */
	if((TWSR & STATUS_BITS_MASK)  != START_ACK)
	{
		Local_ErrorState = NOK ; // Indicate failure if status doesn't match
	}


	return Local_ErrorState ;
}


uint8 TWI_SendSlaveAddressWithWrite(uint8 Copy_u8SlaveAddress)
{
	uint8 Local_ErrorState = OK ;


	/*Set the slave address in the 7 MSB in the data register*/
	TWDR = (Copy_u8SlaveAddress<<1);

	/*Clear Bit zero for write request*/
	CLR_BIT(TWDR, 0u);

	/*Clear the start Condition bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear The interrupt flag to start transmission of address*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait until the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if ((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrorState = NOK;
	}


	return Local_ErrorState ;
}




uint8 TWI_SendSlaveAddressWithRead(uint8 Copy_u8SlaveAddress)
{
	uint8 Local_ErrorState = OK ;


	/*Set the slave address in the 7 MSB in the data register*/
	TWDR = (Copy_u8SlaveAddress<<1);

	/*SET Bit zero for Read request*/
	SET_BIT(TWDR, 0u);

	/*Clear the start Condition bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear The interrupt flag to start transmission of address*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait until the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if ((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_ErrorState = NOK;
	}


	return Local_ErrorState ;
}

uint8 TWI_MasterWriteDataByte(uint8 Copy_u8DataByte)
{
	uint8 Local_ErrorState = OK ;

	/*Set the DataByte in the Data Register */
	TWDR = Copy_u8DataByte;


	/*Clear The interrupt flag to start transmission of data*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Wait until the previous action finishes, and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if ((TWSR & STATUS_BITS_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrorState = NOK;
	}


	return Local_ErrorState ;
}

uint8 TWI_MasterReadDataByte(uint8* Copy_pu8DataByte)
{
	uint8 Local_ErrorState = OK ;

	if (Copy_pu8DataByte != NULL)
	{
		/*Clear The interrupt flag to enable slave to send data*/
		SET_BIT(TWCR, TWCR_TWINT);

		/*Wait until the slave writing finish and the interrupt flag is raised again*/
		while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);


		/*Check the status of the bus*/
		if ((TWSR & STATUS_BITS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_ErrorState = NOK;
		}

		else
		{
			/*Reading the bus*/
			*Copy_pu8DataByte = TWDR;
		}


	}

	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}
	return Local_ErrorState ;
}


uint8 TWI_SendStopCondition(void)
{
	uint8 Local_ErrorState = OK ;


	/*Generate stop condition on the bus set bit stop condition */
		SET_BIT(TWCR,TWCR_TWSTO);

		/*Clear the interrupt flag to start the previous operation*/
		SET_BIT(TWCR,TWCR_TWINT);


	return Local_ErrorState ;

}




