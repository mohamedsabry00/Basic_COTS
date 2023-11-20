#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

typedef enum{
	ActiveLow =0,
	ActiveHigh = 1
}LED_ACT_t;

typedef struct{
	uint8 LED_u8PORT;
	uint8 LED_u8PIN;
	LED_ACT_t LED_u8ACTIVE_TYPE;
}LED_Config_t;

uint8 LED_u8SetON(const LED_Config_t* Copy_Conf);

uint8 LED_u8SetOFF(const LED_Config_t* Copy_Conf);

uint8 LED_u8Toggle(const LED_Config_t* Copy_Conf);

#endif
