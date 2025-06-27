/*
 * TWI_Interface.h
 *
 *  Created on: Apr 30, 2025
 *      Author: moham
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


void TWI_voidMasterInit(uint8 Copy_u8Adress);
void TWI_voidSlaveInit(uint8 Copy_u8Adress);

uint8  TWI_SendStartCondition(void);
uint8 TWI_SendRepeatedStart(void);

uint8 TWI_SendSlaveAddressWithWrite(uint8 Copy_u8SlaveAdress);
uint8 TWI_SendSlaveAddressWithRead(uint8 Copy_u8SlaveAdress);


uint8 TWI_MasterWriteDataByte(uint8 Copy_u8DataByte);
uint8 TWI_MasterReadDataByte(uint8* Copy_pu8DataByte);

uint8 TWI_SendStopCondition(void);


#endif /* TWI_INTERFACE_H_ */
