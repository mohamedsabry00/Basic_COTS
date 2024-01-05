#ifndef WDT_INTERFACE_H
#define WDT_INTERFACE_H

typedef enum{
	T_16_3_ms = 0u,
	T_32_5_ms = 1u,
	T_65_ms = 2u,
	T_130_ms = 3u,
	T_260_ms = 4u,
	T_520_ms = 5u,
	T_1000_ms = 6u,
	T_2100_ms = 7u
}WDT_TIME_t;


uint8 WDT_u8SetTime(WDT_TIME_t Copy_Time);

void WDT_voidEnable(void);

void WDT_voidDisable(void);

void WDT_voidReset(void);

#endif
