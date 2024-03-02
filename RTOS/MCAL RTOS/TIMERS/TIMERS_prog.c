#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "TIMERS_interface.h"
#include "TIMERS_cfg.h"
#include "TIMERS_prv.h"
#include "TIMERS_reg.h"


static void(*TIMER_pvCallBackFunction)(void) = {NULL};

void Timer0_voidInit(void){
	/*Set CTC PWM Mode*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Clear Prescaler bits*/
	TCCR0 &= TIMER0_PRESCALER_BIT_MASK;

	/*Set the Compare match value*/
	OCR0 = 250u;

	/*Set prescaler to be division by 256*/
	TCCR0 |= 0b00000011;

	/*Enable Timer interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

}

void Timer1_voidInit(void){
	/*Set Fast PWM, ICR1 Top Value ,Mode 14*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*Set the TOP Value*/
	ICR1 = 40000u;

	/*Set the Comp Value*/
	OCR1A = 0u;

	/*Set Hardware action*/
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);

	/*Clear Prescaler bits*/
	TCCR1B &= TIMER1_PRESCALER_BIT_MASK;

	/*Set the Prescaler value 8*/
	TCCR1B |= 0b00000010;

}

uint8 Timer0_u8GetTimerValue(void){
	return TCNT0;
}

uint16 Timer1_u16GetTimerValue(void){
	return TCNT1;
}

uint8 Timer_SetCompareMatchCallBack(void(*Copy_pvCallBackFunc)(void)){
	uint8 Local_ErrorState = OK;
	if(Copy_pvCallBackFunc != NULL){
		TIMER_pvCallBackFunction = Copy_pvCallBackFunc;
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}


	return Local_ErrorState;
}

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadValue){
	TCNT0 = Copy_u8PreloadValue;
}

void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompMatchValue){
	OCR0 = Copy_u8CompMatchValue;
}

void Timer1_voidSetValue(uint16 Copy_u16Value){
	TCNT1 =  Copy_u16Value;
}

void Timer1_voidSetCompareMatchValue(uint16 Copy_u16CompMatchValue){
	OCR1A = Copy_u16CompMatchValue;
}


/*Interrupt*/
__attribute__((signal)) void __vector_11(void);
void __vector_11(void){

	if(TIMER_pvCallBackFunction[TIMER0_OVF_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER0_OC_INT]();
	}


}


__attribute__((signal)) void __vector_10(void);
void __vector_10(void){

	if(TIMER_pvCallBackFunction != NULL){
		TIMER_pvCallBackFunction();
	}


}
