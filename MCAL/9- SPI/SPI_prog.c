#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "SPI_prv.h"
#include "SPI_reg.h"
#include "SPI_cfg.h"
#include "SPI_interface.h"


void SPI_voidInit(void){
	/*Setting the Role of the module in the network*/
#if SPI_ROLE == MASTER
	SET_BIT(SPCR,SPCR_MSTR);

	/*Setting Clock Polarity / IDLE clk state to be LOW*/
	CLR_BIT(SPCR,SPCR_CPOL);

	/*Setting the clk division factor to 16*/
	SPCR &= SCK_BIT_MASK;
	SPCR |= 0b00000001;
	CLR_BIT(SPSR,SPSR_SPI2X);

#elif SPI_ROLE == SLAVE
	CLR_BIT(SPCR,SPCR_MSTR);
#else
#error	Wrong SPI_Role configuration option
#endif

	/*Setting Clock Phase to Sample First*/
	CLR_BIT(SPCR,SPCR_CPHA);

	/*Setting the Data Order Bits to LSB transmitted first*/
	SET_BIT(SPCR,SPCR_DORD);

	/*Enable the SPI*/
	SET_BIT(SPCR,SPCR_SPE);


}

uint8 SPI_u8Transcieve(uint8 Copy_data, uint8* Copy_result){
	uint8 Local_u8ErrorState = OK;

	if(Copy_result != NULL){
		uint32 Local_u32Counter = 0;
		SPDR = Copy_data;
		while((GET_BIT(SPSR,SPSR_SPIF) == 0) && (Local_u32Counter < SPI_u32TIMEOUT)){
			Local_u32Counter++;
		}
		if(Local_u32Counter == SPI_u32TIMEOUT){
			/*Timeout Value is reached*/
			Local_u8ErrorState = TIMEOUT_ERR;
		}
		else {/*SPI Transfer & Receive Complete*/
			*Copy_result = SPDR;
		}
	}
	else{
		Local_u8ErrorState =  NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
