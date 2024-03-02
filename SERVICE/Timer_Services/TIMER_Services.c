#include "STD_TYPES.h"
#include "ErrType.h"

#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "TIMERS_interface.h"

#include "TIMER_Services.h"

#define PRESCALER				8u


uint16 Global_u16TOVCounts = 0u, Global_u16Reading1 = 0u, Global_u16Reading2 = 0u;

uint32 Global_u32TimeMs = 0u;
Periodicity Global_enuPeriodicity = ONCE;
static void(*Global_pvCallBackFunction)(void) = NULL;

uint8 PWM_u8Set(uint16 Copy_u32Period, uint16 Copy_u32OnTime)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_u32Period >= Copy_u32OnTime){
		uint16 Local_u16TopValue, Local_u16CompareValue;
		Timer1_config_t Local_timTimerBase = {
				.CLKSelect = CLK_8,
				.INTSource = NO_INT_SOURCE,
				.WGM = FAST_PWM_ICR1TOP,
				.OCMA = THIRD_MODE_T1,
				.OCMB = FIRST_MODE
		};

		Timer1_voidInit(&Local_timTimerBase);

		Local_u16TopValue = (Copy_u32Period * CPU_FFREQUENCY) / PRESCALER ;
		Timer1_voidSetICRPreloadValue(Local_u16TopValue);

		Local_u16CompareValue = (Copy_u32OnTime * CPU_FFREQUENCY) / PRESCALER;
		Timer1_voidSetCompareMatchValue(OCR1A_REG,Local_u16CompareValue);

		Local_u8ErrorState = Timer1_voidInit(&Local_timTimerBase);
	}
	else{
		Local_u8ErrorState = NOK;
	}


	return Local_u8ErrorState;
}

uint8 PWM_u8GetPeriod(uint32* Copy_pu32Period)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pu32Period != NULL){
		Global_u16Reading1 = 0u;
		Global_u16Reading2 = 0u;
		Global_u16TOVCounts = 0u;
		uint32 Local_u32TimoutCounter;

		Timer_SetCallBack(TIMER1_OVF_INT,&PWM_voidCountTOVs);
		Timer_SetCallBack(TIMER1_IC_INT,&PWM_voidGetPeriodHelper);

		Timer1_config_t Local_tTimer1_Base = {
				.WGM = NORMAL_MODE,
				.CLKSelect = CLK_64,
				.OCMA = FIRST_MODE_T1,
				.OCMB = FIRST_MODE,
				.INTSource = TIMER1_OVF_INT
		};

		Timer1_voidInit(&Local_tTimer1_Base);

		Timer_INTEnable(TIMER1_IC_INT);

		Timer1_voidEnableInCaptureNoiseCanceler();
		Timer1_u8InptCaptureEdgeSelect(RISING);

		while(((Global_u16Reading1 == 0u) || (Global_u16Reading2 == 0u)) && (Local_u32TimoutCounter < CAPTURE_TIMEOUT_VAL)){
			Local_u32TimoutCounter++;
		}


		if(Local_u32TimoutCounter < CAPTURE_TIMEOUT_VAL){

			if(Global_u16TOVCounts > 0){/*Timer Overflows occurred*/
				(*Copy_pu32Period) = ((TIMER1_MAX_VALUE - Global_u16Reading1) + ((Global_u16TOVCounts-1) * TIMER1_MAX_VALUE) + Global_u16Reading2) * TICKTIME_INMICRO;
			}
			else{ /*No Timer Overflows occurred*/
				(*Copy_pu32Period) = ((Global_u16Reading2 - Global_u16Reading1) * TICKTIME_INMICRO);
			}
		}
		else{
			Local_u8ErrorState = TIMEOUT_ERR;
		}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


uint8 PWM_u8GetOnTime(uint32* Copy_pu32OnTime)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pu32OnTime != NULL){
		Global_u16Reading1 = 0u;
		Global_u16Reading2 = 0u;
		Global_u16TOVCounts = 0u;
		uint32 Local_u32TimoutCounter = 0u;

		Timer_SetCallBack(TIMER1_OVF_INT,&PWM_voidCountTOVs);
		Timer_SetCallBack(TIMER1_IC_INT,&PWM_voidGetOnTimeHelper);

		Timer1_config_t Local_tTimer1_Base = {
				.WGM = NORMAL_MODE,
				.CLKSelect = CLK_64,
				.OCMA = FIRST_MODE_T1,
				.OCMB = FIRST_MODE,
				.INTSource = TIMER1_OVF_INT
		};

		Timer1_voidInit(&Local_tTimer1_Base);

		Timer_INTEnable(TIMER1_IC_INT);

		Timer1_voidEnableInCaptureNoiseCanceler();
		Timer1_u8InptCaptureEdgeSelect(RISING);

		while(((Global_u16Reading1 == 0u) || (Global_u16Reading2 == 0u)) && (Local_u32TimoutCounter < CAPTURE_TIMEOUT_VAL)){
			Local_u32TimoutCounter++;
		}

		if(Local_u32TimoutCounter < CAPTURE_TIMEOUT_VAL){
			if(Global_u16TOVCounts > 0){/*Timer Overflows occurred*/
				(*Copy_pu32OnTime) = ((TIMER1_MAX_VALUE - Global_u16Reading1) + ((Global_u16TOVCounts-1) * TIMER1_MAX_VALUE) + Global_u16Reading2) * TICKTIME_INMICRO;
			}
			else{ /*No Timer Overflows occurred*/
				(*Copy_pu32OnTime) = ((Global_u16Reading2 - Global_u16Reading1) * TICKTIME_INMICRO);
			}
		}
		else{
			Local_u8ErrorState = TIMEOUT_ERR;
		}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


void PWM_voidGetPeriodHelper(void){
	static volatile uint8 Local_u8Counter = 0u;
	Local_u8Counter++;

	if(Local_u8Counter == 1u){
		Global_u16Reading1 = Timer1_GetICR1Value();
	}
	else if(Local_u8Counter == 2u){
		Global_u16Reading2 = Timer1_GetICR1Value();
		Timer_INTDisable(TIMER1_IC_INT);
		Timer_INTDisable(TIMER1_OVF_INT);
		Local_u8Counter = 0u;
	}
	else{

	}

}

void PWM_voidGetOnTimeHelper(void){
	static volatile uint8 Local_u8Counter = 0u;
	Local_u8Counter++;

	if(Local_u8Counter == 1u){
		Global_u16Reading1 = Timer1_GetICR1Value();
		Timer1_u8InptCaptureEdgeSelect(FALLING);
	}
	else if(Local_u8Counter == 2u){
		Global_u16Reading2 = Timer1_GetICR1Value();
		Timer_INTDisable(TIMER1_IC_INT);
		Timer_INTDisable(TIMER1_OVF_INT);
		Local_u8Counter = 0u;
	}
	else{

	}
}

void PWM_voidCountTOVs(void){
	Global_u16TOVCounts++;
}


uint8 Schedule_Ms(uint32 Copy_u32TimeMs,Periodicity Copy_enuPeriodicty,void(*Copy_pvCallBackFunc)(void)){
	uint8 Local_u8ErrorState = OK;
	if(Copy_pvCallBackFunc != NULL){
		Global_u32TimeMs = Copy_u32TimeMs;
		Global_enuPeriodicity = Copy_enuPeriodicty;
		Global_pvCallBackFunction = Copy_pvCallBackFunc;

		Timer1_voidSetCompareMatchValue(OCR1A_REG,COMPAREMATCH_VALUE);

		Timer_SetCallBack(TIMER1_OCA_INT,&Schedule_MsHelper);

		Timer1_config_t Local_tTimer1_Base = {
				.WGM = CTC_OCR1ATOP,
				.CLKSelect = CLK_64,
				.OCMA = FIRST_MODE_T1,
				.OCMB = FIRST_MODE,
				.INTSource = TIMER1_OCA_INT
		};

		Timer1_voidInit(&Local_tTimer1_Base);

	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

void Schedule_MsHelper(void){
	volatile static uint32 Local_u32MsCounts = 0;
	Local_u32MsCounts++;

	if(Local_u32MsCounts == Global_u32TimeMs){
		if(Global_enuPeriodicity == ONCE){
			Timer_INTDisable(TIMER1_OCA_INT);
		}

		Global_pvCallBackFunction();
	}
	else{
		/*Do Nothing*/
	}
}

