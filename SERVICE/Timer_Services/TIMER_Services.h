#ifndef TIMER_SERVICES_H
#define	TIMER_SERVICES_H

/*CPU Frequency in MHz*/
#define CPU_FFREQUENCY			16u

#define CAPTURE_TIMEOUT_VAL		500000u

#define TIMER1_MAX_VALUE		0xFFFFu

#define TICKTIME_INMICRO		4u

#define COMPAREMATCH_VALUE		240u

typedef enum{
	ONCE,
	PERIODIC
}Periodicity;

/*IMPORTANT
 * ALL of the following functions uses Timer 1 as it is the best option
 * Don't use More than 1 function in your application to obviate any undefined behavior
 * */

/*This Function Sets a PWM signal with the desired period and duty cycle using Timer 1
 * Parameters should be given in microseconds
 * Maximum Period = 32767 us
 * Minimum Period = 1 us*/
uint8 PWM_u8Set(uint16 Copy_u32Period, uint16 Copy_u32OnTime);

/*This Function Gets the period of a square signal using Input Capture Unit HW*/
uint8 PWM_u8GetPeriod(uint32* Copy_pu16Period);

void PWM_voidGetPeriodHelper(void);

void PWM_voidCountTOVs(void);

/*This Function Gets the On Time of a square signal using Input Capture Unit HW*/
uint8 PWM_u8GetOnTime(uint32* Copy_pu16OnTime);

void PWM_voidGetOnTimeHelper(void);


/*This Function Schedules .....*/

uint8 Schedule_Ms(uint32 Copy_u32TimeMs,Periodicity Copy_enuPeriodicty,void(*Copy_pvCallBackFunc)(void));

void Schedule_MsHelper(void);

#endif
