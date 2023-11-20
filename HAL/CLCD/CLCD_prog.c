#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include <util/delay.h>


#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"

#if CLCD_u8BITMODE == FOUR_BIT
static void voidSetHalfDataPort(uint8 Copy_u8Data){
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4_PIN,GET_BIT(Copy_u8Data,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5_PIN,GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6_PIN,GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7_PIN,GET_BIT(Copy_u8Data,3));

}
#endif

static void voidSendEnablePulse(void){
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_u8PIN_HIGH);
	/*Delay to set by PULSE*/
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_u8PIN_LOW);
}

void CLCD_voidSendCmd(uint8 Copy_u8Cmd){
	/*Set RS Pin to Low for CMD*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_u8PIN_LOW);

	/*SET RW pin to low for write*/
#if CLCD_u8RW_CONN_STS == DIO_CONNECTED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_u8PIN_LOW);
#endif

#if CLCD_u8BITMODE == EIGHT_BIT
	/*Send the Command*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Cmd);
	voidSendEnablePulse();
#elif CLCD_u8BITMODE == FOUR_BIT
	/*Send the Four Most significant bits of command first*/
	voidSetHalfDataPort(Copy_u8Cmd >> 4);
	voidSendEnablePulse();
	voidSetHalfDataPort(Copy_u8Cmd);
	voidSendEnablePulse();

#else
#error Wrong CLCD_u8BIT_MODE configuration option
#endif

}

void CLCD_voidSendData(uint8 Copy_u8Data){
	/*Set RS Pin to high for data*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_u8PIN_HIGH);

	/*SET RW pin to low for write*/
#if CLCD_u8RW_CONN_STS == DIO_CONNECTED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_u8PIN_LOW);
#endif
#if CLCD_u8BITMODE == EIGHT_BIT
	/*Send the Data*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Data);
	voidSendEnablePulse();
#elif CLCD_u8BITMODE == FOUR_BIT
	/*Send the Four Most significant bits of data first*/
	voidSetHalfDataPort(Copy_u8Data >> 4);
	voidSendEnablePulse();
	voidSetHalfDataPort(Copy_u8Data);
	voidSendEnablePulse();
#else
#error Wrong CLCD_u8BIT_MODE configuration option
#endif

}

void CLCD_voidInit(void){
	/*Wait for more then 30ms after power On*/
	_delay_ms(40);

	/*Send function command from datasheet*/
	/*2 Lines, 5*7 Font*/
#if CLCD_u8BITMODE == EIGHT_BIT
	CLCD_voidSendCmd(0b00111000);

#elif CLCD_u8BITMODE == FOUR_BIT
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b1000);
	voidSendEnablePulse();
#endif
	/*Send display command*/
	/*Display ON, Cursor OFF, Blink Cursor OFF*/
	CLCD_voidSendCmd(0b00001100);

	/*Clear Display*/
	CLCD_voidSendCmd(1);

}

uint8 CLCD_u8SendString(const char* Copy_pchString){
	uint8 Local_ErrorState = OK;
	if(Copy_pchString != NULL){
		uint8 Local_u8Iter;
		for(Local_u8Iter=0;Copy_pchString[Local_u8Iter] != '\0';Local_u8Iter++){
			CLCD_voidSendData(Copy_pchString[Local_u8Iter]);
		}
	}
	else{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}

void CLCD_voidSendNumber(sint32 Copy_s32Number){

	char Local_chNumber[10];
	uint8 Local_u8RightDigit, Local_u8Counter1=0;
	sint8 Local_s8Counter2;

	if(Copy_s32Number == 0){
		CLCD_voidSendData('0');
		return;
	}

	else if(Copy_s32Number <0){
		CLCD_voidSendData('-');
		Copy_s32Number = Copy_s32Number * -1;
	}

	while(Copy_s32Number != 0){
		Local_u8RightDigit = (uint8)((uint32)Copy_s32Number % 10);/*Get Right most digit*/

		Copy_s32Number/= 10;
		Local_chNumber[Local_u8Counter1]= Local_u8RightDigit + '0';/*Convert to ASCII*/

		Local_u8Counter1++;
	}

	for(Local_s8Counter2 = (sint8)Local_u8Counter1 -1 ;Local_s8Counter2 >=0;Local_s8Counter2--){
		CLCD_voidSendData(Local_chNumber[(uint8)Local_s8Counter2]);
	}

}

void CLCD_voidGoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos){
	uint8 Local_u8Address;
	if(Copy_u8YPos == 0u){
		Local_u8Address = Copy_u8XPos;
	}
	else if (Copy_u8YPos == 1u){
		Local_u8Address = 0x40 + Copy_u8XPos;
	}
	//Local_u8Address = Copy_u8YPos* 0x40 + Copy_u8XPos

	/*Set bit 7 in for SetDDRAM address cmd*/
	SET_BIT(Local_u8Address,7);

	/*Send command Set DDRAM*/
	CLCD_voidSendCmd(Local_u8Address);

}

uint8 CLCD_u8SendSpecialCharacter(uint8 Copy_u8LocationNum, uint8* Copy_pu8Pattern,uint8 Copy_u8XPos, uint8 Copy_u8YPos){
	uint8 Local_u8ErrorState = OK;
	if(Copy_pu8Pattern != NULL){
		uint8 Local_u8Counter;
		uint8 Local_u8CGRAMAddress = Copy_u8LocationNum * 8;
		/*Set Bit 6 for CGRAM Address command*/
		SET_BIT(Local_u8CGRAMAddress,6u);

		/*Send the command*/
		CLCD_voidSendCmd(Local_u8CGRAMAddress);

		/*Write the pattern inside CGRAM*/
		for(Local_u8Counter =0; Local_u8Counter < 8; Local_u8Counter++){
			CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
		}
		/*Go back to DDRAM*/
		CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

		/*Display the special pattern inside CGRAM*/
		CLCD_voidSendData(Copy_u8LocationNum);

	}
	else{
		Local_u8ErrorState =NULL_PTR_ERR;
	}


	return Local_u8ErrorState;
}
