#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "WDT_cfg.h"
#include "WDT_interface.h"
#include "WDT_prv.h"
#include "WDT_reg.h"

uint8 WDT_u8SetTime(WDT_TIME_t Copy_Time){
	/*Clearing the prscaler bits*/
	WDTCR &= PRESCALER_BITG_MASK;

	/*Setting prescaler bits*/
	WDTCR |= Copy_Time;
}

void WDT_voidEnable(void){
	SET_BIT(WDTCR,WDTCR_WDE);
}

void WDT_voidDisable(void){
	/*Disabling Sequence*/
	/*Set WDE and WDTOE bits IN THE SAME OPERATION*/
	WDTCR = 0b00011000;

	/*Clear the WDE bit in the next 4 clock cycles*/
	WDTCR = 0u;

}

void WDT_voidReset(void){
	__asm volatile("WDR");		/*In-Line Assembly: Watch Dog Timer Reset*/
}
