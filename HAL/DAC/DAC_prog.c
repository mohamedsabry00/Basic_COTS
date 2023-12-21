#include "STD_TYPES.h"


#include "DIO_interface.h"

#include "DAC_interface.h"
#include "DAC_cfg.h"
#include "DAC_prv.h"

void DAC_voidSetAnalogVolt(uint16 Copy_Analogmv){

	uint8 Local_Digital = (uint8)(((uint32)Copy_Analogmv * RESOLUTION) / MAX_ANALOG_VALUE);

	DIO_u8SetPortValue(DAC_PORT,Local_Digital);
}
