#ifndef DCM_INTERFACE_H
#define DCM_INTERFACE_H

typedef struct{
	uint8 u8_PORT;
	uint8 u8_PIN1;
	uint8 u8_PIN2;
}DCM_Config_t;

uint8 DCM_u8Rotate_Clockwise(const DCM_Config_t* Copy_Conf);

uint8 DCM_u8Rotate_CounterClockwise(const DCM_Config_t* Copy_Conf);

uint8 DCM_u8Stop(const DCM_Config_t* Copy_Conf);

#endif
