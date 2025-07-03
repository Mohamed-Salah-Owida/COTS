/*
 * EEPROM_Interface.h
 *
 *  Created on: May 1, 2025
 *      Author: moham
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_VoidInit(void);
void EEPROM_VoidWriteDataByte (uint16 Copy_u16LocAddress , uint8 Copy_u8DataByte);
uint8 EEPROM_u8ReadDataByte (uint16 Copy_u16LocAddress);



#endif /* EEPROM_INTERFACE_H_ */
