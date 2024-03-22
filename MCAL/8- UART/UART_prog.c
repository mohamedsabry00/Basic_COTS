#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"


#include "UART_prv.h"
#include "UART_cfg.h"
#include "UART_interface.h"
#include "UART_reg.h"

static uint8* UART_pu8Buffer = NULL;

static uint8 UART_u8Size = 0u;

static void(*UART_pvCallBackNotificationFunc)(void) = NULL;

static uint8 UART_u8BusyFlag = IDLE;

void UART_voidInit(void){

	uint8 Local_u8UCSRCValue = 0;
	uint16 Local_u16UBRRValue = 0;

#if DOUBLE_TRANSMISSION_SPEED == ENABLED
	SET_BIT(UCSRA, UCSRA_U2X);
#endif

	/*Set All configuration bits in UCSRB Register*/
	UCSRB = RECEIVE_COMPLETE_INT | TRANSMIT_COMPLETE_INT | DATA_REG_EMPTY_INT | TRANSFERSHIP;

#if CHARACTER_SIZE == NINE_BIT
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(UCSRB,UCSRB_UCSZ2);
#endif

	Local_u8UCSRCValue |= SYNCHRONIZATION | PARITY_MODE | STOP_BITS | (CHARACTER_SIZE & CHARACTER_SIZE_BITMASK);

#if SYNCHRONIZATION == SYNCHRONOUS
	Local_u8UCSRCValue |= CLOCK_POLARITY;
#endif

	/*Set Register select bit to select UCSRC*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);

	/*Assign the UCSRC Register with configured variable*/
	UCSRC = Local_u8UCSRCValue;

#if SYNCHRONIZATION == ASYNCHRONOUS
#if DOUBLE_TRANSMISSION_SPEED == ENABLED
	Local_u16UBRRValue = (OSCILLATOR_FREQUENCY / (8*BAUD_RATE)) - 1u;
#elif DOUBLE_TRANSMISSION_SPEED == DISABLED
	Local_u16UBRRValue = (OSCILLATOR_FREQUENCY / (16*BAUD_RATE)) - 1u;
#else
#error Wrong configuration parameter!! Please configure the correct option
#endif

#elif SYNCHRONIZATION == SYNCHRONOUS
	Local_u16UBRRValue = (OSCILLATOR_FREQUENCY / (2*BAUD_RATE)) - 1u;
#else
#error Wrong Configuration Parameter!! Please select correct configuration

#endif

	/*Set UBRR Value to Output the desired Baud rate*/
	UBRRL = (uint8)Local_u16UBRRValue;
	UBRRH = ((Local_u16UBRRValue >> 8) & UBRRH_REGISTER_BITMASK);

}

uint8 UART_voidSend(uint8 Copy_u8Data){

	uint8 Local_u8ErrorState = OK;
	uint16 Local_u16TimeoutCounter = 0u;

	/*Busy wait for data register empty flag*/
	while((GET_BIT(UCSRA,UCSRA_UDRE) == 0u) && (Local_u16TimeoutCounter < TIMEOUT_VALUE)){
		Local_u16TimeoutCounter++;
	}
	if(Local_u16TimeoutCounter < TIMEOUT_VALUE){
		/*Send the data*/
		UDR = Copy_u8Data;
	}
	else{
		Local_u8ErrorState = TIMEOUT_ERR;
	}

	return Local_u8ErrorState;
}

uint8 UART_u8Receive(uint8* Copy_pu8Data){

	uint8 Local_u8ErrorState = OK;

	if(Copy_pu8Data != NULL){
		uint16 Local_u16TimoutValue = 0u;
		/*Wait until data is received*/
		while((GET_BIT(UCSRA,UCSRA_RXC) == 0) && (Local_u16TimoutValue < TIMEOUT_VALUE)){
			Local_u16TimoutValue++;
		}

		if(Local_u16TimoutValue < TIMEOUT_VALUE){
			/*Put the UDR Register in the Out Parameter*/
			*Copy_pu8Data =  UDR;
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

uint8 UART_u8SendBufferSynch(uint8* Copy_pu8Data, uint8 Copy_u8Size){
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8Iterator = 0u;
	if(Copy_pu8Data != NULL){
		for(Local_u8Iterator = 0;(Local_u8Iterator < Copy_u8Size) && (Local_u8ErrorState == OK); Local_u8Iterator++){
			Local_u8ErrorState = UART_voidSend(Copy_pu8Data[Local_u8Iterator]);
		}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 UART_u8RecieveBufferSynch(uint8* Copy_pu8Data, uint8 Copy_u8Size){
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8Iterator = 0u;
	if(Copy_pu8Data != NULL){
		for(Local_u8Iterator = 0;(Local_u8Iterator < Copy_u8Size) && (Local_u8ErrorState == OK); Local_u8Iterator++){
			Local_u8ErrorState = UART_u8Receive(&Copy_pu8Data[Local_u8Iterator]);
		}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 UART_u8SendBufferASynch(uint8* Copy_pu8Data, uint8 Copy_u8Size,void(*Copy_pvCallBackFunc)(void)){
	uint8 Local_u8ErrorState = OK;

	if((Copy_pu8Data!=NULL) && (Copy_pvCallBackFunc!=NULL)){

		if(UART_u8BusyFlag == IDLE){

			UART_u8BusyFlag = BUSY;

			UART_pu8Buffer = Copy_pu8Data;
			UART_u8Size = Copy_u8Size;
			UART_pvCallBackNotificationFunc = Copy_pvCallBackFunc;

			/*Enable Data Register Empty Interrupt Enable*/
			SET_BIT(UCSRB,UCSRB_UDRIE);
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

uint8 UART_u8RecieveBufferASynch(uint8* Copy_pu8Data, uint8 Copy_u8Size,void(*Copy_pvCallBackFunc)(void)){
	uint8 Local_u8ErrorState = OK;

	if((Copy_pu8Data!=NULL) && (Copy_pvCallBackFunc!=NULL)){

		if(UART_u8BusyFlag == IDLE){

			UART_u8BusyFlag = BUSY;

			UART_pu8Buffer = Copy_pu8Data;
			UART_u8Size = Copy_u8Size;
			UART_pvCallBackNotificationFunc = Copy_pvCallBackFunc;

			/*Enable Receive complete Interrupt Enable*/
			SET_BIT(UCSRB,UCSRB_RXCIE);
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

uint8 UART_voidSendStringSynch(const char* Copy_puString){
	uint8 Local_u8ErrorState = OK;
	if(Copy_puString != NULL){
		uint8 Local_u8Counter =0u;
		while(Copy_puString[Local_u8Counter] != '\0'){
			UART_voidSend((uint8)Copy_puString[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


static void voidASynchReceiveBufferISRHandler(void){
	static volatile uint8 Local_u8Counter = 0u;
	if(Local_u8Counter < UART_u8Size){
		/*Chain not completed Sent, read new data from UDR*/
		UART_pu8Buffer[Local_u8Counter++] = UDR;
	}
	else{
		/*Buffer Completely received*/
		/*Disable the Interrupt*/
		CLR_BIT(UCSRB,UCSRB_RXCIE);

		UART_u8BusyFlag = IDLE;

		Local_u8Counter = 0u;

		if(UART_pvCallBackNotificationFunc != NULL){
			UART_pvCallBackNotificationFunc();
		}
	}
}

static void voidASynchSendBufferISRHandler(void){
	static volatile uint8 Local_u8Counter = 0u;
	if(Local_u8Counter < UART_u8Size){
		/*Chain not completed Sent, put new data in UDR*/
		UDR = UART_pu8Buffer[Local_u8Counter++];
	}
	else{
		/*Buffer Completely Sent*/
		/*Disable the Interrupt*/
		CLR_BIT(UCSRB,UCSRB_UDRIE);

		UART_u8BusyFlag = IDLE;

		Local_u8Counter = 0u;

		if(UART_pvCallBackNotificationFunc != NULL){
			UART_pvCallBackNotificationFunc();
		}
	}
}

/*UART Receive complete ISR*/
__attribute__((signal)) void __vector_13(void);

void __vector_13(void){
	voidASynchReceiveBufferISRHandler();
}

/*UART Data Register Empty ISR*/
__attribute__((signal)) void __vector_14(void);

void __vector_14(void){
	voidASynchSendBufferISRHandler();
}
