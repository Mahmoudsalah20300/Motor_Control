/*****************************************************************
 * FILE DESCRIPTION:
----------------------------------------------------------------
 *  file    : TIMER0_prog.c
 *  details : Source file for TIMER0 Driver.
 *****************************************************************/


/******************************************
  INCLUDES
 *******************************************/
#include "STD_TYPES.h"
#include <util/delay.h>
#include "Dio_int.h"
#include "TIMER_int.h"
#include "GIE_int.h"
#include "ULTRASONIC_priv.h"
#include "ULTRASONIC_cfg.h"
#include "ULTRASONIC_types.h"
#include "ULTRASONIC_int.h"

/******************************************
  Local Data
 *******************************************/

volatile static u8 g_edgeCount = 0;
volatile static u16 g_echo_HighTime = 0;

/******************************************
  Global Data
 *******************************************/



/******************************************
  Local Functions  body
 *******************************************/
static void Ultrasonic_Trigger(void);

/******************************************
  Global Functions body
 *******************************************/
void HUltrasonic_voidinit(void)
{
	ICU_ConfigType Local_xConfig = {TIMER_8_PRESCALER,RISING};

	MTIMER1_voidICUInit(&Local_xConfig);

	MTIMER_enSetCallBack(TIMER1_ICU,Ultrasonic_edgeProcessing);

}

static void Ultrasonic_Trigger(void)
{
	MDIO_voidSetPinValue(ULTRASONIC_TRIGGER_PIN, DIO_HIGH);
	_delay_us(TRIGGER_PULSE_DURATION);
	MDIO_voidSetPinValue(ULTRASONIC_TRIGGER_PIN, DIO_LOW);
}

u16 HULTRASONIC_u16GetDistance(void)
{
	Ultrasonic_Trigger();

	return (0.017 * g_echo_HighTime);
}

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;

	if(g_edgeCount == 1)
	{
		/* Clear the timer counter register to start measurements from the first detected rising edge */
		MTIMER1_voidClearTimer();

		/* Detect falling edge at the Echo pin */
		MTIMER1_voidICUSetTrigger(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the high time (pulse time) generated by the ultrasonic sensor */
		g_echo_HighTime = MTIMER1_u16ICUTakeReading();

		/* Detect falling edge at the Echo pin */
		MTIMER1_voidICUSetTrigger(RISING);

		/* Clear the timer counter register to start measurements again */
		MTIMER1_voidClearTimer();

		g_edgeCount = 0;
	}
}