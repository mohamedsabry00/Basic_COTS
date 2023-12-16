#include "STD_TYPES.h"
#include "BIT_MATH.H"
#include "ErrType.h"

#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"


static uint16* ADC_pu16Result = NULL;
static void(*ADC_pvCallBackNotificationFunc)(void) = NULL;
static uint8 ADC_u8BusyFlag = IDLE;

void ADC_voidInit(void){
	/*Set AVCC as reference mode*/
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	/*Select left or right adjust based on the configured resolution*/
#if	ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error	Wrong ADC_u8RESOLUTION Configuration option
#endif
	/*Start conversion manually, disable auto trigger mode*/
	CLR_BIT(ADCSRA, ADCSRA_ADATE);

	/*Disable Interrupt Enable bit*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	/*Configure the prescaler division factor*/
	/*Clear the prscaler bit first*/
	ADCSRA &= PRESCALER_BIT_MASK;
	ADCSRA |= ADC_u8PRESCALER_DIVISION_FACTOR << PRESCALER_BIT_POS ;


	/*Enable ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);

}

uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result){
	uint8 Local_ErrorState = OK;
	uint32 Local_u32Counter=0;

	if(Copy_pu16Result != NULL){
		/*Check if ADC is IDLE*/
		if(ADC_u8BusyFlag == IDLE){

			/*ADC is Now Busy*/
			ADC_u8BusyFlag = BUSY;

			/*Set the input channel*/
			ADMUX &= CHANNEL_BIT_MASK;		/*Clear the channel selection bits*/
			ADMUX |= Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Polling with blocking and */
			while((!(GET_BIT(ADCSRA,ADCSRA_ADIF))) && (Local_u32Counter < ADC_u32TIMEOUT)){
				Local_u32Counter++;
			}
			if(Local_u32Counter == ADC_u32TIMEOUT){
				/*Time out has passed without flag being raised*/
				Local_ErrorState = TIMEOUT_ERR;
			}
			else{
				/*Conversion complete before timeout*/
				/*Clear flag after conversion ends*/
				SET_BIT(ADCSRA, ADCSRA_ADIF);	/*Clear by SET*/

#if ADC_u8RESOLUTION == EIGHT_BITS
				*Copy_pu16Result = ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
				*Copy_pu16Result =  ADC;
#endif
			}
			/*ADC is Now IDle*/
			ADC_u8BusyFlag = IDLE;
		}
		else{
			Local_ErrorState = BUSY_ERR;
		}
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}


	return Local_ErrorState;
}

uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result, void (*Copy_pvNotificationFunc)(void)){
	uint8 Local_u8ErrorState = OK;

	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL)){
		/*Check if ADC is Busy*/
		if(ADC_u8BusyFlag == IDLE){
			/*ADC is Now Busy*/
			ADC_u8BusyFlag = BUSY;

			/*Convert the local ADC result into global*/
			ADC_pu16Result = Copy_pu16Result;
			/*Convert the local ADC Call Back into global*/
			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Set the input channel*/
			ADMUX &= CHANNEL_BIT_MASK;		/*Clear the channel selection bits*/
			ADMUX |= Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);
		}
		else{
			Local_u8ErrorState = BUSY_ERR;
		}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;

	}

	return Local_u8ErrorState;
}
/*ADC conversion complete ISR*/
__attribute__((signal)) void __vector_16(void);

void __vector_16(void){
	/*Read the result*/
#if ADC_u8RESOLUTION == EIGHT_BITS
	*ADC_pu16Result = ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
	*ADC_pu16Result =  ADC;
#endif

	/*Disable ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	/*ADC is Now IDLE*/
	ADC_u8BusyFlag = IDLE;

	/*Call the Call Back Notification Function*/
	if(ADC_pvCallBackNotificationFunc != NULL){
		ADC_pvCallBackNotificationFunc();
	}
}
