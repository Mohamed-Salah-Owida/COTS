/*
 * USART_Prog.c
 *
 *  Created on: Mar 8, 2025
 *      Author: moham
 */
 #include "../../Library/STD_TYPES.h"
 #include "../../Library/BIT_MATH.h"
#include "../../Library/ErrorType.h"
#include "USART_reg.h"
#include "USART_Cfg.h"
#include "USART_Prv.h"
#include "USART_interface.h"



/* Private variables */
static volatile uint8 Global_u8USART_StateT = USART_IDLE ;
static volatile uint8 Global_u8USART_StateR = USART_IDLE ;

static volatile uint8 Global_u8IndexT = 0;                  /* Current transmission index */
static volatile uint8 Global_u8IndexR = 0;                  /* Current transmission index */

static void (*Global_pvNotificationFuncT)(void) = NULL;  /* Notification callback */
static void (*Global_pvNotificationFuncR)(void) = NULL;  /* Notification callback */

static const char* Global_pchTransmitString = NULL;        /* Pointer to transmit string */
static  volatile char* Global_pchReceiveString = NULL;        /* Pointer to Receive string */



void USART_Init(void)
{
	/*UCSRC configurations will  hold in this variable   to assigned with the bit selection in one operation */
	uint8 Local_u8UCSRC_Cfg = 0;
	uint16 Local_u16UBRR   = 0;

	/*Calculating & Setting the Baud Rate*/
	Local_u16UBRR = ((uint16)((SYSTEM_FREQUENCY / (16ul * USART_BAUD_RATE)) - 1));

	UBRRH = (uint8)(Local_u16UBRR >> 8);
	UBRRL = (uint8)(Local_u16UBRR);


	/*Setting the Transmission mode*/
#if USART_MODE == ASYNCHRONOUS
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UMSEL);
#elif USART_MODE == SYNCHRONOUS
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UMSEL);
#else
#error Wrong configuratoin of transmission mode
#endif


	/*Selecting the data size*/
#if	USART_CHAR_SIZE == FIVE_BITS
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);

#elif USART_CHAR_SIZE == SIX_BITS
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);

#elif USART_CHAR_SIZE == SEVEN_BITS
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);

#elif USART_CHAR_SIZE == EIGHT_BITS
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);
#elif USART_CHAR_SIZE == NINE_BITS
	SET_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCSZ0);
#else
#error Wrong configuratoin of the Charachter size.
#endif



	/*Setting the Parity mode*/
#if USART_PARITY_MODE == NO_PARITY
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM1);
#elif USART_PARITY_MODE == EVEN_PARITY
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM1);
#elif USART_PARITY_MODE == ODD_PARITY
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UPM1);
#else
#error Wrong configuratoin of Parity mode.
#endif


	/*Setting the stop bit mode*/
#if USART_STOP_BIT_MODE == SINGLE_STOP_BIT
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_USBS);
#elif USART_STOP_BIT_MODE == TWO_STOP_BITS
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_USBS);
#else
#error Wrong configuratoin of STOP_BOT_MODE
#endif



	/*Setting the CLK Polarity*/
#if (USART_MODE == SYNCHRONOUS && USART_CLK_POLARITY == TXRISING_RXFALLING)
	CLR_BIT(Local_u8UCSRC_Cfg, UCSRC_UCPOL);
#elif (USART_MODE == SYNCHRONOUS && USART_PARITY_MODE == TXFALLING_RXRISING)
	SET_BIT(Local_u8UCSRC_Cfg, UCSRC_UCPOL);
#endif




	/*Writing the configurations in the UCSRC Register  and set the selection bit in one operation*/
	UCSRC = (1 << UCSRC_URSEL) | Local_u8UCSRC_Cfg;





	/* RX Complete Interrupt Configuration */
#if USART_RX_INTERRUPT_ENABLE == DISABLE
	CLR_BIT(UCSRB, UCSRB_RXCIE);    /* Disable RX Complete Interrupt */
#elif USART_RX_INTERRUPT_ENABLE == ENABLE
	SET_BIT(UCSRB, UCSRB_RXCIE);    /* Enable RX Complete Interrupt */
#else
#error "Wrong USART_RX_INTERRUPT_ENABLE configuration"
#endif

	/* TX Complete Interrupt Configuration */
#if USART_TX_COMPLETE_INTERRUPT == DISABLE
	CLR_BIT(UCSRB, UCSRB_TXCIE);    /* Disable TX Complete Interrupt */
#elif USART_TX_COMPLETE_INTERRUPT == ENABLE
	SET_BIT(UCSRB, UCSRB_TXCIE);    /* Enable TX Complete Interrupt */
#else
#error "Wrong USART_TX_COMPLETE_INTERRUPT configuration"
#endif

	/* Data Register Empty Interrupt Configuration */
#if USART_UDRE_INTERRUPT_ENABLE == DISABLE
	CLR_BIT(UCSRB, UCSRB_UDRIE);    /* Disable UDRE Interrupt */
#elif USART_UDRE_INTERRUPT_ENABLE == ENABLE
	SET_BIT(UCSRB, UCSRB_UDRIE);    /* Enable UDRE Interrupt */
#else
#error "Wrong USART_UDRE_INTERRUPT_ENABLE configuration"
#endif



	/*Adjusting the initial states of the Receiver & Transmitter*/
#if USART_RECEIVER_ENABLE ==  RX_ENABLED
	SET_BIT(UCSRB, UCSRB_RXEN);
#elif USART_RECEIVER_ENABLE == RX_DISABLED
	CLR_BIT(UCSRB, UCSRB_RXEN);
#else
#error Wrong configuratoin of RX_INIT_STATE
#endif

#if USART_TRANSMITTER_ENABLE ==  TX_ENABLED
	SET_BIT(UCSRB, UCSRB_TXEN);
#elif USART_TRANSMITTER_ENABLE == TX_DISABLED
	CLR_BIT(UCSRB, UCSRB_TXEN);
#else
#error Wrong configuratoin of TX_INIT_STATE
#endif



}


void USART_VoidSendByte(uint8 Copy_u8Data)
{
	/*To transmit the signal , UDRE Flag must set to one First in the UCSRA Register*/
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR = Copy_u8Data;
}


uint8 USART_u8RecieveByte(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}


uint8 USART_u8SendStringAsynch(const char* Copy_pchString, void (* Copy_PvNotificationFunction)(void))
{
	uint8 Local_u8ErrorState  = OK;
	/* Validate parameters */
	if(Copy_pchString == NULL || Copy_PvNotificationFunction == NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	/* Check if UART is busy */
	else if(Global_u8USART_StateT == USART_BUSY)
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	else
	{
		/* Set USART to busy state */
		Global_u8USART_StateT = USART_BUSY ;

		/* Store string information */
		Global_pchTransmitString = Copy_pchString;
		Global_pvNotificationFuncT = Copy_PvNotificationFunction;

		/* Initialize index to start transmitting from first character */
		Global_u8IndexT = 0;


		/* Enable USART Data Register Empty Interrupt to handle asynchronous transmission */
		SET_BIT(UCSRB, UCSRB_UDRIE);
	}

	return Local_u8ErrorState ;

}


/*********************************
 * USART Data Register Empty ISR *
 *********************************/
void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
	if(Global_u8USART_StateT == USART_BUSY && Global_pchTransmitString != NULL)
	{
		if(Global_pchTransmitString[Global_u8IndexT] != '\0')
		{

			/* Send current byte */
			UDR = Global_pchTransmitString[Global_u8IndexT];
			Global_u8IndexT++;
		}
		else
		{
			/* Disable UDRE interrupt */
			CLR_BIT(UCSRB, UCSRB_UDRIE);
			/* Reset transmission variables */
			Global_pchTransmitString = NULL;
			Global_u8IndexT = 0;
			Global_u8USART_StateT = USART_IDLE;
			/* Call notification function */
			if(Global_pvNotificationFuncT != NULL)
			{
				Global_pvNotificationFuncT();
			}
		}
	}

}




uint8 USART_u8ReceiveStringAsynch(char* Copy_pchString, void (* Copy_PvNotificationFunction)(void))
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pchString == NULL || Copy_PvNotificationFunction == NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	/* Check if UART is busy */
	else if(Global_u8USART_StateR == USART_BUSY)
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	else
	{
		/* Set USART to busy state */
		Global_u8USART_StateR = USART_BUSY;

		/* Store string information */
		Global_pchReceiveString = Copy_pchString;
		Global_pvNotificationFuncR = Copy_PvNotificationFunction;

		/* Initialize index to start receiving from first character */
		Global_u8IndexR = 0;

		/* Enable USART RX Complete Interrupt */
		SET_BIT(UCSRB, UCSRB_RXCIE);
	}

	return Local_u8ErrorState;
}


/*********************************
 * USART RX complete ISR *
 *********************************/
void __vector_13 (void) __attribute__ ((signal));
void __vector_13 (void)
{
	if(Global_u8USART_StateR == USART_BUSY && Global_pchReceiveString != NULL)
	{
		char receivedChar = UDR; // Read received character

		/* Check if end of string or buffer limit */
		if(receivedChar == '\r' || receivedChar == '\n' || Global_u8IndexR >= (  MAX_RECEIVE_BUFFER_SIZE - 1 ))
		{
			/* Null terminate the string */
			Global_pchReceiveString[Global_u8IndexR] = '\0';

			/* Reset index */
			Global_u8IndexR = 0;

			/* USART is now IDLE */
			Global_u8USART_StateR = USART_IDLE;

			/* Disable USART RX complete Interrupt */
			CLR_BIT(UCSRB, UCSRB_RXCIE);

			/* Call notification function */
			if(Global_pvNotificationFuncR != NULL)
			{
				Global_pvNotificationFuncR();
			}
		}
		else if (Global_u8IndexR <( MAX_RECEIVE_BUFFER_SIZE - 1)) // Prevent overflow
		{
			/* Store received character */
			Global_pchReceiveString[Global_u8IndexR] = receivedChar;

			/* Increment data index */
			Global_u8IndexR++;
		}
	}
}
