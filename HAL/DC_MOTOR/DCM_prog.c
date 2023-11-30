#include "STD_TYPES.h"
#include "ErrType.h"

#include "DIO_interface.h"

#include "DCM_interface.h"
#include "DCM_cfg.h"
#include "DCM_prv.h"

uint8 DCM_u8Rotate_Clockwise(const DCM_Config_t* Copy_Conf){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		DIO_u8SetPinValue(Copy_Conf->u8_PORT,Copy_Conf->u8_PIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_Conf->u8_PORT,Copy_Conf->u8_PIN2,DIO_u8PIN_HIGH);
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}

uint8 DCM_u8Rotate_CounterClockwise(const DCM_Config_t* Copy_Conf){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		DIO_u8SetPinValue(Copy_Conf->u8_PORT,Copy_Conf->u8_PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_Conf->u8_PORT,Copy_Conf->u8_PIN1,DIO_u8PIN_HIGH);
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}

uint8 DCM_u8Stop(const DCM_Config_t* Copy_Conf){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		DIO_u8SetPinValue(Copy_Conf->u8_PORT,Copy_Conf->u8_PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_Conf->u8_PORT,Copy_Conf->u8_PIN1,DIO_u8PIN_LOW);
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}
