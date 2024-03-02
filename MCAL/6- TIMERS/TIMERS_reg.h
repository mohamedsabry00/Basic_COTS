#ifndef TIMERS_REG_H
#define TIMERS_REG_H

/*Timer 0 Registers*/
#define TCCR0			*((volatile uint8*) 0x53)
#define TCCR0_WGM00		6u
#define TCCR0_WGM01		3u
#define TCCR0_COM00		4u
#define TCCR0_COM01		5u

#define TCNT0			*((volatile uint8*) 0x52)

#define OCR0			*((volatile uint8*) 0x5C)

/*Timer 1 Registers*/
#define TCNT1			*((volatile uint16*) 0x4C)
#define OCR1A			*((volatile uint16*) 0x4A)
#define OCR1B			*((volatile uint16*) 0x48)
#define ICR1			*((volatile uint16*) 0x46)

#define TCCR1A			*((volatile uint8*) 0x4F)
#define	TCCR1A_WGM10	0u
#define	TCCR1A_WGM11	1u
#define	TCCR1A_COM1B0	4u
#define	TCCR1A_WGM1B1	5u
#define	TCCR1A_WGM1A0	6u
#define	TCCR1A_WGM1A1	7u

#define TCCR1B			*((volatile uint8*) 0x4E)
#define	TCCR1B_WGM12	3u
#define	TCCR1B_WGM13	4u
#define	TCCR1B_ICES1	6u
#define	TCCR1B_ICNC1	7u

/*Timer 2 Registers*/
#define TCCR2			*((volatile uint8*) 0x45)
#define TCCR2_WGM20		6u
#define TCCR2_WGM21		3u
#define TCCR2_COM20		4u
#define TCCR2_COM21		5u

#define TCNT2			*((volatile uint8*) 0x44)

#define OCR2			*((volatile uint8*) 0x43)

/*Timers Interrupt Mask Register*/
#define TIMSK			*((volatile uint8*) 0x59)
#define TIMSK_TOIE0		0u
#define TIMSK_OCIE0		1u
#define TIMSK_TOIE1		2u
#define TIMSK_OCIE1B	3u
#define TIMSK_OCIE1A	4u
#define TIMSK_TICIE1	5u
#define TIMSK_TOIE2		6u
#define TIMSK_OCIE2		7u



#endif
