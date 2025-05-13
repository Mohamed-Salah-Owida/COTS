#include "../../Library/STD_TYPES.h"
#include "../../Library/ErrorType.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "SW_Interface.h"
#include "SW_Cfg.h"
#include  "SW_Prov.h"

uint8 SW_u8GetState (const SW_CFG_t* Copy_pstConfig, uint8* copy_pu8State )
{

	uint8 Local_u8ErrorState = OK ;
	uint8 Local_u8State  ;

	if(Copy_pstConfig != NULL)
	{
		DIO_u8ReadPinValue(Copy_pstConfig -> PORT , Copy_pstConfig -> PIN ,&Local_u8State);


		if (Copy_pstConfig -> TYPE == INT_Pull_UP   || Copy_pstConfig -> TYPE == EX_Pull_UP )
		{
			if(Local_u8State ==  1 )
			{
				*copy_pu8State = Released ;
			}
			else if (Local_u8State ==  0)
			{
				*copy_pu8State = Pressed ;
			}
			else
			{
				Local_u8ErrorState =NOK ;
			}

		}
		else if ( Copy_pstConfig -> TYPE == EX_Pull_DOWN )
		{
			if(Local_u8State ==  1 )
			{
				*copy_pu8State = Pressed ;
			}
			else if (Local_u8State ==  0)
			{
				*copy_pu8State = Released ;
			}
			else
			{
				Local_u8ErrorState =NOK ;
			}
		}
		else
		{
			Local_u8ErrorState =NOK ;
		}
	}
	else
	{
		Local_u8ErrorState = NOK ;

	}



	return Local_u8ErrorState ;

}


