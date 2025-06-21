/*
 * WDT_Prog.c
 *
 *  Created on: Feb 25, 2025
 *      Author: moham
 */
#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/ErrorType.h"
#include "WDT_reg.h"
#include "WDT_Intrtface.h"

uint8 WDT_voidSet_Time(WDT_Time_t Time)
{
	uint8 Local_u8ErroState=OK;
	switch(Time){
	case WDT_16_3: WDTCR &= 0b1111000 ; break;
	case WDT_32_5: WDTCR &= 0b1111000 ; WDTCR |= 1 ; break;
	case WDT_65  : WDTCR &= 0b1111000 ; WDTCR |= 2 ; break;
	case WDT_0_13: WDTCR &= 0b1111000 ; WDTCR |= 3 ; break;
	case WDT_0_26: WDTCR &= 0b1111000 ; WDTCR |= 4 ; break;
	case WDT_0_52: WDTCR &= 0b1111000 ; WDTCR |= 5 ; break;
	case WDT_1_0 : WDTCR &= 0b1111000 ; WDTCR |= 6 ; break;
	case WDT_2_1 : WDTCR &= 0b1111000 ; WDTCR |= 7 ; break;
	default: Local_u8ErroState = NOK; break;
	}

	return Local_u8ErroState;
}

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}

void WDT_voidDisable(void)
{
	WDTCR =  (1<<WDTCR_WDTOE) | (1<<WDTCR_WDE);  //0b0001100;
	/* Turn off WDT */
	WDTCR = 0x00;
}

void WDT_Reset(void)
{
	__asm volatile("WDR");
}
