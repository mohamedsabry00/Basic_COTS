#ifndef TWI_REG_H
#define TWI_REG_H

/*TWI Bit Rate Register*/
#define TWBR				*((volatile uint8*) 0x20)

/*TWI Control Register*/
#define TWCR				*((volatile uint8*) 0x56)
#define TWCR_TWIE			0u /*Interrupt Enable*/
#define TWCR_TWEN			2u /*Enable*/
#define TWCR_TWWC			3u /*Write Collision*/
#define TWCR_TWSTO			4u /*Stop Condition*/
#define TWCR_TWSTA			5u /*Start Condition*/
#define TWCR_TWEA			6u /*Enable Acknowledge*/
#define TWCR_TWINT			7u /*Interrupt Flag*/

/*TWI Status Register*/
#define TWSR				*((volatile uint8*) 0x21)
#define TWSR_TWPS0			0u
#define TWSR_TWPS1			1u

/*TWI Data Register*/
#define TWDR				*((volatile uint8*) 0x23)

/*TWI Address Register*/
#define TWAR				*((volatile uint8*) 0x22)
#define TWAR_TWGCE			0u /*General Call recognition Enable*/

#endif
