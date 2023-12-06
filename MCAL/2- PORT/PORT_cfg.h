#ifndef PORT_CFG_H
#define PORT_CFG_H

/*Configure the MCU Pins direction, options: 	1- INPUT	
												2- OUTPUT   */


#define PORTA_PIN0_DIR       OUTPUT
#define PORTA_PIN1_DIR       OUTPUT
#define PORTA_PIN2_DIR       OUTPUT
#define PORTA_PIN3_DIR       OUTPUT
#define PORTA_PIN4_DIR       OUTPUT
#define PORTA_PIN5_DIR       OUTPUT
#define PORTA_PIN6_DIR       OUTPUT
#define PORTA_PIN7_DIR       OUTPUT

#define PORTB_PIN0_DIR       OUTPUT
#define PORTB_PIN1_DIR       OUTPUT
#define PORTB_PIN2_DIR       OUTPUT
#define PORTB_PIN3_DIR       OUTPUT
#define PORTB_PIN4_DIR       INPUT
#define PORTB_PIN5_DIR       INPUT
#define PORTB_PIN6_DIR       INPUT
#define PORTB_PIN7_DIR       INPUT

#define PORTC_PIN0_DIR       OUTPUT
#define PORTC_PIN1_DIR       OUTPUT
#define PORTC_PIN2_DIR       OUTPUT
#define PORTC_PIN3_DIR       OUTPUT
#define PORTC_PIN4_DIR       OUTPUT
#define PORTC_PIN5_DIR       OUTPUT
#define PORTC_PIN6_DIR       OUTPUT
#define PORTC_PIN7_DIR       OUTPUT

#define PORTD_PIN0_DIR       OUTPUT
#define PORTD_PIN1_DIR       OUTPUT
#define PORTD_PIN2_DIR       OUTPUT
#define PORTD_PIN3_DIR       OUTPUT
#define PORTD_PIN4_DIR       OUTPUT
#define PORTD_PIN5_DIR       OUTPUT
#define PORTD_PIN6_DIR       OUTPUT
#define PORTD_PIN7_DIR       OUTPUT

/*Configure the initial state of the pin.
In case of INPUT, options : 1- FLOATING
							2- PULLED_UP 

In case of OUTPUT, optins : 1- HIGH
							2- LOW*/
#define PORTA_PIN0_INITIAL_VALUE       LOW
#define PORTA_PIN1_INITIAL_VALUE       LOW
#define PORTA_PIN2_INITIAL_VALUE       LOW
#define PORTA_PIN3_INITIAL_VALUE       LOW
#define PORTA_PIN4_INITIAL_VALUE       LOW
#define PORTA_PIN5_INITIAL_VALUE       LOW
#define PORTA_PIN6_INITIAL_VALUE       LOW
#define PORTA_PIN7_INITIAL_VALUE       LOW
									   
#define PORTB_PIN0_INITIAL_VALUE       LOW
#define PORTB_PIN1_INITIAL_VALUE       LOW
#define PORTB_PIN2_INITIAL_VALUE       LOW
#define PORTB_PIN3_INITIAL_VALUE       LOW
#define PORTB_PIN4_INITIAL_VALUE       PULLED_UP
#define PORTB_PIN5_INITIAL_VALUE       PULLED_UP
#define PORTB_PIN6_INITIAL_VALUE       PULLED_UP
#define PORTB_PIN7_INITIAL_VALUE	   PULLED_UP
									   
#define PORTC_PIN0_INITIAL_VALUE       LOW
#define PORTC_PIN1_INITIAL_VALUE       LOW
#define PORTC_PIN2_INITIAL_VALUE       LOW
#define PORTC_PIN3_INITIAL_VALUE       LOW
#define PORTC_PIN4_INITIAL_VALUE       LOW
#define PORTC_PIN5_INITIAL_VALUE       LOW
#define PORTC_PIN6_INITIAL_VALUE       LOW
#define PORTC_PIN7_INITIAL_VALUE       LOW
									   
#define PORTD_PIN0_INITIAL_VALUE       LOW
#define PORTD_PIN1_INITIAL_VALUE       LOW
#define PORTD_PIN2_INITIAL_VALUE       LOW
#define PORTD_PIN3_INITIAL_VALUE       LOW
#define PORTD_PIN4_INITIAL_VALUE       LOW
#define PORTD_PIN5_INITIAL_VALUE       LOW
#define PORTD_PIN6_INITIAL_VALUE       LOW
#define PORTD_PIN7_INITIAL_VALUE       LOW


#endif
