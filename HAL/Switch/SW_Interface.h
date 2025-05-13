#ifndef SW_INTERFACE_H
#define SW_INTERFACE_H

typedef enum
{
	Released = 0u,
	Pressed  = 1u

}SW_State_t;


typedef enum
{
	EX_Pull_UP = 0u,
	EX_Pull_DOWN = 1u,
	INT_Pull_UP
}SW_TYPE_t;


typedef struct
{
	uint8 PORT ;
	uint8 PIN ;
	SW_TYPE_t TYPE ;
}SW_CFG_t;

uint8 SW_u8GetState (const SW_CFG_t* Copy_pstConfig, uint8* copy_pu8State );








#endif
