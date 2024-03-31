/*****************************************************************
* FILE DESCRIPTION:
----------------------------------------------------------------
 *  file    : TIMER_Lcfg.c
 *  details : Source file for link time configurations TIMER Driver.
 *****************************************************************/

/******************************************
  INCLUDES
 *******************************************/
#include "TIMER_types.h"
#include "TIMER_cfg.h"


/******************************************
  Global Data
 *******************************************/
const TIMER0_ConfigType TIMER0_Config ={TIMER_CTC_MODE,OC_DISCONNECTED,TIMER_1024_PRESCALER,TIMER_COMPARE_MATCH_INT_ENABLE};
const TIMER1_ConfigType TIMER1_Config ={TIMER1_NORMAL_MODE,TIMER1_CHANNEL_A,OC_DISCONNECTED,TIMER_NO_PRESCALER,TIMER1_INPUT_CAPTURE_INT_ENABLE};
