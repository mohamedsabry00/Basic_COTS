#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "TWI_cfg.h"
#include "TWI_interface.h"
#include "TWI_prv.h"
#include "TWI_reg.h"

/*If the Master will never be a Slave in the network Pass Address '0' as a parameter*/
void TWI_voidMasterInit(uint8 Copy_u8Address){

	if((Copy_u8Address != 0u) && ((Copy_u8Address>>3) != 0x0F)){
		/*Assign the Master/Slave Address*/
		TWAR = (Copy_u8Address << 1u);
	}

	/*Enable the Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Set SCL frequency 400Kbps
	 * TWPS = 0
	 * TWBR = 12*/
	TWSR &= PRESCALER_BIT_MASK;
	TWBR = 12u;

	/*Enable the TWI Module*/
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidSlaveInit(uint8 Copy_u8Address){

	/*Enable the Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	if((Copy_u8Address != 0u) && ((Copy_u8Address>>3) != 0x0F)){ //Check For Reserved addresses
		/*Assign the Master/Slave Address and Disable the General Call*/
		TWAR = (Copy_u8Address << 1u);
	}

	/*Enable the TWI Module*/
	SET_BIT(TWCR,TWCR_TWEN);
}

TWI_ErrorStatus_t TWI_enuSendStartCondition(void){
	TWI_ErrorStatus_t Local_u8ErrorState = NOERROR;

	/*Set the Start Bit*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear the TWINT Flag bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling on the TWINT Flag*/
	while(!(GET_BIT(TWCR,TWCR_TWINT)));

	/*Check on Status*/
	if((TWSR & STATUS_BIT_MASK) == MT_START){
		/*Do nothing*/
	}
	else{
		Local_u8ErrorState = START_COND_ERR;
	}

	return Local_u8ErrorState;
}

TWI_ErrorStatus_t TWI_enuSendRepeatedStartCondition(void){
	TWI_ErrorStatus_t Local_u8ErrorState = NOERROR;

	/*Set the Start Bit*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear the TWINT Flag bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling on the TWINT Flag*/
	while(!(GET_BIT(TWCR,TWCR_TWINT)));

	/*Check on Status*/
	if((TWSR & STATUS_BIT_MASK) == MT_REPEATED_START){
		/*Do nothing*/
	}
	else{
		Local_u8ErrorState = REP_START_ERR;
	}

	return Local_u8ErrorState;
}

TWI_ErrorStatus_t TWI_enuSendSlaveAddwithWrite(uint8 Copy_u8Address){
	TWI_ErrorStatus_t Local_u8ErrorState = NOERROR;

	/*Assign the address to the TWDR*/
	TWDR = (Copy_u8Address << 1);

	/*Clear bit 0 for Write operation*/
	CLR_BIT(TWDR,0u);

	/*clear the Start Bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear the TWINT Flag bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling on the TWINT Flag*/
	while(!(GET_BIT(TWCR,TWCR_TWINT)));

	/*Check on Status*/
	if((TWSR & STATUS_BIT_MASK) == MT_SLA_W_ACK){

	}
	else{
		Local_u8ErrorState = SLAVE_ADD_WR_ERR;
	}

	return Local_u8ErrorState;
}

TWI_ErrorStatus_t TWI_enuSendSlaveAddwithRead(uint8 Copy_u8Address){
	TWI_ErrorStatus_t Local_u8ErrorState = NOERROR;

	/*Assign the address to the TWDR and set the 0th Bit for Read*/
	TWDR = (Copy_u8Address << 1) | 1u;

	/*clear the Start Bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear the TWINT Flag bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling on the TWINT Flag*/
	while(!(GET_BIT(TWCR,TWCR_TWINT)));

	/*Check on Status*/
	if((TWSR & STATUS_BIT_MASK) == MT_SLA_R_ACK){

	}
	else{
		Local_u8ErrorState = SLAVE_ADD_RE_ERR;
	}

	return Local_u8ErrorState;
}

TWI_ErrorStatus_t TWI_enuMasterWriteDataByte(uint8 Copy_u8Data){
	TWI_ErrorStatus_t Local_u8ErrorState = NOERROR;

	/*Assign the Data to TWDR register*/
	TWDR = Copy_u8Data;

	/*Clear the TWINT Flag bit*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling on the TWINT Flag*/
	while(!(GET_BIT(TWCR,TWCR_TWINT)));

	/*Check on Status*/
	if((TWSR & STATUS_BIT_MASK) == MT_DATA_ACK){

	}
	else{
		Local_u8ErrorState = MSTR_WR_BYTE_ACK_ERR;
	}

	return Local_u8ErrorState;
}

TWI_ErrorStatus_t TWI_enuMasterReadDataByte(uint8* Copy_pu8Data){
	TWI_ErrorStatus_t Local_u8ErrorState = NOERROR;

	if(Copy_pu8Data != NULL){

		/*Clear the TWINT Flag bit*/
		SET_BIT(TWCR,TWCR_TWINT);

		/*Polling on the TWINT Flag*/
		while(!(GET_BIT(TWCR,TWCR_TWINT)));

		/*Check on Status*/
		if((TWSR & STATUS_BIT_MASK) == MR_DATA_ACK){
			/*Read the TWDR register*/
			*Copy_pu8Data = TWDR;
		}
		else{
			Local_u8ErrorState = MSTR_RE_BYTE_ACK_ERR;
		}
	}
	else{
		Local_u8ErrorState = NULLPTR_ERR;
	}

	return Local_u8ErrorState;
}

void TWI_voidSendStopCondition(void){

	/*Set the Stop Bit*/
	SET_BIT(TWCR,TWCR_TWSTO);

	/*Clear the TWINT Flag bit*/
	SET_BIT(TWCR,TWCR_TWINT);

}

void TWI_voidMasterACKEnable(void){
	/*Enable the Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);
}

void TWI_voidMasterNACKEnable(void){
	/*Disable the Acknowledge bit*/
	CLR_BIT(TWCR,TWCR_TWEA);
}
