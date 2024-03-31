/*
 * main.c
 *
 *  Created on: Feb 19, 2023
 *      Author: m_hsa
 */
#include <util/delay.h>

#include "STD_TYPES.h"
#include "Led_int.h"
#include "PB_int.h"
#include "Dio_int.h"
#include "Port_int.h"
#include "CLCD_int.h"
#include "KPD_int.h"
#include "EXTI_int.h"
#include "GIE_int.h"
#include "TIMER_int.h"
#include "ULTRASONIC_int.h"

void LED (void);
void PWM(void);
extern const Port_Configtype Port_ConfigArr[PORT_PINS_CONFIG_ARR_SIZE];
extern const EXTI_ConfigType EXTI_ConfigArr[EXTI_PINS_CONFIG_ARR_SIZE]; 

void main(void)
{
	u8 Local_u8Temperature;

	MPort_voidInit(Port_ConfigArr);
	MGIE_voidEnable();
	HCLCD_voidInit();



	while(1)
	{
		Local_u8Temperature = HTEMP_u8GetTemperature();

		HCLCD_voidSendCommand(0x1);

		HCLCD_voidIntegerToString(Local_u8Temperature);
		HCLCD_voidSendString(" C");
		_delay_ms(1000);

	}
}

void LED (void)
{
	HLED_voidToggle(LED_BLUE);
}


void PWM(void)
{
	static u8 Local_u8Counter = 0;
	Local_u8Counter++;
	if(Local_u8Counter == 15)
	{
		/* Set pin to low */
		HLED_voidTurnOff(LED_BLUE);
	}
	else if(Local_u8Counter == 20)
	{
		/* Set pin to high */
		HLED_voidTurnOn(LED_BLUE);
		Local_u8Counter = 0;
	}
}
