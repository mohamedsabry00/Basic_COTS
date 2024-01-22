#ifndef SPI_REG_H
#define SPI_REG_H


#define SPCR				*((volatile uint8*) 0x2D)
#define SPCR_SPIE			7u
#define SPCR_SPE			6u
#define SPCR_DORD			5u
#define SPCR_MSTR			4u
#define SPCR_CPOL			3u
#define SPCR_CPHA			2u

#define SPSR				*((volatile uint8*) 0x2E)
#define SPSR_SPIF			7u
#define SPSR_WCOL			6u
#define SPSR_SPI2X			0u

#define SPDR				*((volatile uint8*) 0x2F)


#endif
