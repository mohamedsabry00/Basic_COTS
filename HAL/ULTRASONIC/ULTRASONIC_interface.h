#ifndef ULTRASONIC_INTERFACE_H
#define ULTRASONIC_INTERFACE_H

typedef struct{
	uint8 PORT;
	uint8 TRIG_PIN;
	uint8 ECHO_PIN;
}Ultrasonic_Config_t;



uint8 ULTRASONIC_u8GetDistance(const Ultrasonic_Config_t* Copy_pstrConfig,uint16* Copy_pu16Distance);


#endif
