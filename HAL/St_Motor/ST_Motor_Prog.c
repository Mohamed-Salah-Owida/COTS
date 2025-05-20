/*
 * Steper_Motor_Prog.c
 *
 *  Created on: Dec 2, 2023
 *      Author: Mahmoud
 */
#include "../../Library/STD_TYPES.h"
#include "../../Library/ErrorType.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include <util/delay.h>
#include "ST_Motor_Config.h"
#include "ST_Motor_Interface.h"

uint8 Stepper_u8RotateAngle(const SteperConfig_t* Copy_stpStepper , uint8 Copy_u8Direction , uint16 Copy_u8Angle )
{
	uint8 Local_u8ErrorState = OK ; // Local variable to store error state
	uint16 Local_u16Steps;
	uint16 Local_u16LoopCounter ;

	if(Copy_stpStepper != NULL)
	{
		Local_u16Steps = (uint16)( (  ( (uint32)Copy_u8Angle ) * (2048UL)  ) /360UL );

		if(Copy_u8Direction == ROTAT_CCW)
		{
			for(Local_u16LoopCounter = 0 ; Local_u16LoopCounter < Local_u16Steps ; Local_u16LoopCounter++)
			{
				if(Local_u16LoopCounter % 4 == 0 )
				{
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> BLUE_PIN,DIO_u8PINLOW);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> PINK_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> YELLOW_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> ORANGE_PIN,DIO_u8PINHIGH);
					_delay_ms(3);
				}
				else if(Local_u16LoopCounter % 4 == 1 )
				{
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> BLUE_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> PINK_PIN,DIO_u8PINLOW);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> YELLOW_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> ORANGE_PIN,DIO_u8PINHIGH);
					_delay_ms(3);

				}
				else if(Local_u16LoopCounter % 4 == 2 )
				{
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> BLUE_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> PINK_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> YELLOW_PIN,DIO_u8PINLOW);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> ORANGE_PIN,DIO_u8PINHIGH);
					_delay_ms(3);
				}
				else if(Local_u16LoopCounter % 4 == 3  )
				{
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> BLUE_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> PINK_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> YELLOW_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> ORANGE_PIN,DIO_u8PINLOW);
					_delay_ms(3);
				}

			}
		}

		else if(ROTAT_CW)
		{
			for(Local_u16LoopCounter = 0 ; Local_u16LoopCounter < Local_u16Steps ; Local_u16LoopCounter++)
			{
				if(Local_u16LoopCounter % 4 == 0 )
				{
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> BLUE_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> PINK_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> YELLOW_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> ORANGE_PIN,DIO_u8PINLOW);
					_delay_ms(3);
				}
				else if(Local_u16LoopCounter % 4 == 1 )
				{
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> BLUE_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> PINK_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> YELLOW_PIN,DIO_u8PINLOW);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> ORANGE_PIN,DIO_u8PINHIGH);
					_delay_ms(3);

				}
				else if(Local_u16LoopCounter % 4 == 2 )
				{
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> BLUE_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> PINK_PIN,DIO_u8PINLOW);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> YELLOW_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> ORANGE_PIN,DIO_u8PINHIGH);
					_delay_ms(3);
				}
				else if(Local_u16LoopCounter % 4 == 3  )
				{
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> BLUE_PIN,DIO_u8PINLOW);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> PINK_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> YELLOW_PIN,DIO_u8PINHIGH);
					DIO_u8SetPinValue(Copy_stpStepper -> PORT,Copy_stpStepper -> ORANGE_PIN,DIO_u8PINHIGH);
					_delay_ms(3);
				}

			}
		}
		//s


	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;// Set error state to NULL pointer error
	}
	return Local_u8ErrorState ;// Return the error state
}







