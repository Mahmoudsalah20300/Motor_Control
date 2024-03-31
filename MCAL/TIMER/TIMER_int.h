/*****************************************************************
* FILE DESCRIPTION:
----------------------------------------------------------------
*  file    : TIMER_int.h
*  details : Header file for interface IIMER Driver.
*****************************************************************/
#ifndef TIMER_INT_H_
#define TIMER_INT_H_

/******************************************
  INCLUDES
*******************************************/
#include "STD_TYPES.h"
#include "TIMER_types.h"
#include "TIMER_cfg.h"

/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/


/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL DATA TYPES AND STRUCTURES
*******************************************/

/******************************************
  GLOBAL DATA PROTOTYPES
*******************************************/

/******************************************
   GLOBAL FUNCTIONS PROTOTYPES
*******************************************/

/******************************************
  syntax : Error_State TIMER0_enInit(const TIMER0_ConfigType * Copy_xConfig)

  Description : this function is to initialize TIMER/COUNTER0
  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER0_enInit(const TIMER0_ConfigType * Copy_xConfig);

/******************************************
  syntax : Error_State TIMER1_enInit(const TIMER1_ConfigType * Copy_xConfig)

  Description : this function is to initialize TIMER/COUNTER1
  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER1_enInit(const TIMER1_ConfigType * Copy_xConfig);

/******************************************
  syntax : Error_State TIMER2_enInit(const TIMER2_ConfigType * Copy_xConfig)

  Description : this function is to initialize TIMER/COUNTER2

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : void
******************************************/
Error_State MTIMER2_enInit(const TIMER2_ConfigType * Copy_xConfig);

/******************************************
  syntax : Error_State TIMER0_enStart(const TIMER0_ConfigType * Copy_xConfig)

  Description : this function is to start TIMER/COUNTER0

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER0_enStart(const TIMER0_ConfigType * Copy_xConfig);

/******************************************
  syntax : Error_State TIMER1_enStart(const TIMER1_ConfigType * Copy_xConfig)

  Description : this function is to start TIMER/COUNTER1

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER1_enStart(const TIMER1_ConfigType * Copy_xConfig);

/******************************************
  syntax : Error_State TIMER0_enStart(const TIMER0_ConfigType * Copy_xConfig)

  Description : this function is to start TIMER/COUNTER2

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER2_enStart(const TIMER2_ConfigType * Copy_xConfig);

/******************************************
  syntax : Error_State TIMER0_enStop(void)

  Description : Stop the Timer0

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : void
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER0_enStop(void);

/******************************************
  syntax : Error_State TIMER1_voidStop(void)

  Description : Stop the Timer1

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : void
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER1_enStop(void);

/******************************************
  syntax : Error_State TIMER2_voidStop(void)

  Description : Stop the Timer2

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : void
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER2_enStop(void);

/******************************************
  syntax : Error_State TIMER0_enGetCounts(void)

  Description : Stop the Timer0

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : void
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER0_enGetCounts(u8 * Copy_u8CounterValue);


/******************************************
  syntax : Error_State TIMER0_enSetDelayTimeMilliSec(const TIMER0_ConfigType * Copy_xConfig , u8 Copy_u8MilliSec)

  Description : Delay MilliSec Function

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : Number of MilliSec and the pointer to the timer0 configuration type
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER0_enSetDelayTimeMilliSec(const TIMER0_ConfigType * Copy_xConfig , u16 Copy_u16MilliSec);


/******************************************
  syntax : Error_State MTIMER0_enEnableInt(const TIMER0_ConfigType * Copy_xConfig)

  Description : function to enable the timer0 interrupt.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to the struct configuration of timer0
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER0_enEnableInt(const TIMER0_ConfigType * Copy_xConfig);

Error_State MTIMER1_enEnableInt(const TIMER1_ConfigType * Copy_xConfig);

/******************************************
  syntax : Error_State MTIMER0_MTIMER0_enDisableInt(const TIMER0_ConfigType * Copy_xConfig)

  Description : function to Disable the timer0 interrupt.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to the struct configuration of timer0
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER0_enDisableInt(const TIMER0_ConfigType * Copy_xConfig);

/******************************************
  syntax : Error_State MTIMER_enSetCallBack(void (TIMER_InterruptSource Copy_enEvent , *Copy_pvCallBackFunc)(void))

  Description : function to Set the Callback Function.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to the callback function
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER_enSetCallBack(TIMER_InterruptSource Copy_u8Event , void (*Copy_pvCallBackFunc)(void));

/******************************************
  syntax : Error_State MTIMER0_enSetFastPWM(u8 Copy_u8Frequency , u8 Copy_u8DutyCycle);

  Description : function to set the fast PWM signal.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : frequency , the duty cycle and the OC pin state.
  parameters (out) : none
  Return Value     : Error_State
******************************************/
Error_State MTIMER0_enSetFastPWM(u8 Copy_u8Frequency , u8 Copy_u8DutyCycle , TIMER_OCState Copy_enOCState);

/******************************************
  syntax : void MTIMER1_voidICUSetTrigger(TIMER_ICUTrigger Copy_enTrigger)

  Description : function to set the icu trigger for timer1.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : trigger mode
  parameters (out) : none
  Return Value     : void
 ******************************************/
void MTIMER1_voidICUSetTrigger(TIMER_ICUTrigger Copy_enTrigger);

u16 MTIMER1_u16ICUTakeReading(void);


void MTIMER1_voidICUInit(const ICU_ConfigType * Copy_xConfig);

void MTIMER1_voidICUsetEdgeDetectionType(const TIMER_ICUTrigger Copy_enEdgeType);

#endif /* TIMER_INT_H_ */
