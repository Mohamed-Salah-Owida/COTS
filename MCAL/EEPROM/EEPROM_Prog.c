/*
 * EEPROM_Prog.c
 *
 *  Created on: May 1, 2025
 *      Author: moham
 */
#include "STD_TYPES.h"
#include "ErrorType.h"
#include "util/delay.h"


#include "TWI_Interface.h"
#include "EEPROM_Interface.h"
#include "EEPROM_Cfg.h"
#include "EEPROM_Prv.h"


/*initialization of TWI Peripheral  */
void EEPROM_VoidInit(void)
{
	TWI_voidMasterInit(0);
}


void EEPROM_VoidWriteDataByte (uint16 Copy_u16LocAddress , uint8 Copy_u8DataByte)
{
	/*Get the 7-bits slave Address  */
	uint8  Local_u8SlaveAddress = (EEPROM_FIXED_ADDRESS | (A2_Connection <<2u ) | ((Copy_u16LocAddress>>8) & 0x3));

	/*Send Start condition */
	TWI_SendStartCondition();

	/*Send the 7 bit SLA with write request */
	TWI_SendSlaveAddressWithWrite(Local_u8SlaveAddress);

	/*Send the rest 8 bits of location address */
	TWI_MasterWriteDataByte((uint8) Copy_u16LocAddress);

	/*Send the data  */
	TWI_MasterWriteDataByte(Copy_u8DataByte);

	/*Send Stop Condition*/
	TWI_SendStopCondition();

	/*Wait until the write cycle is finished */
	_delay_ms(10);
}


uint8 EEPROM_u8ReadDataByte (uint16 Copy_u16LocAddress)
{
	uint8 Local_u8DataByte =0;

	/*Get the 7-bits slave Address  */
	uint8  Local_u8SlaveAddress = EEPROM_FIXED_ADDRESS | (A2_Connection <<2 ) | (((uint8)(Copy_u16LocAddress>>8)) & 0x3);

	/*Send Start condition */
	TWI_SendStartCondition();

	/*Send the 7 bit SLA with write request */
	TWI_SendSlaveAddressWithWrite(Local_u8SlaveAddress);

	/*Send the rest 8 bits of location address */
	TWI_MasterWriteDataByte((uint8) Copy_u16LocAddress);

	/*Sending repeated start to change write request to read request*/
	TWI_SendRepeatedStart();

	/*Sending SLA again after the repeated start but with read request*/
	TWI_SendSlaveAddressWithRead(Local_u8SlaveAddress);

	/*Reading from the data byte from the memory*/
	TWI_MasterReadDataByte(&Local_u8DataByte);

	/*Sending stop condition*/
	TWI_SendStopCondition();

	return Local_u8DataByte;
}



