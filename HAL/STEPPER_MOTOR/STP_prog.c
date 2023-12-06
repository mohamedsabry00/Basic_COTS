#include "STD_TYPES.h"
#include "ErrType.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "STP_interface.h"
#include "STP_cfg.h"
#include "STP_prv.h"





uint8 STP_u8Rotate(const STP_Config_t* Copy_Conf,Rotate_Direction_t Copy_Direction,uint16 Copy_Angle){
	uint8 Local_u8ErrorState = OK;
	uint16 Local_u16Steps, Local_Iterator;
	if(Copy_Conf != NULL){
		if(Copy_Direction == Clockwise){
			if(Copy_Angle >= 360u){
				for(Local_Iterator=0; Local_Iterator<512;Local_Iterator++){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8BluePin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8OrangePin,DIO_u8PIN_LOW);
					_delay_ms(2);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8OrangePin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8YellowPin,DIO_u8PIN_LOW);
					_delay_ms(2);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8YellowPin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8PinkPin,DIO_u8PIN_LOW);
					_delay_ms(2);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8PinkPin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8BluePin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
			}
			Local_u16Steps = (uint16)(((uint32)(Copy_Angle%360)*2048UL)/360UL);
			for(Local_Iterator =0;Local_Iterator < Local_u16Steps;Local_Iterator++){
				if(Local_Iterator%4 ==0){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8BluePin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8OrangePin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
				else if(Local_Iterator%4 ==1){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8OrangePin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8YellowPin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
				else if(Local_Iterator%4 ==2){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8YellowPin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8PinkPin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
				else if(Local_Iterator%4 ==3){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8PinkPin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8BluePin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
			}

		}
		else if(Copy_Direction == Counterclockwise){
			if(Copy_Angle >= 360u){
				for(Local_Iterator=0; Local_Iterator<512;Local_Iterator++){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8OrangePin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8BluePin,DIO_u8PIN_LOW);
					_delay_ms(2);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8BluePin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8PinkPin,DIO_u8PIN_LOW);
					_delay_ms(2);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8PinkPin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8YellowPin,DIO_u8PIN_LOW);
					_delay_ms(2);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8YellowPin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8OrangePin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
			}
			Local_u16Steps = (uint16)(((uint32)(Copy_Angle%360)*2048UL)/360UL);
			for(Local_Iterator =0;Local_Iterator < Local_u16Steps;Local_Iterator++){
				if(Local_Iterator%4 ==0){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8OrangePin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8BluePin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
				else if(Local_Iterator%4 ==1){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8BluePin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8PinkPin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
				else if(Local_Iterator%4 ==2){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8PinkPin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8YellowPin,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
				else if(Local_Iterator%4 ==3){
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8YellowPin,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_Conf->u8Port,Copy_Conf->u8OrangePin,DIO_u8PIN_LOW);
					_delay_ms(2);
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
