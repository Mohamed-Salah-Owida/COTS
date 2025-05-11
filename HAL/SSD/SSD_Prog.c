
#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include"../../Library/ErrorType.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "SSD_Interface.h"



uint8 SSD_u8ON(const SSD_cfg_t* Copy_PstCfg )
{
	uint8 Local_u8ErrorState = OK ;

	if (Copy_PstCfg != NULL)
	{

		if( (Copy_PstCfg -> Type  == ANODE) ||  (Copy_PstCfg -> Type  == ETA_KIT))
		{
			DIO_u8SetPinValue(Copy_PstCfg ->En_Port , Copy_PstCfg ->En_Pin , DIO_u8PINHIGH);
		}
		else if (Copy_PstCfg -> Type  == CATHODE)
		{
			DIO_u8SetPinValue(Copy_PstCfg ->En_Port , Copy_PstCfg ->En_Pin , DIO_u8PINLOW);
		}
		else
		{
			Local_u8ErrorState = NOK ;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;
	}

	return Local_u8ErrorState  ;

}





uint8 SSD_u8OFF(const SSD_cfg_t* Copy_PstCfg )
{
	uint8 Local_u8ErrorState = OK ;

	if (Copy_PstCfg != NULL)
	{

		if( (Copy_PstCfg -> Type  == ANODE) ||  (Copy_PstCfg -> Type  == ETA_KIT))
		{
			DIO_u8SetPinValue(Copy_PstCfg ->En_Port , Copy_PstCfg ->En_Pin , DIO_u8PINLOW);
		}
		else if (Copy_PstCfg -> Type  == CATHODE)
		{
			DIO_u8SetPinValue(Copy_PstCfg ->En_Port , Copy_PstCfg ->En_Pin , DIO_u8PINHIGH);
		}
		else
		{
			Local_u8ErrorState = NOK ;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR ;
	}

	return Local_u8ErrorState  ;


}

uint8 SSD_u8SetNumber(const SSD_cfg_t* Copy_PstCfg , uint8 Copy_u8Number)
{

	uint8 Local_u8ErrorState = OK ;



	if (Copy_u8Number < 9)
	{

		if (Copy_PstCfg != NULL)
		{
			uint8 Local_au8SSD_BCD[10]={
					// (Segments:G, F, E, D, C, B, A)
					0b00111111, // 0
					0b00110000, // 1
					0b01011011, // 2
					0b01001111, // 3
					0b01100110, // 4
					0b01101101, // 5
					0b01111101, // 6
					0b00000111, // 7
					0b01111111, // 8
					0b01101111  // 9
			};

			if(Copy_PstCfg->Type == ANODE)
			{
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_a ,~(GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,0u)));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_b ,~(GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,1u)));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_c ,~(GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,2u)));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_d ,~(GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,3u)));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_e ,~(GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,4u)));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_f ,~(GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,5u)));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_g ,~(GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,6u)));
			}

			else if((Copy_PstCfg->Type == CATHODE) || (Copy_PstCfg->Type == ETA_KIT ))
			{
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_a ,GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,0u));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_b ,GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,1u));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_c ,GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,2u));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_d ,GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,3u));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_e ,GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,4u));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_f ,GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,5u));
				DIO_u8SetPinValue(Copy_PstCfg->PORT,Copy_PstCfg->Led_g ,GET_BIT(Local_au8SSD_BCD[Copy_u8Number] ,6u));

			}
			else
			{
				Local_u8ErrorState =NOK ;
			}

		}
		else
		{
			Local_u8ErrorState = NULL_PTR_ERR ;
		}

	}
	else
	{
		Local_u8ErrorState =NOK ;
	}

	return Local_u8ErrorState  ;


}


