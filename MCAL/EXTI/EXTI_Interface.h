/*
 * EXTI_Interface.h
 *
 *  Created on: Jan 11, 2025
 *      Author: moham
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

typedef enum
{
	INT0,
	INT1,
	INT2
}IntChannel_t;

typedef enum
{
	LOW_LEVEL , ON_CHANGE , FALLING_EDGE, RAISING_EDGE
}SenseCtrl_t;

void EXTI_VoidInit(void);

uint8 EXTI_u8SetSenseCtrl(IntChannel_t Copy_IntCh,SenseCtrl_t Copy_SenseCtrl);
uint8 EXTI_u8EnableIntChannel(IntChannel_t Copy_IntCh);
uint8 EXTI_u8DisableIntChannel(IntChannel_t Copy_IntCh);

uint8 EXTI_u8SetCallBack(IntChannel_t Copy_IntCh, void(*Copy_pvCallBackFunc)(void));


uint8 EXTI_u8SetCallBack(IntChannel_t Copy_IntCh, void(*Copy_pvCallBackFunc)(void));



#endif /* EXTI_INTERFACE_H_ */
