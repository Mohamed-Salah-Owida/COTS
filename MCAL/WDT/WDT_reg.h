/*
 * WDT_reg.h
 *
 *  Created on: Feb 25, 2025
 *      Author: moham
 */

#ifndef WDT_REG_H_
#define WDT_REG_H_


#define WDTCR					  *((volatile uint16 *)0x41)
#define WDTCR_WDP0				  0
#define WDTCR_WDP1				  1
#define WDTCR_WDP2				  2
#define WDTCR_WDE				  3
#define WDTCR_WDTOE				  4


#endif /* WDT_REG_H_ */
