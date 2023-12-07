#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_reg.h"



void GIE_voidEnableGlobal(void){
	__asm volatile("SEI");		/*In-Line Assembly: Set I-bit*/
	/*SET_BIT(SREG, SREG_I);*/
}

void GIE_voidDisableGlobal(void){
	__asm volatile("CLI");		/*In-Line Assembly: clear I-bit*/
	/*CLR_BIT(SREG, SREG_I);*/
}