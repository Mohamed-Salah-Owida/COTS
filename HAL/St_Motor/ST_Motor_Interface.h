/*
 * Steper_Motor_Interface.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Mahmoud
 */

#ifndef STEPER_MOTOR_INTERFACE_H_
#define STEPER_MOTOR_INTERFACE_H_

typedef enum
{
	ROTAT_CW = 1 ,
	ROTAT_CCW = 2
};

// Define a structure to hold motor configuration parameters
typedef struct
{
	uint8 PORT  ;
	uint8 BLUE_PIN  ;
	uint8 PINK_PIN ;
	uint8 YELLOW_PIN ;
	uint8 ORANGE_PIN  ;

}SteperConfig_t;


uint8 Stepper_u8RotateAngle(const SteperConfig_t* Copy_stpStepper , uint8 Copy_u8Direction , uint16 Copy_u8Angle );

#endif /* STEPER_MOTOR_INTERFACE_H_ */
