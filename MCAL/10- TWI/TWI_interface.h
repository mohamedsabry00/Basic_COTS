#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

typedef enum{
	NOERROR,
	NULLPTR_ERR,
	START_COND_ERR,
	REP_START_ERR,
	SLAVE_ADD_WR_ERR, /*Slave Address with write error*/
	SLAVE_ADD_RE_ERR, /*Slave Address with read error*/
	MSTR_WR_BYTE_ACK_ERR, /*Master write byte with ACK error*/
	MSTR_RE_BYTE_ACK_ERR /*Master read byte with ACK error*/
}TWI_ErrorStatus_t;

/*If the Master will never be a Slave in the network Pass Address '0' as a parameter*/
void TWI_voidMasterInit(uint8 Copy_u8Address);

void TWI_voidSlaveInit(uint8 Copy_u8Address);

TWI_ErrorStatus_t TWI_enuSendStartCondition(void);

TWI_ErrorStatus_t TWI_enuSendRepeatedStartCondition(void);

TWI_ErrorStatus_t TWI_enuSendSlaveAddwithWrite(uint8 Copy_u8Address);

TWI_ErrorStatus_t TWI_enuSendSlaveAddwithRead(uint8 Copy_u8Address);

TWI_ErrorStatus_t TWI_enuMasterWriteDataByte(uint8 Copy_u8Data);

TWI_ErrorStatus_t TWI_enuMasterReadDataByte(uint8* Copy_pu8Data);

void TWI_voidSendStopCondition(void);

void TWI_voidMasterACKEnable(void);

void TWI_voidMasterNACKEnable(void);

#endif
