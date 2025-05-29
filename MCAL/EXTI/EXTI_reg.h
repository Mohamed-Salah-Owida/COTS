/*
 * EXTI_reg.h
 *
 *  Created on: Jan 11, 2025
 *      Author: moham
 */

#ifndef EXTI_REG_H_
#define EXTI_REG_H_


#define GICR  *((volatile uint8*)0x5B)  /*Global interrupt control register*/
#define GICR_INT0    6u                 /*INT0 bit*/
#define GICR_INT1    7u                  /*INT1 bit*/
#define GICR_INT2    5u                   /*INT2 bit*/

#define MCUCR *((volatile uint8*)0x55)   /*MCU Control register*/
#define MCUCR_ISC00 0u /*Int0 sense control bit0*/
#define MCUCR_ISC01 1u /*Int0 sense control bit1*/
#define MCUCR_ISC10 2u /*Int1 sense control bit0*/
#define MCUCR_ISC11 3u /*Int0 sense control bit1*/

#define MCUCSR *((volatile uint8*)0x54)/*MCU control and status register*/
#define MCUCSR_ISC2 6u                 /*Int2 sense control bit*/

#define GIFR  *((volatile uint8*)0x5A)  /*Global interrupt flag Register*/
#define GIFR_INTF1   7u;
#define GIFR_INTF0   6u;
#define GIFR_INTF2   5u;













#endif /* EXTI_REG_H_ */
