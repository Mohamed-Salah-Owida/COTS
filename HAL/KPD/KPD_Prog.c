#include "../../Library/STD_TYPES.h"
#include "../../Library/ErrorType.h"


#include "../../MCAL/DIO/DIO_Interface.h"
#include "KPD_Interface.h"
#include "KPD_Prv.h"
#include "KPD_Cfg.h"




uint8 KPD_u8GetPressedKey(void)
{
	uint8 Local_u8ColIndx  ;
	uint8 Local_u8RowIndx  ;
	uint8 Local_u8PinState ;
	uint8 Local_u8PressedKey = KPD_u8NO_PRESSED_KEY_VAL;


	uint8 Local_au8ColArr[COL_NUM] = { KPD_u8COL0_PIN,KPD_u8COL1_PIN,KPD_u8COL2_PIN,KPD_u8COL3_PIN};
	uint8 Local_au8RowArr[ROW_NUM] = { KPD_u8ROW0_PIN,KPD_u8ROW1_PIN,KPD_u8ROW2_PIN,KPD_u8ROW3_PIN};


	uint8 Local_au8KPDArr[ROW_NUM][COL_NUM] = KPD_au8_BUTTON_ARR;

	/* Activate the column pins */
	for(Local_u8ColIndx = 0 ; Local_u8ColIndx < COL_NUM  ; Local_u8ColIndx++)
	{
		/* Activate the current column */
		DIO_u8SetPinValue(KPD_u8COL_PORT , Local_au8ColArr[Local_u8ColIndx],DIO_u8PINLOW);

		/*Read the row pins */
		for(Local_u8RowIndx = 0 ; Local_u8RowIndx < ROW_NUM ; Local_u8RowIndx++)
		{
			/*Read the current row */
			DIO_u8ReadPinValue(KPD_u8ROW_PORT,Local_au8RowArr[Local_u8RowIndx],&Local_u8PinState);

			if(Local_u8PinState == DIO_u8PINLOW)
			{
				Local_u8PressedKey = Local_au8KPDArr[Local_u8RowIndx][Local_u8ColIndx];


				/* Polling with blocking(waiting) until the key is released  */
				while (Local_u8PinState == DIO_u8PINLOW)
				{
					DIO_u8ReadPinValue(KPD_u8ROW_PORT,Local_au8RowArr[Local_u8RowIndx],&Local_u8PinState);
				}

				return Local_u8PressedKey;
			}

		}

		/*Deactivate the current column */
		DIO_u8SetPinValue(KPD_u8COL_PORT , Local_au8ColArr[Local_u8ColIndx],DIO_u8PINHIGH);

	}

	return Local_u8PressedKey ;
}

