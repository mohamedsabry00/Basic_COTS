#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "DIO_interface.h"

#include "SSD_interface.h"
#include "SSD_cfg.h"
#include "SSD_prv.h"

uint8 SSD_u8ON(const SSD_Config_t* Copy_Conf){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		if(Copy_Conf->SSD_u8TYPE == CATHODE){
			DIO_u8SetPinValue(Copy_Conf->SSD_u8ENABLE_PORT,Copy_Conf->SSD_u8ENABLE_PIN,DIO_u8PIN_LOW);
		}
		else if((Copy_Conf->SSD_u8TYPE == ANODE) || (Copy_Conf->SSD_u8TYPE == ETAKIT)){
			DIO_u8SetPinValue(Copy_Conf->SSD_u8ENABLE_PORT,Copy_Conf->SSD_u8ENABLE_PIN,DIO_u8PIN_HIGH);
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

uint8 SSD_u8OFF(const SSD_Config_t* Copy_Conf){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		if(Copy_Conf->SSD_u8TYPE == CATHODE){
			DIO_u8SetPinValue(Copy_Conf->SSD_u8ENABLE_PORT,Copy_Conf->SSD_u8ENABLE_PIN,DIO_u8PIN_HIGH);
		}
		else if((Copy_Conf->SSD_u8TYPE == ANODE) || (Copy_Conf->SSD_u8TYPE == ETAKIT)){
			DIO_u8SetPinValue(Copy_Conf->SSD_u8ENABLE_PORT,Copy_Conf->SSD_u8ENABLE_PIN,DIO_u8PIN_LOW);
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

uint8 SSD_u8SetNumber(const SSD_Config_t* Copy_Conf,uint8 Copy_Number){
	uint8 Local_ErrorState = OK;
	if(Copy_Conf != NULL){
		uint8 Local_au8SSD_BCD[10]={
				// ABCDEFG (Segments: A, B, C, D, E, F, G)
				0b00111111, // 0
				0b00110000, // 1
				0b01011011, // 2
				0b01001111, // 3
				0b01100110, // 4
				0b01101101, // 5
				0b01111101, // 6
				0b00000111, // 7
				0b01111111, // 8
				0b01101111  // 9
		};

		if((Copy_Conf->SSD_u8TYPE == CATHODE) || (Copy_Conf->SSD_u8TYPE == ETAKIT)){
			uint8 Local_Display_Num = Local_au8SSD_BCD[Copy_Number];
			if(Copy_Conf->SSD_u8LEDA_PIN == DIO_u8PIN0){
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN0,GET_BIT(Local_Display_Num,0u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN1,GET_BIT(Local_Display_Num,1u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN2,GET_BIT(Local_Display_Num,2u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN3,GET_BIT(Local_Display_Num,3u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN4,GET_BIT(Local_Display_Num,4u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN5,GET_BIT(Local_Display_Num,5u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN6,GET_BIT(Local_Display_Num,6u));
			}
			else if(Copy_Conf->SSD_u8LEDA_PIN == DIO_u8PIN1){
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN1,GET_BIT(Local_Display_Num,0u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN2,GET_BIT(Local_Display_Num,1u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN3,GET_BIT(Local_Display_Num,2u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN4,GET_BIT(Local_Display_Num,3u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN5,GET_BIT(Local_Display_Num,4u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN6,GET_BIT(Local_Display_Num,5u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN7,GET_BIT(Local_Display_Num,6u));
			}
			else{
				Local_ErrorState = NOK;
			}
		}
		else if(Copy_Conf->SSD_u8TYPE == ANODE){
			uint8 Local_Display_Num = ~(Local_au8SSD_BCD[Copy_Number]);
			if(Copy_Conf->SSD_u8LEDA_PIN == DIO_u8PIN0){
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN0,GET_BIT(Local_Display_Num,0u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN1,GET_BIT(Local_Display_Num,1u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN2,GET_BIT(Local_Display_Num,2u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN3,GET_BIT(Local_Display_Num,3u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN4,GET_BIT(Local_Display_Num,4u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN5,GET_BIT(Local_Display_Num,5u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN6,GET_BIT(Local_Display_Num,6u));
			}
			else if(Copy_Conf->SSD_u8LEDA_PIN == DIO_u8PIN1){
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN1,GET_BIT(Local_Display_Num,0u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN2,GET_BIT(Local_Display_Num,1u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN3,GET_BIT(Local_Display_Num,2u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN4,GET_BIT(Local_Display_Num,3u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN5,GET_BIT(Local_Display_Num,4u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN6,GET_BIT(Local_Display_Num,5u));
				DIO_u8SetPinValue(Copy_Conf->SSD_u8PORT,DIO_u8PIN7,GET_BIT(Local_Display_Num,6u));
			}
			else{
				Local_ErrorState = NOK;
			}
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
