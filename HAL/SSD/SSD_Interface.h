#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

/*Configurations:
 * 1) SSD_u8Type options:   1- ANODE
 * 							2- CATHODE
 * 							3- ETAKIT
 * */


typedef enum
{
	ANODE   = 1u,
	CATHODE = 2u,
	ETA_KIT = 3u
}SSD_TYPE_t;



typedef struct
{

	SSD_TYPE_t Type ;

	uint8 PORT;

	uint8 Led_a;
	uint8 Led_b;
	uint8 Led_c;
	uint8 Led_d;
	uint8 Led_e;
	uint8 Led_f;
	uint8 Led_g;


	uint8 En_Port;
	uint8 En_Pin ;

}SSD_cfg_t;



uint8 SSD_u8ON(const SSD_cfg_t* Copy_PstCfg );

uint8 SSD_u8OFF(const SSD_cfg_t* Copy_PstCfg );

uint8 SSD_u8SetNumber(const SSD_cfg_t* Copy_PstCfg , uint8 Copy_u8Number);






#endif
