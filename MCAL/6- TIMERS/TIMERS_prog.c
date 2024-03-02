#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "TIMERS_interface.h"
#include "TIMERS_cfg.h"
#include "TIMERS_prv.h"
#include "TIMERS_reg.h"


static void(*TIMER_pvCallBackFunction[8])(void) = {NULL};

/*Functions Related to ALL Timers*/
uint8 Timer_SetCallBack(uint8 Copy_u8IntSource,void(*Copy_pvCallBackFunc)(void)){
	uint8 Local_ErrorState = OK;
	if(Copy_pvCallBackFunc != NULL){
		TIMER_pvCallBackFunction[Copy_u8IntSource] = Copy_pvCallBackFunc;
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}


	return Local_ErrorState;
}

void Timer_INTEnable(const TIMER_INT_SRS_t Copy_INTSource){
	/*Enable Timer interrupt Enable*/
	TIMSK |= Copy_INTSource;
}

void Timer_INTDisable(TIMER_INT_SRS_t Copy_INTSource){
	/*Enable Timer interrupt Enable*/
	TIMSK &= (~Copy_INTSource);
}


/*TIMER 0 RELATED FUNCTIONS*/
uint8 Timer0_u8Init(const Timer0_config_t* Copy_Config){
	uint8 Local_u8ErrorState = OK;
	if(Copy_Config != NULL){

		/*Setting Timer Mode*/
		TCCR0 &= TIMER0_2_WGM_BIT_MASK;
		TCCR0 |= Copy_Config->WGM;

		/*Setting Hardware Action*/
		TCCR0 &= TIMER0_2_OCM_BIT_MASK;
		TCCR0 |= Copy_Config->OCM;

		/*Enable Timer interrupt Enable*/
		TIMSK &= TIMER0_TIMSK_BIT_MASK;
		TIMSK |= Copy_Config->INTSource;

		/*Setting Prescaler Configuration*/
		TCCR0 &= TIMER0_1_2_PRESCALER_BIT_MASK;
		TCCR0 |= Copy_Config->CLKSelect;
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

void Timer0_voidSetOutputCompMode(TIMER0_2_OCM_t Copy_OCMode){
	/*Setting Hardware Action*/
	TCCR0 &= TIMER0_2_OCM_BIT_MASK;
	TCCR0 |= Copy_OCMode;
}

void Timer0_voidSetWaveGenMode(TIMER0_2_WGM_t Copy_WGMode){
	/*Setting Timer Mode*/
	TCCR0 &= TIMER0_2_WGM_BIT_MASK;
	TCCR0 |= Copy_WGMode;
}

void Timer0_voidSetPrescaler(TIMER0_1_CLK_t Copy_Clk){
	/*Setting Prescaler*/
	TCCR0 &= TIMER0_1_2_PRESCALER_BIT_MASK;
	TCCR0 |= Copy_Clk;
}


uint8 Timer0_u8GetTimerValue(void){
	return TCNT0;
}

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadValue){
	TCNT0 = Copy_u8PreloadValue;
}

void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompMatchValue){
	OCR0 = Copy_u8CompMatchValue;
}

/*====================================================================================*/

/*TIMER 1 RELATED FUNNCTIONS*/
uint8 Timer1_voidInit(const Timer1_config_t* Copy_Config){
	uint8 Local_u8ErrorState = OK;
	if(Copy_Config != NULL){

		/*Setting Timer Mode*/
		TCCR1A &= TIMER1_WGM_TCCR1A_BIT_MASK;
		TCCR1B &= TIMER1_WGM_TCCR1B_BIT_MASK;
		switch(Copy_Config->WGM){
		case NORMAL_MODE:break;
		case PWM_PHASE_CORRECT_8BITS:SET_BIT(TCCR1A,TCCR1A_WGM10);break;
		case PWM_PHASE_CORRECT_9BITS:SET_BIT(TCCR1A,TCCR1A_WGM11);break;
		case PWM_PHASE_CORRECT_10BITS:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);break;
		case CTC_OCR1ATOP:SET_BIT(TCCR1B,TCCR1B_WGM12);break;
		case FAST_PWM_8BITS:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1B,TCCR1B_WGM12);break;
		case FAST_PWM_9BITS:SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);break;
		case FAST_PWM_10BITS:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);break;
		case PWM_PHASE_FREQUENCY_CORRECT_ICR1TOP:SET_BIT(TCCR1B,TCCR1B_WGM13);break;
		case PWM_PHASE_FREQUENCY_CORRECT_OCR1ATOP:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
		case PWM_PHASE_CORRECT_ICR1TOP:SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
		case PWM_PHASE_CORRECT_OCR1ATOP:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
		case CTC_ICR1TOP:SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
		case FAST_PWM_ICR1TOP:SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
		case FAST_PWM_OCR1ATOP:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
		default: Local_u8ErrorState = NOK;break;
		}

		/*Setting Prescaler Configuration*/
		TCCR1B &= TIMER0_1_2_PRESCALER_BIT_MASK;
		TCCR1B |= Copy_Config->CLKSelect;

		/*Enable Timer interrupt Enable*/
		TIMSK &= TIMER1_TIMSK_BIT_MASK;
		TIMSK |= Copy_Config->INTSource;

		/*Setting Hardware action on OCA1 PIN*/
		TCCR1A &= TIMER1_OCMA_BIT_MASK;
		TCCR1A |= Copy_Config->OCMA;

		/*Setting Hardware action on OCB1 PIN*/
		TCCR1A &= TIMER1_OCMB_BIT_MASK;
		TCCR1A |= Copy_Config->OCMB;

	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint16 Timer1_u16GetTimerValue(void){
	return TCNT1;
}


void Timer1_voidSetPreloadValue(uint16 Copy_u16Value){
	TCNT1 =  Copy_u16Value;
}

void Timer1_voidSetICRPreloadValue(uint16 Copy_u16Value){
	ICR1 = Copy_u16Value;
}

uint8 Timer1_voidSetCompareMatchValue(TIMER1_COMP_REG_t Copy_Register,uint8 Copy_u8CompMatchValue){
	uint8 Local_u8ErrorState = OK;

	if(Copy_Register == OCR1A_REG){
		OCR1A = Copy_u8CompMatchValue;
	}
	else if(Copy_Register == OCR1B_REG){
		OCR1B = Copy_u8CompMatchValue;
	}
	else{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

void Timer1_voidSetPrescaler(TIMER0_1_CLK_t Copy_Clk){
	/*Setting Prescaler Configuration*/
	TCCR1B &= TIMER0_1_2_PRESCALER_BIT_MASK;
	TCCR1B |= Copy_Clk;
}

uint8 Timer1_voidSetWaveGenMode(TIMER1_WGM_t Copy_WGMode){
	uint8 Local_u8ErrorState = OK;

	/*Setting Timer Mode*/
	TCCR1A &= TIMER1_WGM_TCCR1A_BIT_MASK;
	TCCR1B &= TIMER1_WGM_TCCR1B_BIT_MASK;
	switch(Copy_WGMode){
	case NORMAL_MODE:break;
	case PWM_PHASE_CORRECT_8BITS:SET_BIT(TCCR1A,TCCR1A_WGM10);break;
	case PWM_PHASE_CORRECT_9BITS:SET_BIT(TCCR1A,TCCR1A_WGM11);break;
	case PWM_PHASE_CORRECT_10BITS:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);break;
	case CTC_OCR1ATOP:SET_BIT(TCCR1B,TCCR1B_WGM12);break;
	case FAST_PWM_8BITS:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1B,TCCR1B_WGM12);break;
	case FAST_PWM_9BITS:SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);break;
	case FAST_PWM_10BITS:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);break;
	case PWM_PHASE_FREQUENCY_CORRECT_ICR1TOP:SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case PWM_PHASE_FREQUENCY_CORRECT_OCR1ATOP:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case PWM_PHASE_CORRECT_ICR1TOP:SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case PWM_PHASE_CORRECT_OCR1ATOP:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case CTC_ICR1TOP:SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case FAST_PWM_ICR1TOP:SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	case FAST_PWM_OCR1ATOP:SET_BIT(TCCR1A,TCCR1A_WGM10);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1B,TCCR1B_WGM13);break;
	default: Local_u8ErrorState = NOK;break;
	}

	return Local_u8ErrorState;
}

uint8 Timer1_voidSetOutputCompMode(TIMER1_COMP_REG_t Copy_Register,TIMER0_2_OCM_t Copy_OCMode){
	uint8 Local_u8ErrorState = OK;

	if(Copy_Register == OCR1A_REG){
		OCR1A = (Copy_OCMode<<1);
	}
	else if(Copy_Register == OCR1B_REG){
		OCR1B = Copy_Register;
	}
	else{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}


void Timer1_voidEnableInCaptureNoiseCanceler(void){
	SET_BIT(TCCR1B,TCCR1B_ICNC1);
}

void Timer1_voidDisableInCaptureNoiseCanceler(void){
	CLR_BIT(TCCR1B,TCCR1B_ICNC1);
}

uint8 Timer1_u8InptCaptureEdgeSelect(InCapture_Trigger Copy_u8TriggerEdge){
	uint8 Local_u8ErrorState = OK;

	if(Copy_u8TriggerEdge == FALLING){
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8TriggerEdge == RISING){
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint16 Timer1_GetICR1Value(void){
	return ICR1;
}


/*===============================================================================================*/

/*TIMER 2 RELATED FUNCTIONS*/
uint8 Timer2_u8Init(const Timer2_config_t* Copy_Config){
	uint8 Local_u8ErrorState = OK;
	if(Copy_Config != NULL){

		/*Setting Timer Mode*/
		TCCR2 &= TIMER0_2_WGM_BIT_MASK;
		TCCR2 |= Copy_Config->WGM;

		/*Setting Hardware Action*/
		TCCR2 &= TIMER0_2_OCM_BIT_MASK;
		TCCR2 |= Copy_Config->OCM;

		/*Enable Timer interrupt Enable*/
		TIMSK &= TIMER2_TIMSK_BIT_MASK;
		TIMSK |= Copy_Config->INTSource;

		/*Setting Prescaler Configuration*/
		TCCR2 &= TIMER0_1_2_PRESCALER_BIT_MASK;
		TCCR2 |= Copy_Config->CLKSelect;
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

void Timer2_voidSetOutputCompMode(TIMER0_2_OCM_t Copy_OCMode){
	/*Setting Hardware Action*/
	TCCR2 &= TIMER0_2_OCM_BIT_MASK;
	TCCR2 |= Copy_OCMode;
}

void Timer2_voidSetWaveGenMode(TIMER0_2_WGM_t Copy_WGMode){
	/*Setting Timer Mode*/
	TCCR2 &= TIMER0_2_WGM_BIT_MASK;
	TCCR2 |= Copy_WGMode;
}

void Timer2_voidSetPrescaler(TIMER2_CLK_t Copy_Clk){
	/*Setting Prescaler*/
	TCCR2 &= TIMER0_1_2_PRESCALER_BIT_MASK;
	TCCR2 |= Copy_Clk;
}


uint8 Timer2_u8GetTimerValue(void){
	return TCNT2;
}

void Timer2_voidSetPreloadValue(uint8 Copy_u8PreloadValue){
	TCNT2 = Copy_u8PreloadValue;
}

void Timer2_voidSetCompareMatchValue(uint8 Copy_u8CompMatchValue){
	OCR2 = Copy_u8CompMatchValue;
}

/*==================================================================*/
/*Interrupts Handling Routines*/

/*Interrupt Handler for Timer 2 Output Compare Match */
__attribute__((signal)) void __vector_4(void);
void __vector_4(void){

	if(TIMER_pvCallBackFunction[TIMER2_OC_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER2_OC_INT]();
	}
	else
	{

	}
}

/*Interrupt Handler for Timer 2 Overflow*/
__attribute__((signal)) void __vector_5(void);
void __vector_5(void){

	if(TIMER_pvCallBackFunction[TIMER2_OVF_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER2_OVF_INT]();
	}
	else
	{

	}
}

/*Interrupt Handler for Timer 1 Input Capture Event*/
__attribute__((signal)) void __vector_6(void);
void __vector_6(void){

	if(TIMER_pvCallBackFunction[TIMER1_IC_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER1_IC_INT]();
	}
	else
	{

	}
}

/*Interrupt Handler for Timer 1 Output Compare Match A */
__attribute__((signal)) void __vector_7(void);
void __vector_7(void){

	if(TIMER_pvCallBackFunction[TIMER1_OCA_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER1_OCA_INT]();
	}
	else
	{

	}
}

/*Interrupt Handler for Timer 1 Output Compare Match B */
__attribute__((signal)) void __vector_8(void);
void __vector_8(void){

	if(TIMER_pvCallBackFunction[TIMER1_OCB_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER1_OCB_INT]();
	}
	else
	{

	}
}

/*Interrupt Handler for Timer 1 Overflow*/
__attribute__((signal)) void __vector_9(void);
void __vector_9(void){

	if(TIMER_pvCallBackFunction[TIMER1_OVF_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER1_OVF_INT]();
	}
	else
	{

	}
}


/*Interrupt Handler for Timer 0 Output Compare Match*/
__attribute__((signal)) void __vector_10(void);
void __vector_10(void){

	if(TIMER_pvCallBackFunction[TIMER0_OC_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER0_OC_INT]();
	}
	else
	{

	}
}


/*Interrupt Handler for Timer 0 Overflow*/
__attribute__((signal)) void __vector_11(void);
void __vector_11(void){

	if(TIMER_pvCallBackFunction[TIMER0_OVF_INT] != NULL){
		TIMER_pvCallBackFunction[TIMER0_OVF_INT]();
	}
	else
	{

	}
}

