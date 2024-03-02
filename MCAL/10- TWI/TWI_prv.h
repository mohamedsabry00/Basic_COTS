#ifndef TWI_PRV_H
#define TWI_PRV_H

#define PRESCALER_BIT_MASK		0b11111100

#define STATUS_BIT_MASK			0b11111000

#define	MT_START 				0x08
#define	MT_REPEATED_START 		0x10
#define	MT_SLA_W_ACK 			0x18
#define	MT_SLA_R_ACK 			0x40
#define	MT_DATA_ACK 			0x28
#define	MR_DATA_ACK 			0x50
#define	MR_DATA_NACK 			0x58

#endif
