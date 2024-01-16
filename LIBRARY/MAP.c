#include "STD_TYPES.h"

#include "MAP.h"

sint32 MAP(sint32 Copy_InpRangeMIN, sint32 Copy_InpRangeMAX, sint32 Copy_OpRangeMIN, sint32 Copy_OpRangeMAX, sint32 Copy_ValToMap){
	
	return (((Copy_OpRangeMAX - Copy_OpRangeMIN)*(Copy_ValToMap - Copy_InpRangeMIN))/(Copy_InpRangeMAX - Copy_InpRangeMIN)) + Copy_OpRangeMIN;
}
