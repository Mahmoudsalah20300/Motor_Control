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
#include "BIT_MATH.h"
#include "Mcu_HW.h"

#include "TIMER_types.h"
#include "TIMER_priv.h"
#include "TIMER_cfg.h"
#include "TIMER_int.h"



/******************************************
  Local Data
 *******************************************/

static u32 Number_Of_OverFlow=0;
static u32 Number_Of_Remaining_Time=0;
static u32 Number_Of_CompareMatch = 0;

/******************************************
  Global Data
 *******************************************/



/******************************************
  Local Functions  body
 *******************************************/
/*Global pointer to function to set call back*/
void (*OverFlow0ptr)(void) = NULL;          //global pointer to function for timer0 over flow ISR
void (*CompareMatch0ptr)(void) = NULL;      //global pointer to function for timer0 compare match ISR

void (*OverFlow1ptr)(void) = NULL;          //global pointer to function for timer1 over flow ISR
void (*CompareMatch1Aptr)(void) = NULL;     //global pointer to function for timer1 channel A compare match ISR
void (*CompareMatch1Bptr)(void) = NULL;     //global pointer to function for timer1 channel b compare match ISR

void (*OverFlow2ptr)(void) = NULL;          //global pointer to function for timer2 over flow ISR
void (*CompareMatch2ptr)(void) = NULL;      //global pointer to function for timer2 compare match IS
void (*ICUptr)(void) = NULL;                //global pointer to function for timer1 ICU

/******************************************
  Global Functions body
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
Error_State MTIMER0_enInit(const TIMER0_ConfigType * Copy_xConfig)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;
	if(Copy_xConfig != NULL)
	{

		/*resetting TCCR0 register*/
		TCCR0 = 0 ;

		/********************************Setting mode of timer0********************************/
		/*checking for correct input of timer mode*/
		if(((Copy_xConfig->Mode)>=TIMER_NORMAL_MODE) && ((Copy_xConfig->Mode)<=TIMER_FAST_PWM))
		{
			/*switching over timer modes*/
			switch(Copy_xConfig->Mode)
			{
			//in case of normal mode(over flow mode)
			case TIMER_NORMAL_MODE:
				CLR_BIT(TCCR0 , TCCR0_WGM00);
				CLR_BIT(TCCR0 , TCCR0_WGM01);
				break;
				//in case of phase correct pwm
			case TIMER_PHASE_CORRECT_PWM:
				SET_BIT(TCCR0,TCCR0_WGM00);
				SET_BIT(TCCR0,TCCR0_WGM01);
				break;
				//in case of compare match mode
			case TIMER_CTC_MODE:
				CLR_BIT(TCCR0,TCCR0_WGM00);
				SET_BIT(TCCR0,TCCR0_WGM01);
				break;
				//in case of fast pwm mode
			case TIMER_FAST_PWM:
				SET_BIT(TCCR0,TCCR0_WGM00);
				SET_BIT(TCCR0,TCCR0_WGM01);
				break;
			default:
				/* Do nothing */
				break;
			}
		}
		/*in case of wrong input of timer mode*/
		else
		{
			Local_enErrorState = OUT_OF_RANGE_VALUE;
		}

		/********************************Setting action of OC0 pin*****************************************/
		/*checking for correct input of OC0 action*/
		if(((Copy_xConfig->OC0_Action)>= OC_DISCONNECTED) && ((Copy_xConfig->OC0_Action) <=OC_SET))
		{
			TCCR0 &= OC_ACTION_MASK;    //clearing OC0 bits to receive new values
			TCCR0 |= ((Copy_xConfig->OC0_Action)<<4);  //setting action of OC0 pin
		}
		/*in case of wrong input of OC0 action*/
		else
		{
			Local_enErrorState = OUT_OF_RANGE_VALUE;
		}
	}
	else
	{
		Local_enErrorState = NULL_POINTER;
	}
	return Local_enErrorState;
}

/******************************************
  syntax : Error_State TIMER1_enInit(const TIMER1_ConfigType * Copy_xConfig)

  Description : this function is to initialize TIMER/COUNTER1
  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER1_enInit(const TIMER1_ConfigType * Copy_xConfig)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;

	if(Copy_xConfig != NULL)
	{
		/*resetting TCCR1A and TCCR1B register*/
		TCCR1A = 0;
		TCCR1B = 0;

		/********************************Setting mode of timer1********************************/

		/*checking for correct input of timer mode*/
		if(((Copy_xConfig->Mode)>=TIMER1_NORMAL_MODE)&&((Copy_xConfig->Mode)<=TIMER1_FAST_PWM2))
		{
			/*switching over timer modes*/
			switch(Copy_xConfig->Mode)
			{
			//in case of normal mode(over flow mode)
			case TIMER1_NORMAL_MODE:
				CLR_BIT(TCCR1A,TCCR1A_WGM10);
				CLR_BIT(TCCR1A,TCCR1A_WGM11);
				CLR_BIT(TCCR1B,TCCR1B_WGM12);
				CLR_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of phase correct pwm 8 bit mode
			case TIMER1_PHASE_CORRECT_8_BIT:
				SET_BIT(TCCR1A,TCCR1A_WGM10);
				CLR_BIT(TCCR1A,TCCR1A_WGM11);
				CLR_BIT(TCCR1B,TCCR1B_WGM12);
				CLR_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of phase correct pwm 9 bit mode
			case TIMER1_PHASE_CORRECT_9_BIT:
				CLR_BIT(TCCR1A,TCCR1A_WGM10);
				SET_BIT(TCCR1A,TCCR1A_WGM11);
				CLR_BIT(TCCR1B,TCCR1B_WGM12);
				CLR_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of phase correct pwm 10 bit mode
			case TIMER1_PHASE_CORRECT_10_BIT:
				SET_BIT(TCCR1A,TCCR1A_WGM10);
				SET_BIT(TCCR1A,TCCR1A_WGM11);
				CLR_BIT(TCCR1B,TCCR1B_WGM12);
				CLR_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of compare match mode 1
			case TIMER1_CTC1_MODE:
				CLR_BIT(TCCR1A,TCCR1A_WGM10);
				CLR_BIT(TCCR1A,TCCR1A_WGM11);
				SET_BIT(TCCR1B,TCCR1B_WGM12);
				CLR_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of fast PWM 8 bit
			case TIMER1_FAST_PWM_8_BIT:
				SET_BIT(TCCR1A,TCCR1A_WGM10);
				CLR_BIT(TCCR1A,TCCR1A_WGM11);
				SET_BIT(TCCR1B,TCCR1B_WGM12);
				CLR_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of fast PWM 9 bit
			case TIMER1_FAST_PWM_9_BIT:
				CLR_BIT(TCCR1A,TCCR1A_WGM10);
				SET_BIT(TCCR1A,TCCR1A_WGM11);
				SET_BIT(TCCR1B,TCCR1B_WGM12);
				CLR_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of fast PWM 10 bit
			case TIMER1_FAST_PWM_10_BIT:
				SET_BIT(TCCR1A,TCCR1A_WGM10);
				SET_BIT(TCCR1A,TCCR1A_WGM11);
				SET_BIT(TCCR1B,TCCR1B_WGM12);
				CLR_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of phase and frequency correct mode 1
			case TIMER1_PHASE_CORRECT_FREQUENCY_CORRECT1:
				CLR_BIT(TCCR1A,TCCR1A_WGM10);
				CLR_BIT(TCCR1A,TCCR1A_WGM11);
				CLR_BIT(TCCR1B,TCCR1B_WGM12);
				SET_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of phase and frequency correct mode 2
			case TIMER1_PHASE_CORRECT_FREQUENCY_CORRECT2:
				SET_BIT(TCCR1A,TCCR1A_WGM10);
				CLR_BIT(TCCR1A,TCCR1A_WGM11);
				CLR_BIT(TCCR1B,TCCR1B_WGM12);
				SET_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of phase correct mode 1
			case TIMER1_PHASE_CORRECT1:
				CLR_BIT(TCCR1A,TCCR1A_WGM10);
				SET_BIT(TCCR1A,TCCR1A_WGM11);
				CLR_BIT(TCCR1B,TCCR1B_WGM12);
				SET_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of phase correct mode 2
			case TIMER1_PHASE_CORRECT2:
				SET_BIT(TCCR1A,TCCR1A_WGM10);
				SET_BIT(TCCR1A,TCCR1A_WGM11);
				CLR_BIT(TCCR1B,TCCR1B_WGM12);
				SET_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of compare match mode 2
			case TIMER1_CTC2_MODE:
				CLR_BIT(TCCR1A,TCCR1A_WGM10);
				CLR_BIT(TCCR1A,TCCR1A_WGM11);
				SET_BIT(TCCR1B,TCCR1B_WGM12);
				SET_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of fast pwm mode 1
			case TIMER1_FAST_PWM1:
				CLR_BIT(TCCR1A,TCCR1A_WGM10);
				SET_BIT(TCCR1A,TCCR1A_WGM11);
				SET_BIT(TCCR1B,TCCR1B_WGM12);
				SET_BIT(TCCR1B,TCCR1B_WGM13);
				break;
				//in case of fast pwm mode 2
			case TIMER1_FAST_PWM2:
				SET_BIT(TCCR1A,TCCR1A_WGM10);
				SET_BIT(TCCR1A,TCCR1A_WGM11);
				SET_BIT(TCCR1B,TCCR1B_WGM12);
				SET_BIT(TCCR1B,TCCR1B_WGM13);
				break;
			default:
				/* Do nothing */
				break;
			}
		}
		/*in case of wrong input of timer mode*/
		else
		{
			Local_enErrorState = OUT_OF_RANGE_VALUE;
		}


		/********************************Setting action of OC1 pin*****************************************/

		if(Copy_xConfig->Channel == TIMER1_CHANNEL_A || Copy_xConfig->Channel == TIMER1_CHANNEL_B)
		{
			/*switching over channels*/
			switch(Copy_xConfig->Channel)
			{

			case TIMER1_CHANNEL_A:

				/*switching over actions of OC1 A */
				switch(Copy_xConfig->OC1_Action)
				{
				//OC1A disconnected
				case OC_DISCONNECTED:
					CLR_BIT(TCCR1A,TCCR1A_COM1A0);
					CLR_BIT(TCCR1A,TCCR1A_COM1A1);
					break;
					//OC1A toggle on over flow or compare match
				case OC_TOGGLE:
					SET_BIT(TCCR1A,TCCR1A_COM1A0);
					CLR_BIT(TCCR1A,TCCR1A_COM1A1);
					break;
					//OC1A clear on over flow or compare match
				case OC_CLEAR:
					CLR_BIT(TCCR1A,TCCR1A_COM1A0);
					SET_BIT(TCCR1A,TCCR1A_COM1A1);
					break;
					//OC1A set on over flow or compare match
				case OC_SET:
					SET_BIT(TCCR1A,TCCR1A_COM1A0);
					SET_BIT(TCCR1A,TCCR1A_COM1A1);
					break;
				default:
					Local_enErrorState = OUT_OF_RANGE_VALUE;
					break;
				}
				/*breaking from case of channel A*/
				break;

				case TIMER1_CHANNEL_B:

					/*switching over actions of OC1 B */
					switch(Copy_xConfig->OC1_Action)
					{
					//OC1B disconnected
					case OC_DISCONNECTED:
						CLR_BIT(TCCR1A,TCCR1A_COM1B0);
						CLR_BIT(TCCR1A,TCCR1A_COM1B1);
						break;
						//OC1A toggle on over flow or compare match
					case OC_TOGGLE:
						SET_BIT(TCCR1A,TCCR1A_COM1B0);
						CLR_BIT(TCCR1A,TCCR1A_COM1B1);
						break;
						//OC1A clear on over flow or compare match
					case OC_CLEAR:
						CLR_BIT(TCCR1A,TCCR1A_COM1B0);
						SET_BIT(TCCR1A,TCCR1A_COM1B1);
						break;
						//OC1A set on over flow or compare match
					case OC_SET:
						SET_BIT(TCCR1A,TCCR1A_COM1B0);
						SET_BIT(TCCR1A,TCCR1A_COM1B1);
						break;
					default:
						Local_enErrorState = OUT_OF_RANGE_VALUE;
						break;
					}
					/*breaking from case of channel B*/
					break;
			}
		}
		/*in case of wrong input for timer1 channel*/
		else
		{
			Local_enErrorState = OUT_OF_RANGE_VALUE;
		}
	}
	else
	{
		Local_enErrorState = NULL_POINTER;
	}
	return Local_enErrorState;
}

/******************************************
  syntax : Error_State TIMER2_enInit(const TIMER2_ConfigType * Copy_xConfig)

  Description : this function is to initialize TIMER/COUNTER2

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : void
 ******************************************/
Error_State MTIMER2_enInit(const TIMER2_ConfigType * Copy_xConfig)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;

	if(Copy_xConfig != NULL)
	{

		/*resetting TCCR2 register*/
		TCCR2 = 0;

		/********************************Setting mode of timer2********************************/

		/*checking for correct input of timer mode*/
		if(((Copy_xConfig->Mode)>=TIMER_NORMAL_MODE) && ((Copy_xConfig->Mode)<=TIMER_FAST_PWM))
		{
			/*switching over timer modes*/
			switch(Copy_xConfig->Mode)
			{
			//in case of normal mode(over flow mode)
			case TIMER_NORMAL_MODE:
				CLR_BIT(TCCR2,TCCR2_WGM20);
				CLR_BIT(TCCR2,TCCR2_WGM21);
				break;
				//in case of phase correct pwm
			case TIMER_PHASE_CORRECT_PWM:
				SET_BIT(TCCR2,TCCR2_WGM20);
				CLR_BIT(TCCR2,TCCR2_WGM21);
				break;
				//in case of compare match mode
			case TIMER_CTC_MODE:
				CLR_BIT(TCCR2,TCCR2_WGM20);
				SET_BIT(TCCR2,TCCR2_WGM21);
				break;
				//in case of fast pwm mode
			case TIMER_FAST_PWM:
				SET_BIT(TCCR2,TCCR2_WGM20);
				SET_BIT(TCCR2,TCCR2_WGM21);
				break;
			default:
				Local_enErrorState = OUT_OF_RANGE_VALUE;
				break;
			}
		}
		/*in case of wrong input of timer mode*/
		else
		{
			Local_enErrorState = OUT_OF_RANGE_VALUE;
		}

		/********************************Setting action of OC2 pin*****************************************/

		/*checking for correct input of OC2 action*/
		if(((Copy_xConfig->OC2_Action)>=OC_DISCONNECTED) && ((Copy_xConfig->OC2_Action)<=OC_SET))
		{
			TCCR2 &= OC_ACTION_MASK;     //clearing OC1 bits to receive new values
			TCCR2 |= ((Copy_xConfig->OC2_Action)>>4);  //setting action of OC1 pin
		}
		/*in case of wrong input of OC1 action*/
		else
		{
			Local_enErrorState =OUT_OF_RANGE_VALUE;
		}
	}
	else
	{
		Local_enErrorState = NULL_POINTER;
	}

	return Local_enErrorState;
}


/******************************************
  syntax : Error_State TIMER0_enStart(const TIMER0_ConfigType * Copy_xConfig)

  Description : this function is to start TIMER/COUNTER0

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER0_enStart(const TIMER0_ConfigType * Copy_xConfig)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;
	if(Copy_xConfig == NULL)
	{
		Local_enErrorState =NULL_POINTER;
	}
	else
	{

		/********************************Setting prescaler*********************************/

		/*checking for correct input for prescaler*/
		if(((Copy_xConfig->Prescaler)>=TIMER_NO_PRESCALER) && ((Copy_xConfig->Prescaler)<=TIMER_EXT_CLK_RISING))
		{
			TCCR0 &= PRESCALER_MASK;    //clearing clock select bits to receive new values
			TCCR0 |= Copy_xConfig->Prescaler; //setting prescaler to run the timer
		}
		/*in case of wrong input of prescaler*/
		else
		{
			Local_enErrorState = OUT_OF_RANGE_VALUE;
		}
	}

	return Local_enErrorState;
}


/******************************************
  syntax : Error_State TIMER1_enStart(const TIMER1_ConfigType * Copy_xConfig)

  Description : this function is to start TIMER/COUNTER1

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER1_enStart(const TIMER1_ConfigType * Copy_xConfig)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;
	if(Copy_xConfig == NULL)
	{
		Local_enErrorState =NULL_POINTER;
	}
	else
	{
		/********************************Setting prescaler*********************************/

		/*checking for correct input for prescaler*/
		if(((Copy_xConfig->Prescaler)>=TIMER_NO_PRESCALER) && ((Copy_xConfig->Prescaler)<=TIMER_EXT_CLK_RISING))
		{
			TCCR1B &= PRESCALER_MASK;    //clearing clock select bits to receive new values
			TCCR1B |= Copy_xConfig->Prescaler; //setting prescaler to run the timer
		}
		/*in case of wrong input of prescaler*/
		else
		{
			Local_enErrorState = OUT_OF_RANGE_VALUE;
		}
	}

	return Local_enErrorState;
}

/******************************************
  syntax : Error_State TIMER2_enStart(const TIMER2_ConfigType * Copy_xConfig)

  Description : this function is to start TIMER/COUNTER2

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to struct of initialization configurations
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER2_enStart(const TIMER2_ConfigType * Copy_xConfig)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;
	if(Copy_xConfig == NULL)
	{
		Local_enErrorState =NULL_POINTER;
	}
	else
	{
		/********************************Setting prescaler*********************************/

		/*checking for correct input for prescaler*/
		if(((Copy_xConfig->Prescaler)>=TIMER_NO_PRESCALER) && ((Copy_xConfig->Prescaler)<=TIMER_EXT_CLK_RISING))
		{
			TCCR0 &= PRESCALER_MASK;    //clearing clock select bits to receive new values
			TCCR0 |= Copy_xConfig->Prescaler; //setting prescaler to run the timer
		}
		/*in case of wrong input of prescaler*/
		else
		{
			Local_enErrorState = OUT_OF_RANGE_VALUE;
		}
	}

	return Local_enErrorState;
}

/******************************************
  syntax : Error_State TIMER0_voidStop(void)

  Description : Stop the Timer0

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : void
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER0_enStop(void)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;
	TCNT0 = 0;
	OCR0  = 0;
	TCCR0 = 0;  //clearing prescaler bits
	return Local_enErrorState;
}

/******************************************
  syntax : Error_State TIMER1_voidStop(void)

  Description : Stop the Timer1

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : void
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER1_enStop(void)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	//clearing prescaler bits
	TCCR1A = 0;
	TCCR1B = 0;
	return Local_enErrorState;
}

/******************************************
  syntax : Error_State TIMER2_voidStop(void)

  Description : Stop the Timer2

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : void
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER2_enStop(void)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;
	TCNT2 = 0;
	OCR2  = 0;
	//clearing prescaler bits
	TCCR2 = 0;
	return Local_enErrorState;
}

/******************************************
  syntax : Error_State TIMER0_enGetCounts(u8 * Copy_u8CounterValue)

  Description : Stop the Timer0

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : u8 * Copy_u8CounterValue
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER0_enGetCounts(u8 * Copy_u8CounterValue)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;
	*Copy_u8CounterValue = Number_Of_OverFlow*255+ TCNT0;
	return Local_enErrorState;
}

Error_State MTIMER0_enSetDelayTimeMilliSec(const TIMER0_ConfigType * Copy_xConfig , u16 Copy_u16MilliSec)
{
	/*local variable for error checking*/
	Error_State Local_enErrorState = NO_ERROR;

	u16 Local_u16PrescalerArr[5] = {1,8,64,256,1024};

	f32 Local_f32TickTime = (f32) Local_u16PrescalerArr[(Copy_xConfig->Prescaler)-1] / FCPU_CLOCK;

	u32 Local_u32DesiredTicks= ((Copy_u16MilliSec*1000) / Local_f32TickTime);

	if(Copy_xConfig->Mode == TIMER_NORMAL_MODE)
	{
		Number_Of_OverFlow = (Local_u32DesiredTicks / MAX_NUMBER_OF_OVERFLOW);

		Number_Of_Remaining_Time = (Local_u32DesiredTicks % MAX_NUMBER_OF_OVERFLOW);

		if(Number_Of_Remaining_Time != 0)
		{
			TCNT0 = MAX_NUMBER_OF_OVERFLOW - Number_Of_Remaining_Time;
			Number_Of_OverFlow++;
		}
	}
	else if(Copy_xConfig->Mode == TIMER_CTC_MODE)
	{
		u8 Local_u8Value = MAX_NUMBER_OF_OVERFLOW - 1;

		while(Local_u32DesiredTicks % Local_u8Value)
		{
			Local_u8Value--;
		}

		Number_Of_CompareMatch = Local_u32DesiredTicks / Local_u8Value;
		OCR0 = Local_u8Value;
	}
	else
	{
		Local_enErrorState = OUT_OF_RANGE_VALUE;
	}

	return Local_enErrorState;
}

/******************************************
  syntax : Error_State MTIMER0_enEnableInt(const TIMER0_ConfigType * Copy_xConfig)

  Description : function to enable the timer0 interrupt.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to the struct configuration of timer0
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER0_enEnableInt(const TIMER0_ConfigType * Copy_xConfig)
{
	/*local variable for error checking*/
	Error_State Local_enErrorSate = NO_ERROR;

	/*******************************Setting interrupt****************************************/

	/*checking for correct input of interrupt status*/
	if(Copy_xConfig->Interrupt_Enable == TIMER_OVER_FLOW_INT_ENABLE || Copy_xConfig->Interrupt_Enable == TIMER_COMPARE_MATCH_INT_ENABLE)
	{
		/*switching over interrupt states for timer0*/
		switch(Copy_xConfig->Interrupt_Enable)
		{
		//enable over flow interrupt
		case TIMER_OVER_FLOW_INT_ENABLE: SET_BIT(TIMSK,TIMSK_TOIE0); break;
		//enable compare match interrupt
		case TIMER_COMPARE_MATCH_INT_ENABLE: SET_BIT(TIMSK,TIMSK_OCIE0); break;
		default:  /* Do nothing */     break;
		}
	}
	/*in case of wrong input of interrupt status*/
	else
	{
		Local_enErrorSate = OUT_OF_RANGE_VALUE;
	}

	return Local_enErrorSate;
}


/******************************************
  syntax : Error_State MTIMER0_enDisableInt(const TIMER0_ConfigType * Copy_xConfig)

  Description : function to enable the timer0 interrupt.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to the struct configuration of timer0
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER0_enDisableInt(const TIMER0_ConfigType * Copy_xConfig)
{
	/*local variable for error checking*/
	Error_State Local_enErrorSate = NO_ERROR;

	/*******************************Setting interrupt****************************************/

	/*checking for correct input of interrupt status*/
	if(Copy_xConfig->Interrupt_Enable == TIMER_OVER_FLOW_INT_DISABLE || Copy_xConfig->Interrupt_Enable == TIMER_COMPARE_MATCH_INT_DISABLE)
	{
		/*switching over interrupt states for timer0*/
		switch(Copy_xConfig->Interrupt_Enable)
		{
		//enable over flow interrupt
		case TIMER_OVER_FLOW_INT_DISABLE: CLR_BIT(TIMSK,TIMSK_TOIE0); break;
		//enable compare match interrupt
		case TIMER_COMPARE_MATCH_INT_DISABLE: CLR_BIT(TIMSK,TIMSK_OCIE0); break;
		default:  /* Do nothing */     break;
		}
	}
	/*in case of wrong input of interrupt status*/
	else
	{
		Local_enErrorSate = OUT_OF_RANGE_VALUE;
	}

	return Local_enErrorSate;
}

/******************************************
  syntax : Error_State MTIMER0_enSetCallBack(void (TIMER_InterruptSource Copy_enEvent , *Copy_pvCallBackFunc)(void))

  Description : function to Set the Callback Function.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : pointer to the callback function
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER_enSetCallBack(TIMER_InterruptSource Copy_enEvent , void (*Copy_pvCallBackFunc)(void))
{
	/*local variable for error checking*/
	Error_State Local_enErrorSate = NO_ERROR;
	if(Copy_pvCallBackFunc != NULL)
	{
		switch(Copy_enEvent)
		{
		case TIMER0_OVER_FLOW: OverFlow0ptr = Copy_pvCallBackFunc; break;
		case TIMER0_COMPARE_MATCH: CompareMatch0ptr = Copy_pvCallBackFunc; break;
		case TIMER1_OVER_FLOW: OverFlow1ptr = Copy_pvCallBackFunc; break;
		case TIMER1_COMPARE_MATCH_A: CompareMatch1Aptr = Copy_pvCallBackFunc; break;
		case TIMER1_COMPARE_MATCH_B: CompareMatch1Bptr = Copy_pvCallBackFunc; break;
		case TIMER2_OVER_FLOW: OverFlow2ptr = Copy_pvCallBackFunc; break;
		case TIMER2_COMPARE_MATCH: CompareMatch2ptr = Copy_pvCallBackFunc; break;
		case TIMER1_ICU: ICUptr = Copy_pvCallBackFunc;  break;
		default : /* DO nothing */; break;
		}
	}
	else
	{
		Local_enErrorSate = NULL_POINTER;
	}

	return Local_enErrorSate;
}



/******************************************
  syntax : Error_State MTIMER0_enSetFastPWM(u8 Copy_u8Frequency , u8 Copy_u8DutyCycle);

  Description : function to set the fast PWM signal.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : frequency and the duty cycle.
  parameters (out) : none
  Return Value     : Error_State
 ******************************************/
Error_State MTIMER0_enSetFastPWM(u8 Copy_u8Frequency , u8 Copy_u8DutyCycle , TIMER_OCState Copy_enOCState)
{
	/*local variable for error checking*/
	Error_State Local_enErrorSate = NO_ERROR;
	if(Copy_enOCState == OC_CLEAR)
	{
		OCR0 = ((u16)Copy_u8DutyCycle *256) /100;
	}
	else if(Copy_enOCState == OC_SET)
	{
		OCR0 = 255 - (((u16)Copy_u8DutyCycle * 256)/100);
	}
	else
	{
		Local_enErrorSate = OUT_OF_RANGE_VALUE;
	}

	/*Setting prescaler to run TIMER/COUNTER0*/
	TCCR0 &= PRESCALER_MASK;
	TCCR0 |= Copy_u8Frequency;

	return Local_enErrorSate;
}


/******************************************
  syntax : void MTIMER1_voidICUSetTrigger(TIMER_ICUTrigger Copy_enTrigger)

  Description : function to set the icu trigger for timer1.

  Synch/Asynch     : Synchronous
  Reentrance       : Reentrant
  parameters (in)  : trigger mode
  parameters (out) : none
  Return Value     : void
 ******************************************/
void MTIMER1_voidICUSetTrigger(TIMER_ICUTrigger Copy_enTrigger)
{

	switch(Copy_enTrigger)
	{
	case FALLING:
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
		break;
	case RISING:
		SET_BIT(TCCR1B,TCCR1B_ICES1);
		break;
	default:
		/* Do nothing */
		break;
	}
}

u16 MTIMER1_u16ICUTakeReading(void)
{

	return ICR1;
}

void MTIMER1_voidICUInit(const ICU_ConfigType * Copy_xConfig)
{
	/* Timer1 always operates in Normal Mode */
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

	/* Insert the required edge type in ICES1 bit in TCCR1B Register */
	switch(Copy_xConfig->Edge)
	{
	case FALLING:
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
		break;
	case RISING:
		SET_BIT(TCCR1B,TCCR1B_ICES1);
		break;
	default:
		/* Do nothing */
		break;
	}

	/* Insert the required clock value in the first three bits (CS10, CS11 and CS12)of TCCR1B Register */
	/********************************Setting prescaler*********************************/

	/*checking for correct input for prescaler*/
	if(((Copy_xConfig->Prescaler)>=TIMER_NO_PRESCALER) && ((Copy_xConfig->Prescaler)<=TIMER_EXT_CLK_RISING))
	{
		TCCR1B &= PRESCALER_MASK;    //clearing clock select bits to receive new values
		TCCR1B |= Copy_xConfig->Prescaler; //setting prescaler to run the timer
	}
	/*in case of wrong input of prescaler*/
	else
	{
		/* Do nothing */
	}

	/* Initial Value for Timer1 */
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;

	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	SET_BIT(TIMSK, TIMSK_TICIE1);
}

void MTIMER1_voidICUsetEdgeDetectionType(const TIMER_ICUTrigger Copy_enEdgeType)
{
	/* Insert the required edge type in ICES1 bit in TCCR1B Register */
	switch(Copy_enEdgeType)
	{
	case FALLING:
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
		break;
	case RISING:
		SET_BIT(TCCR1B,TCCR1B_ICES1);
		break;
	default:
		/* Do nothing */
		break;
	}
}

void MTIMER1_voidClearTimer(void)
{
	TCNT1 = 0;
}

/*ISR for compare match event on timer0*/

void __vector_10 (void)
{
	static u32 Local_u32Counter=0;
	Local_u32Counter++;
	if(Local_u32Counter == Number_Of_CompareMatch)
	{
		CompareMatch0ptr();
		Local_u32Counter=0;
	}
}

/*ISR for over flow event on timer0*/

void __vector_11 (void)
{
	static u32 Local_u32Counter=0;
	Local_u32Counter++;

	if(Local_u32Counter == Number_Of_OverFlow)
	{
		OverFlow0ptr();
		Local_u32Counter=0;
		TCNT0 = MAX_NUMBER_OF_OVERFLOW - Number_Of_Remaining_Time;
	}
}

/*ISR for over flow event on timer1*/

void __vector_9 (void)
{
	Number_Of_OverFlow++;
}

void __vector_6 (void)
{
	if(ICUptr != NULL)
	{
		(*ICUptr)();
	}
}
