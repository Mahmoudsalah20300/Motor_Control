/*****************************************************************
 * FILE DESCRIPTION:
----------------------------------------------------------------
 *  file    : TIMER_cfg.h
 *  details : Header file for configuration TIMER Driver.
 ******************************************************************/

#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_

/******************************************
  GLOBAL CONSTANT MACROS
 *******************************************/
#define FCPU_CLOCK    16
/******************************************
  Global Data TYPES AND STRUCTURES
 *******************************************/

/*struct for timer0 initialization configurations*/
typedef struct
{
	TIMER_Mode  Mode;   //mode of TIMER0
	TIMER_OCState  OC0_Action; //action of OC0 pin on interrupt
	TIMER_Prescaler Prescaler; //prescaler value
	TIMER_InterruptState Interrupt_Enable; //interrupt of timer0
}TIMER0_ConfigType;

/*struct for timer1 initialization configurations*/
typedef struct
{
	TIMER1_Mode  Mode;              //mode of TIMER1
	TIMER1_Channel Channel;         //channel A or B
	TIMER_OCState OC1_Action;       //action of OC1 pin on interrupt
	TIMER_Prescaler Prescaler;      //prescaler value
	TIMER1_InterruptState Interrupt_Enable;  //interrupt of timer2
}TIMER1_ConfigType;

/*struct for timer2 initialization configurations*/
typedef struct
{
	TIMER_Mode Mode;     //mode of TIMER2
	TIMER_OCState  OC2_Action;   //action of OC2 pin on interrupt
	TIMER_Prescaler Prescaler;   //prescaler value
	TIMER_InterruptState Interrupt_Enable;  //interrupt of timer2
}TIMER2_ConfigType;

typedef struct
{
	TIMER_Prescaler Prescaler;
	TIMER_ICUTrigger Edge;
}ICU_ConfigType;

#endif /* TIMER_CFG_H_ */
