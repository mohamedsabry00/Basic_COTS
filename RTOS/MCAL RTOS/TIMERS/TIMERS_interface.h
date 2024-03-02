#ifndef TIMERS_INTERFACE_H
#define TIMERS_INTERFACE_H

/*Interrupt Sources*/
#define TIMER0_OVF_INT						0u
#define TIMER0_OC_INT						1u

void Timer0_voidInit(void);

void Timer1_voidInit(void);

uint8 Timer_SetCompareMatchCallBack(void(*Copy_pvCallBackFunc)(void));

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadValue);

void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompMatchValue);

uint8 Timer0_u8GetTimerValue(void);


uint16 Timer1_u16GetTimerValue(void);

void Timer1_voidSetValue(uint16 Copy_u16Value);

void Timer1_voidSetCompareMatchValue(uint16 Copy_u16CompMatchValue);

#endif
