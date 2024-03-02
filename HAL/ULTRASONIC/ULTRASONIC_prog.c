#include "STD_TYPES.h"
#include "ErrType.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "TIMERS_interface.h"

#include "TIMER_Services.h"

#include "CLCD_interface.h"

#include "ULTRASONIC_cfg.h"
#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_prv.h"

uint8 ULTRASONIC_u8GetDistance(const Ultrasonic_Config_t* Copy_pstrConfig,uint16* Copy_pu16Distance){
	uint8 Local_u8ErrorState = OK;

	if((Copy_pstrConfig != NULL) && (Copy_pu16Distance != NULL)){
		uint32 Local_u32OnTime = 0u;

		DIO_u8SetPinValue(Copy_pstrConfig->PORT,Copy_pstrConfig->TRIG_PIN,DIO_u8PIN_HIGH);
		_delay_us(12);
		DIO_u8SetPinValue(Copy_pstrConfig->PORT,Copy_pstrConfig->TRIG_PIN,DIO_u8PIN_LOW);

		Local_u8ErrorState = PWM_u8GetOnTime(&Local_u32OnTime);

		if(Local_u8ErrorState == OK){
			(*Copy_pu16Distance) = (SPEED_OF_SOUND * ((uint32)Local_u32OnTime)) / UNIT_CONV_FACTOR ;
		}
		else{
			Local_u8ErrorState = NOK;
		}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
