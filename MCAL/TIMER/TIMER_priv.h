/*****************************************************************
* FILE DESCRIPTION:
----------------------------------------------------------------
*  file    : TIMER_priv.h
*  details : Header file for private TIMER Driver.
*****************************************************************/

#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_

/******************************************
  Local Macros / Functions
*******************************************/
#define OC_ACTION_MASK      0b11001111
#define PRESCALER_MASK      0b11111000

#define MAX_NUMBER_OF_OVERFLOW 256


/*  TCCR1A Bits */
#define TCCR1A_COM1A1            7
#define TCCR1A_COM1A0            6
#define TCCR1A_COM1B1            5
#define TCCR1A_COM1B0            4
#define TCCR1A_FOC1A             3
#define TCCR1A_FOC1B             2
#define TCCR1A_WGM11			 1
#define TCCR1A_WGM10			 0

/*  TCCR1B Bits */
#define TCCR1B_ICNC1             7
#define TCCR1B_ICES1             6
#define TCCR1B_WGM13             4
#define TCCR1B_WGM12             3
#define TCCR1B_CS12              2
#define TCCR1B_CS11			     1
#define TCCR1B_CS10			     0

#define TCCR2_CS20         0
#define TCCR2_CS21         1
#define TCCR2_CS22         2
#define TCCR2_WGM21        3
#define TCCR2_COM20        4
#define TCCR2_COM21        5
#define TCCR2_WGM20        6
#define TCCR2_FOC2         7

/* TIMSK Bits */
#define TIMSK_TOIE0             0
#define TIMSK_OCIE0             1
#define TIMSK_TOIE1             2
#define TIMSK_OCIE1B            3
#define TIMSK_OCIE1A            4
#define TIMSK_TICIE1            5

/*  TCCR0 Bits */
#define TCCR0_FOC0              7
#define TCCR0_WGM00             6
#define TCCR0_COM01             5
#define TCCR0_COM00             4
#define TCCR0_WGM01             3
#define TCCR0_CS02              2
#define TCCR0_CS01				1
#define TCCR0_CS00				0

/* TIFR Bits */
#define TIFR_OCF2               7
#define TIFR_TOV2               6
#define TIFR_ICF1               5
#define TIFR_OCF1A              4
#define TIFR_OCF1B              3
#define TIFR_TOV1               2
#define TIFR_OCF0               1
#define TIFR_TOV0               0

/******************************************
  Local Functions Prototypes
*******************************************/
void __vector_6 (void) __attribute__((signal));
void __vector_9 (void) __attribute__((Signal));
void __vector_10 (void) __attribute__((signal));
void __vector_11 (void) __attribute__((signal));


#endif /* TIMER_PRIV_H_ */
