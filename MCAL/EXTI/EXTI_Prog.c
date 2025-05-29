#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/ErrorType.h"


#include"EXTI_reg.h"
#include"EXTI_interface.h"
#include"EXTI_prv.h"
#include"EXTI_cfg.h"



static void(*EXTICallBack[3])(void)={0}; /*pointer to array function for INT0 & INT1 & INT2*/




void EXTI_VoidInit(void)
{
#if INT0_SENSE_CTRL == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC01);
#elif INT0_SENSE_CTRL == EXTI_ON_CHANGE
	SET_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC01);
#elif INT0_SENSE_CTRL == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC01);
#elif INT0_SENSE_CTRL == EXTI_RAISING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC01);

#else
#error WRONG INT0_SENSE_CTRL configuration option
#endif

#if INT1_SENSE_CTRL == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC10);
	CLR_BIT(MCUCR, MCUCR_ISC11);
#elif INT1_SENSE_CTRL == EXTI_ON_CHANGE
	SET_BIT(MCUCR, MCUCR_ISC10);
	CLR_BIT(MCUCR, MCUCR_ISC11);
#elif INT1_SENSE_CTRL == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR, MCUCR_ISC10);
	SET_BIT(MCUCR, MCUCR_ISC11);
#elif INT1_SENSE_CTRL == EXTI_RAISING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC10);
	SET_BIT(MCUCR, MCUCR_ISC11);

#else
#error WRONG INT1_SENSE_CTRL  configuration option
#endif




#if INT2_SENSE_CTRL == EXTI_FALLING_EDGE
	CLR_BIT(MCUCSR, MCUCSR_ISC2);
#elif INT2_SENSE_CTRL == EXTI_RAISING_EDGE
	SET_BIT(MCUCSR, MCUCSR_ISC2);

#else
#error WRONG INT2_SENSE_CTRL  configuration option
#endif

#if INT0_INIT_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT0);
#elif INT0_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT0);
#else
#error WRONG INT0_INIT_STATE  configuration option
#endif


#if INT1_INIT_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT1);
#elif INT1_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT1);
#else
#error WRONG INT1_INIT_STATE  configuration option
#endif


#if INT2_INIT_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT2);
#elif INT2_INIT_STATE == ENABLED
	SET_BIT(GICR, GICR_INT2);
#else
#error WRONG INT2_INIT_STATE  configuration option
#endif

}
uint8 EXTI_u8SetSenseCtrl(IntChannel_t Copy_IntCh,SenseCtrl_t Copy_SenseCtrl)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_IntCh == INT0)
	{
		switch(Copy_SenseCtrl)
		{
		case(LOW_LEVEL): CLR_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case(ON_CHANGE): SET_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case(FALLING_EDGE): CLR_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		case(RAISING_EDGE): SET_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		default: Local_u8ErrorState = NOK; break;
		}
	}
	else if(Copy_IntCh == INT1)
	{
		switch(Copy_SenseCtrl)
		{
		case(LOW_LEVEL): CLR_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case(ON_CHANGE): SET_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case(FALLING_EDGE): CLR_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		case(RAISING_EDGE): SET_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		default: Local_u8ErrorState = NOK; break;
		}

	}
	else if(Copy_IntCh == INT2)
	{
		switch(Copy_SenseCtrl)
		{
		case(FALLING_EDGE): CLR_BIT(MCUCSR, MCUCSR_ISC2); break;
		case(RAISING_EDGE): SET_BIT(MCUCSR, MCUCSR_ISC2); break;
		default: Local_u8ErrorState = NOK; break;
		}
	}
	return Local_u8ErrorState;


}
uint8 EXTI_u8EnableIntChannel(IntChannel_t Copy_IntCh)
{
	uint8 Local_u8ErrorState = OK;
	switch(Copy_IntCh)
	{
	case(INT0): SET_BIT(GICR,GICR_INT0); break;
	case(INT1): SET_BIT(GICR,GICR_INT1); break;
	case(INT2): SET_BIT(GICR,GICR_INT2); break;
	default:Local_u8ErrorState = NOK; break;
	}
	return Local_u8ErrorState;

}
uint8 EXTI_u8DisableIntChannel(IntChannel_t Copy_IntCh)
{
	uint8 Local_u8ErrorState = OK;
	switch(Copy_IntCh)
	{
	case(INT0): CLR_BIT(GICR,GICR_INT0); break;
	case(INT1): CLR_BIT(GICR,GICR_INT1); break;
	case(INT2): CLR_BIT(GICR,GICR_INT2); break;
	default:Local_u8ErrorState = NOK; break;
	}
	return Local_u8ErrorState;

}


uint8 EXTI_u8SetCallBack(IntChannel_t Copy_IntCh, void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState= OK;

	if(Copy_pvCallBackFunc !=NULL)
	{

		EXTICallBack[Copy_IntCh]=Copy_pvCallBackFunc;

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


/*INT0 ISR Call back*/
__attribute__((signal)) void __vector_1 (void);
void __vector_1 (void)
{
	if(EXTICallBack[INT0]!=NULL)
	{
		EXTICallBack[INT0]();
	}


}


/*INT1 ISR Call back*/
__attribute__((signal)) void __vector_2 (void);
void __vector_2 (void)
{
	if(EXTICallBack[INT1]!=NULL)
	{
		EXTICallBack[INT1]();
	}
}


/*INT2 ISR Call back*/
__attribute__((signal)) void __vector_3 (void);
void __vector_3 (void)
{
	if(EXTICallBack[INT2]!=NULL)
	{
		EXTICallBack[INT2]();
	}
}


