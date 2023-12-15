#include "STD_TYPES.h"
#include "BIT_MATH.H"
#include "ErrType.h"

#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"

void ADC_voidInit(void){
	/*Set AVCC as reference mode*/
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	/*Select left or right adjust based on the configured resolution*/
#if	ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error	Wrong ADC_u8RESOLUTION Configuration option
#endif
	/*Start conversion manually, disable auto trigger mode*/
	CLR_BIT(ADCSRA, ADCSRA_ADATE);

	/*Disable Interrupt Enable bit*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	/*Configure the prescaler division factor*/
	/*Clear the prscaler bit first*/
	ADCSRA &= PRESCALER_BIT_MASK;
	ADCSRA |= ADC_u8PRESCALER_DIVISION_FACTOR << PRESCALER_BIT_POS ;


	/*Enable ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);

}

uint16 ADC_u8GetChannelReading(uint8 Copy_u8Channel){

	/*Set the input channel*/
	ADMUX &= CHANNEL_BIT_MASK;		/*Clear the channel selection bits*/
	ADMUX |= Copy_u8Channel;

	/*Start Conversion*/
	SET_BIT(ADCSRA, ADCSRA_ADSC);

	/*Polling with blocking*/
	while(!(GET_BIT(ADCSRA,ADCSRA_ADIF)));

	/*Clear flag after conversion ends*/
	SET_BIT(ADCSRA, ADCSRA_ADIF);	/*Clear by SET*/

#if ADC_u8RESOLUTION == EIGHT_BITS
	return ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
	return ADC;
#endif
}
