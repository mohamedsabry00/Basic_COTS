#ifndef UART_CFG_H
#define UART_CFG_H

/*Configure the oscillator frequency*/
#define OSCILLATOR_FREQUENCY							16000000u

#define TIMEOUT_VALUE									40000u

/*Configure the Synchronization mode of operation, options: 1- ASYNCHRONOUS
 * 															2- SYNCHRONOUS*/
#define SYNCHRONIZATION									ASYNCHRONOUS

/*Configure the Transferring relationship of data, options: 1- TRANSMITTER_ONLY
 * 															2- RECEIVER_ONLY
 * 															3- TRANSMITTER_RECEIVER */
#define TRANSFERSHIP									TRANSMITTER_RECEIVER

/*Configure the Receive complete interrupt status, options: 1- RX_COMPLETE_INT_ENABLED
 * 															 2- DISABLED*/
#define	RECEIVE_COMPLETE_INT							DISABLED

/*Configure the Transmit complete interrupt status, options: 1- TX_COMPLETE_INT_ENABLED
 * 															 2- DISABLED*/
#define	TRANSMIT_COMPLETE_INT							DISABLED

/*Configure the Data register empty interrupt status, options: 1- DATAREG_EMPTY_INT_ENABLED
 * 															   2- DISABLED*/
#define	DATA_REG_EMPTY_INT								DISABLED

/*Configure the Character size number, options: 1- FIVE_BIT
 * 												2- SIX_BIT
 * 												3- SEVEN_BIT
 * 												4- EIGHT_BIT
 * 												5- NINE_BIT*/
#define CHARACTER_SIZE									EIGHT_BIT

/*Configure the Double Transmission Speed status, options: 1- ENABLED
 * 														   2- DISABLED*/
#define DOUBLE_TRANSMISSION_SPEED						DISABLED

/*Configure your desired baud rate*/
#define BAUD_RATE										9600u

/*Configure the parity mode, options:	1- DISABLE_PARITY
 * 										2- EVEN_PARITY
 * 										3- ODD_PARITY */
#define PARITY_MODE										DISABLE_PARITY

/*Configure the number of stop bits, options:	1- ONE_BIT
 * 												2- TWO_BIT*/
#define STOP_BITS										ONE_BIT

/*Configure the Clock Polarity, options: 1- RISING_ON_TRANSMIT_FALLING_ON_RECEIVE
 * 										 2- FALLING_ON_TRANSMIT_RISING_ON_RECEIVE*/
#define CLOCK_POLARITY									RISING_ON_TRANSMIT_FALLING_ON_RECEIVE

#endif
