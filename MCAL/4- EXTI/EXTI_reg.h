#ifndef EXTI_REG_H
#define EXTI_REG_H

#define GICR		*((volatile uint8*)0x5B)	/*General Interrupt Control register*/
#define GICR_INT1	7u							/*Int1 bit*/
#define GICR_INT0	6u							/*Int0 bit*/
#define GICR_INT2	5u							/*Int2 bit*/

#define	MCUCR		*((volatile uint8*)0x55)	/*MCU Control register*/
#define MCUCR_ISC00	0u							/*Int0 Sense control Bit0*/
#define MCUCR_ISC01	1u                          /*Int0 Sense control Bit1*/
#define MCUCR_ISC10	2u                          /*Int1 Sense control Bit0*/
#define MCUCR_ISC11	3u                          /*Int1 Sense control Bit1*/

#define MCUCSR		*((volatile uint8*)0x54)	/*MCU Control and status register*/
#define MCUCSR_ISC2	6u							/*Int2 Sense control bit*/

#endif
