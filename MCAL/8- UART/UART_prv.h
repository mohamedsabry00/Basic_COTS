#ifndef UART_PRV_H
#define UART_PRV_H

#define ENABLED						                    1u
#define DISABLED						                    0u
#define RX_COMPLETE_INT_ENABLED			                    0b10000000u
#define TX_COMPLETE_INT_ENABLED			                    0b01000000u
#define DATAREG_EMPTY_INT_ENABLED		                    0b00100000u

#define ASYNCHRONOUS					                    0u
#define SYNCHRONOUS						                    0b01000000u


#define TRANSMITTER_ONLY				                    0b00001000u
#define RECEIVER_ONLY					                    0b00010000u
#define TRANSMITTER_RECEIVER			                    0b00011000u

#define FIVE_BIT						                    0u
#define SIX_BIT							                    2u
#define SEVEN_BIT						                    4u
#define EIGHT_BIT						                    6u
#define NINE_BIT						                    14u

#define DISABLE_PARITY					                    0u
#define EVEN_PARITY						                    0b00100000u
#define ODD_PARITY						                    0b00110000u

#define ONE_BIT							                    0u
#define TWO_BIT							                    0b00001000u

#define CHARACTER_SIZE_BITMASK			                    0b00000110

#define RISING_ON_TRANSMIT_FALLING_ON_RECEIVE				0u
#define FALLING_ON_TRANSMIT_RISING_ON_RECEIVE				1u

#define UBRRH_REGISTER_BITMASK								0b00001111u

#define IDLE												0u
#define BUSY												1u

static void voidASynchReceiveBufferISRHandler(void);

static void voidASynchSendBufferISRHandler(void);


#endif
