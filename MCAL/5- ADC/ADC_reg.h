#ifndef ADC_REG_H
#define ADC_REG_H

#define ADMUX  				*((volatile uint8*) 0x27)	/*ADC Multiplexer selection register*/
#define ADMUX_REFS1			7u							/*REference Bit 1*/
#define ADMUX_REFS0			6u							/*REference Bit 0*/
#define ADMUX_ADLAR			5u							/*Left adjust result*/


#define ADCSRA  			*((volatile uint8*) 0x26)	/*ADC Control and status register*/
#define ADCSRA_ADEN			7u							/*Enable*/
#define ADCSRA_ADSC			6u							/*Start Conversion*/	
#define ADCSRA_ADATE		5u							/*Auto trigger enable*/
#define ADCSRA_ADIF			4u							/*Interrupt Flag*/
#define ADCSRA_ADIE			3u
  			




#define ADCH  				*((volatile uint8*) 0x25)
#define ADCL  				*((volatile uint8*) 0x24)

#define ADC   				*((volatile uint16*) 0x24)



#endif
