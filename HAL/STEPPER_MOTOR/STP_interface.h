#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

typedef struct{
	uint8 u8Port;
	uint8 u8BluePin;
	uint8 u8PinkPin;
	uint8 u8YellowPin;
	uint8 u8OrangePin;
}STP_Config_t;

typedef enum{
	Clockwise = 0,
	Counterclockwise = 1
}Rotate_Direction_t;

uint8 STP_u8Rotate(const STP_Config_t* Copy_Conf,Rotate_Direction_t Copy_Direction,uint16 Copy_Angle);

#endif
