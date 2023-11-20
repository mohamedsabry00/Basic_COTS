#ifndef SWITCH_INTERFACE_H
#define SWITCH_INTERFACE_H

typedef enum{
	PULL_DOWN = 0,
	PULL_UP = 1
}SWITCH_PULL_t;

typedef enum{
	RELEASED = 0,
	PRESSED = 1
}SWITCH_STS_t;

typedef struct{
	uint8 u8PORT;
	uint8 u8PIN;
	SWITCH_PULL_t u8PULL_TYPE;
}SWITCH_Config_t;

uint8 Switch_u8GetState(const SWITCH_Config_t* Copy_pstConf, SWITCH_STS_t* Copy_penState);


#endif
