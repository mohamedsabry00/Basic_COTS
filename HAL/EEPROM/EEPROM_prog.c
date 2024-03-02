#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_prv.h"
#include "EEPROM_cfg.h"

void EEPROM_voidWriteDataByte(uint16 Copy_u16LocAddress, uint8 Copy_u8DataByte){

	/*Get the 7 bit slave address*/
	uint8 Local_u8SlaveAddress = EEPROM_FIXED_ADDRESS | A2_CONNECTION | ((Copy_u16LocAddress >> 8u) & 0x03);

	/*Send start condition*/
	TWI_enuSendStartCondition();

	/*Send 7 bit SLA with Write*/
	TWI_enuSendSlaveAddwithWrite(Local_u8SlaveAddress);

	/*Send 8 bits remaining in address*/
	TWI_enuMasterWriteDataByte((uint8)Copy_u16LocAddress);

	/*Send the Data*/
	TWI_enuMasterWriteDataByte(Copy_u8DataByte);

	/*Send Stop Condition*/
	TWI_voidSendStopCondition();

	/*Delay for the memory write cycle*/
	_delay_ms(12);
}

uint8 EEPROM_voidReadDataByte(uint16 Copy_u16LocAddress){

	uint8 Local_u8Data,Local_u8SlaveAddress;

	/*Get the 7 bit slave address*/
	Local_u8SlaveAddress = EEPROM_FIXED_ADDRESS | A2_CONNECTION | ((Copy_u16LocAddress >> 8u) & 0x03);

	/*Send start condition*/
	TWI_enuSendStartCondition();

	/*Send 7 bit SLA with write*/
	TWI_enuSendSlaveAddwithWrite(Local_u8SlaveAddress);

	/*Sent 8 bits remaining in address*/
	TWI_enuMasterWriteDataByte((uint8)Copy_u16LocAddress);

	/*Send Repeated start*/
	TWI_enuSendRepeatedStartCondition();

	/*Send 7 bit SLA with Read*/
	TWI_enuSendSlaveAddwithRead(Local_u8SlaveAddress);

	/*Read the data*/
	TWI_enuMasterReadDataByte(&Local_u8Data);

	/*Send Stop Condition*/
	TWI_voidSendStopCondition();

	return Local_u8Data;
}

