#ifndef CLCD_PRV_H
#define CLCD_PRV_H


#define  FOUR_BIT    1u
#define  EIGHT_BIT   2u

#define  GND_CONNECTED	1u
#define  DIO_CONNECTED	2u

#if CLCD_u8BITMODE == FOUR_BIT
static void voidSetHalfDataPort(uint8 Copy_u8Data);
#endif


static void voidSendEnablePulse(void);

#endif
