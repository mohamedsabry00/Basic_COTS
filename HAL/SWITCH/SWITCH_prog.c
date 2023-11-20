#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "DIO_interface.h"

#include "SWITCH_interface.h"
#include "SWITCH_cfg.h"
#include "SWITCH_prv.h"

uint8 Switch_u8GetState(const SWITCH_Config_t* Copy_pstConf, SWITCH_STS_t* Copy_penState){
	uint8 Local_u8ErrorState = OK;
	if((Copy_pstConf != NULL) && (Copy_penState != NULL)){
		uint8 Local_ButtonState;
		if(Copy_pstConf->u8PULL_TYPE == PULL_UP){
			Local_u8ErrorState = DIO_u8ReadPinValue(Copy_pstConf->u8PORT,Copy_pstConf->u8PIN,&Local_ButtonState);
			if(Local_u8ErrorState == OK){
				if(Local_ButtonState == DIO_u8PIN_LOW){
					*Copy_penState = PRESSED;
				}
				else if(Local_ButtonState == DIO_u8PIN_HIGH){
					*Copy_penState = RELEASED;
				}
				else{
					Local_u8ErrorState = NOK;
				}
			}
		}
		else if(Copy_pstConf->u8PULL_TYPE == PULL_DOWN){
			Local_u8ErrorState = DIO_u8ReadPinValue(Copy_pstConf->u8PORT,Copy_pstConf->u8PIN,&Local_ButtonState);
			if(Local_u8ErrorState == OK){
				if(Local_ButtonState == DIO_u8PIN_LOW){
					*Copy_penState = RELEASED;
				}
				else if(Local_ButtonState == DIO_u8PIN_HIGH){
					*Copy_penState = PRESSED;
				}
				else{
					Local_u8ErrorState = NOK;
				}
			}
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
