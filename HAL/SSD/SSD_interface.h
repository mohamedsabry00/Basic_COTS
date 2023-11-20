#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

/*Configurations:
 * 1) SSD_u8TYPE options:   1- ANODE
 * 							2- CATHODE
 * 							3- ETAKIT
 *
 * 2) SSD_u8LEDA_PIN options:   1- DIO_u8PIN0
 * 								2- DIO_u8PIN1
 * */

typedef enum{
	ANODE = 1u,
	CATHODE = 2U,
	ETAKIT = 3U
}SSD_TYPE_t;

typedef struct{
	SSD_TYPE_t SSD_u8TYPE;
	uint8 SSD_u8PORT;
	uint8 SSD_u8LEDA_PIN;
	uint8 SSD_u8ENABLE_PORT;
	uint8 SSD_u8ENABLE_PIN;
}SSD_Config_t;



uint8 SSD_u8ON(const SSD_Config_t* Copy_Conf);

uint8 SSD_u8OFF(const SSD_Config_t* Copy_Conf);

uint8 SSD_u8SetNumber(const SSD_Config_t* Copy_Conf,uint8 Copy_Number);

#endif
