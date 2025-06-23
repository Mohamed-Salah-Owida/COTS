/*
 * USART_Interface.h
 *
 *  Created on: Mar 8, 2025
 *      Author: moham
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


#define MAX_RECEIVE_BUFFER_SIZE     64u


void USART_Init(void);
void USART_VoidSendByte(uint8 Copy_u8Data);
uint8 USART_u8SendStringAsynch(const char* Copy_pchString, void (* Copy_PvNotificationFunction)(void));
uint8 USART_u8ReceiveStringAsynch( char* Copy_pchString, void (* Copy_PvNotificationFunction)(void));
uint8 USART_u8RecieveByte(void);

#endif /* USART_INTERFACE_H_ */
