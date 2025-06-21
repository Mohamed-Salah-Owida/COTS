/*
 * WDT_Intrtface.h
 *
 *  Created on: Feb 25, 2025
 *      Author: moham
 */

#ifndef WDT_INTRTFACE_H_
#define WDT_INTRTFACE_H_

#include "STD_TYPES.h"
typedef enum{
	WDT_16_3,
	WDT_32_5,
	WDT_65,
	WDT_0_13,
	WDT_0_26,
	WDT_0_52,
	WDT_1_0,
	WDT_2_1

}WDT_Time_t;




uint8 WDT_voidSet_Time(WDT_Time_t Time);
void WDT_voidEnable(void);
void WDT_voidDisable(void);
void WDT_Reset(void);




#endif /* WDT_INTRTFACE_H_ */
