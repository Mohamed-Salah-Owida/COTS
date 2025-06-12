/*
 * ULTRASONIC_Prog.c
 *
 *  Created on: Mar 21, 2025
 *      Author: moham
 */
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "TIMER_Interface.h"
#include "ULTRASONIC_Interface.h"
#include "ULTRASONIC_Cfg.h"
#include "util/delay.h"


static void ICU_CallBackFunction(void);


volatile uint16 ICU_Time1 = 0, ICU_Time2 = 0;
volatile uint8 EdgeCounter = 0;
volatile uint16 Distance = 0;



/* Timer1 Configuration Structure for ultrasonic sensor */
Timer1_Cfg_t Ultrasonic = {
		T1_Normal,                     // Normal mode
		T1_CHA_Disconnected_Non,       // Channel A disconnected (not used)
		T1_CHA_Disconnected_Fast,     // Fast PWM  (not used here)
		T1_CHA_Disconnected_Phase,     // Phase correct PWM (not used here)
		CLK_8,                         // Timer clock prescaler set to 8
		ICU_RAISING_EDGE
};





void Ultrasonic_voidInit(void)
{
	/*Set Trigger Pin Direction output*/
	DIO_u8SetPinDirection(TriggerPort, TriggerPin, DIO_u8PIN_OUTPUT);
	/*Set echo Pin Direction input (ICP)*/
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN6, DIO_u8PIN_INPUT);


	/* if need ultrasonic only in this timer  than -> configuration file Selected normal mode
	 * if need ultrasonic with anything(Servo) in this timer  than -> configuration file Selected FastPWM top OCR1A and Connect the servo in OCR1B as 0 to 180 angle
	*/

     Timer1_u8Init(&Ultrasonic);

	ICU_voidInit(&Ultrasonic);

	/*Set call back get reading the ICU for ultrasonic*/
	Timers_SetCallBack(T1_InpCapT_Int, &ICU_CallBackFunction);

}

uint16 Ultrasonic_u16GetDistance(void)
{

	EdgeCounter = 0;
	ICU_Time1 = 0;
	ICU_Time2 = 0;
	Distance = 0;

	/* Reset Timer1 & Enable ICU interrupt*/
	Timer1_VoidSetVal(0);
	ICU_voidEnableInterrupt();


	/* Send Trigger Pulse (High for 10us) */
	DIO_u8SetPinValue(TriggerPort, TriggerPin, DIO_u8PINHIGH);
	_delay_us(10);
	DIO_u8SetPinValue(TriggerPort,TriggerPin, DIO_u8PINLOW);


	/* Wait for Echo Signal Processing */
	while (EdgeCounter < 2);

	/* Disable ICU interrupt after measurement */
	ICU_voidDisableInterrupt();

	/* Calculate Distance in centimeters */
	/* The ultrasonic wave travels to the object and back, so we divide by 2 */
	/* The speed of sound is 0.0343 cm/µs, so the one-way distance formula is: */
	/* Distance (cm) = (Time in µs × 0.0343) / 2 */
	/* Since the timer increments every 0.5 µs, the distance formula must be adjusted:*/
	/*Simplifying this gives: Distance =( Time / 116)    Instead of Distance = (Time / 58)  (which is used when Timer1 ticks every 1 µs)*/


	Distance = (ICU_Time2 - ICU_Time1) / 116;   // Adjusted for 0.5µs timer tick

	return Distance;



}


void ICU_CallBackFunction(void)
{
	if (EdgeCounter == 0)
	{
		/* First Rising Edge Detected */
		ICU_Time1 =ICU_u16GetReadingInputCaptureUnit();
		ICU_u8SetTriggerEdge(ICU_FALLING_EDGE);
		EdgeCounter++;
	}
	else if (EdgeCounter == 1)
	{
		/* Falling Edge Detected */
		ICU_Time2 =ICU_u16GetReadingInputCaptureUnit();
		ICU_u8SetTriggerEdge(ICU_RAISING_EDGE);
		EdgeCounter++;
	}



}


