#ifndef BUZZER_INTERFACE_H
#define BUZZER_INTERFACE_H

typedef enum
{
	ACTIVE_H = 1u,
	ACTIVE_L = 2u
}BUZZER_Activity_t;

typedef struct
{
	uint8 PORT ;
	uint8 PIN  ;
	BUZZER_Activity_t ActivityType;

}BUZZER_cfg_t;


void BUZZER_VoidInit(const BUZZER_cfg_t* Copy_pstCfg);
uint8 BUZZER_u8SetON(const BUZZER_cfg_t* Copy_pstCfg);
uint8 BUZZER_u8SetOFF(const BUZZER_cfg_t* Copy_pstCfg);
uint8 BUZZER_u8Toggle(const BUZZER_cfg_t* Copy_pstCfg);



#endif
