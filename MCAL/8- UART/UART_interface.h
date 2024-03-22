#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

void UART_voidInit(void);

uint8 UART_voidSend(uint8 Copy_u8Data);

uint8 UART_u8Receive(uint8* Copy_pu8Data);

uint8 UART_u8SendBufferSynch(uint8* Copy_pu8Data, uint8 Copy_u8Size);

uint8 UART_u8RecieveBufferSynch(uint8* Copy_pu8Data, uint8 Copy_u8Size);

uint8 UART_u8SendBufferASynch(uint8* Copy_pu8Data, uint8 Copy_u8Size,void(*Copy_pvCallBackFunc)(void));

uint8 UART_u8RecieveBufferASynch(uint8* Copy_pu8Data, uint8 Copy_u8Size,void(*Copy_pvCallBackFunc)(void));

uint8 UART_voidSendStringSynch(const char* Copy_puString);

#endif
