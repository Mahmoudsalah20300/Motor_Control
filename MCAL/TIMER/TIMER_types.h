/***************************************************************
 * FILE DESCRIPTION:
----------------------------------------------------------------
 *  file    : TIMER_types.h
 *  details : Declare the types in TIMER Driver
 *****************************************************************/

#ifndef TIMER_TYPES_H_
#define TIMER_TYPES_H_

/******************************************
  INCLUDES
 *******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
 *******************************************/


/******************************************
  GLOBAL FUNCTIONS MACROS
 *******************************************/

/******************************************
  Global Data TYPES AND STRUCTURES
 *******************************************/
//timer channels
typedef enum
{
	Timer0,
	Timer1,
	Timer
}TIMER_channel;

//timer1 channels
typedef enum
{
	TIMER1_CHANNEL_A,
	TIMER1_CHANNEL_B
}TIMER1_Channel;

typedef enum
{
	TIMER0_DISABLE,
	TIMER0_ENABLE
}TIMRE0_InitState;

//timer 0 modes
typedef enum
{
	TIMER_NORMAL_MODE,
	TIMER_PHASE_CORRECT_PWM,
	TIMER_CTC_MODE,
	TIMER_FAST_PWM,
}TIMER_Mode;

//timer 1 modes
typedef enum
{
	TIMER1_NORMAL_MODE,
	TIMER1_PHASE_CORRECT_8_BIT,
	TIMER1_PHASE_CORRECT_9_BIT,
	TIMER1_PHASE_CORRECT_10_BIT,
	TIMER1_CTC1_MODE,
	TIMER1_FAST_PWM_8_BIT,
	TIMER1_FAST_PWM_9_BIT,
	TIMER1_FAST_PWM_10_BIT,
	TIMER1_PHASE_CORRECT_FREQUENCY_CORRECT1,
	TIMER1_PHASE_CORRECT_FREQUENCY_CORRECT2,
	TIMER1_PHASE_CORRECT1,
	TIMER1_PHASE_CORRECT2,
	TIMER1_CTC2_MODE,
	TIMER1_RESERVED,
	TIMER1_FAST_PWM1,
	TIMER1_FAST_PWM2,
}TIMER1_Mode;




//timer0|2 interrupt sources state
typedef enum
{
	TIMER_OVER_FLOW_INT_ENABLE=1,     //Enable over flow interrupt
	TIMER_OVER_FLOW_INT_DISABLE,      //Disable over flow interrupt
	TIMER_COMPARE_MATCH_INT_ENABLE,   //Enable compare match interrupt
	TIMER_COMPARE_MATCH_INT_DISABLE,   //Disable compare match interrupt
	TIMER_INPUT_CAPTURE_INT_ENABLE,   //Enable input capture interrupt
	TIMER_INPUT_CAPTURE_INT_DISABLE   //Disable input capture interrupt
}TIMER_InterruptState;

//timer1 interrupt sources state
typedef enum
{
	TIMER1_OVER_FLOW_INT_ENABLE=1,       //Enable over flow interrupt
	TIMER1_OVER_FLOW_INT_DISABLE,        //Disable over flow interrupt
	TIMER1_COMPARE_MATCH_A_INT_ENABLE,   //Enable compare match on channel A interrupt
	TIMER1_COMPARE_MATCH_A_INT_DISABLE,  //Disable compare match on channel A interrupt
	TIMER1_COMPARE_MATCH_B_INT_ENABLE,   //Enable compare match on channel B interrupt
	TIMER1_COMPARE_MATCH_B_INT_DISABLE,   //Disable compare match on channel B interrupt
	TIMER1_INPUT_CAPTURE_INT_ENABLE,      //Enable inputer capture interrupt
	TIMER1_INPUT_CAPTURE_INT_DISABLE      //Disable input capture interrupt
}TIMER1_InterruptState;

//timer clock prescaler values
typedef enum
{
	TIMER_NO_CLOCK,                        //no input clock(stop peripheral)
	TIMER_NO_PRESCALER,                    //tick time = 1/16 us
	TIMER_8_PRESCALER,                     //tick time = .5 us
	TIMER_64_PRESACLER,                    //tick time = 4 us
	TIMER_256_PRESCALER,                   //tick time = 16 us
	TIMER_1024_PRESCALER,                  //tick time = 64 us
	TIMER_EXT_CLK_FALLING,                 //external clock on T0 pin , clock on falling edge
	TIMER_EXT_CLK_RISING                   //external clock on T0 pin , clock on rising edge
}TIMER_Prescaler;




//action on OC0|OC1A|OC1B|OC2 pins on over flow or compare match
typedef enum
{
	OC_DISCONNECTED,   //OC pin disconnected
	OC_TOGGLE,         //toggle on compare match or over flow
	OC_CLEAR,          //clear on compare match or over flow
	OC_SET             //set on compare match or over flow
}TIMER_OCState;


//interrupt sources of timer
typedef enum
{
	TIMER0_OVER_FLOW=1,
	TIMER0_COMPARE_MATCH,
	TIMER1_OVER_FLOW,
	TIMER1_COMPARE_MATCH_A,
	TIMER1_COMPARE_MATCH_B,
	TIMER2_OVER_FLOW,
	TIMER2_COMPARE_MATCH,
	TIMER0_ICU,
	TIMER1_ICU,
	TIMER2_ICU
}TIMER_InterruptSource;


typedef enum
{
	FALLING,
	RISING
}TIMER_ICUTrigger;



#endif /* TIMER_TYPES_H_ */
