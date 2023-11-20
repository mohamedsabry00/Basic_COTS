#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "DIO_interface.h"

#include "LED_interface.h"
#include "LED_cfg.h"
#include "LED_prv.h"

uint8 LED_u8SetON(const LED_Config_t* Copy_Conf){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		if(Copy_Conf->LED_u8ACTIVE_TYPE == ActiveHigh){
			DIO_u8SetPinValue(Copy_Conf->LED_u8PORT,Copy_Conf->LED_u8PIN,DIO_u8PIN_HIGH);
		}
		else if(Copy_Conf->LED_u8ACTIVE_TYPE == ActiveLow){
			DIO_u8SetPinValue(Copy_Conf->LED_u8PORT,Copy_Conf->LED_u8PIN,DIO_u8PIN_LOW);
		}
		else{
			Local_ErrorState = NOK;
		}
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}
	return Local_ErrorState;
}

uint8 LED_u8SetOFF(const LED_Config_t* Copy_Conf){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		if(Copy_Conf->LED_u8ACTIVE_TYPE == ActiveHigh){
			DIO_u8SetPinValue(Copy_Conf->LED_u8PORT,Copy_Conf->LED_u8PIN,DIO_u8PIN_LOW);
		}
		else if(Copy_Conf->LED_u8ACTIVE_TYPE == ActiveLow){
			DIO_u8SetPinValue(Copy_Conf->LED_u8PORT,Copy_Conf->LED_u8PIN,DIO_u8PIN_HIGH);
		}
		else{
			Local_ErrorState = NOK;
		}
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}
	return Local_ErrorState;
}

uint8 LED_u8Toggle(const LED_Config_t* Copy_Conf){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		DIO_u8TogglePinValue(Copy_Conf->LED_u8PORT,Copy_Conf->LED_u8PIN);
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}
	return Local_ErrorState;
}
