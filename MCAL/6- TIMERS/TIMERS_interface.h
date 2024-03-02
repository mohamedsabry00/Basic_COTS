#ifndef TIMERS_INTERFACE_H
#define TIMERS_INTERFACE_H

/*Wave Generation Mode Options for Timers 0 & 2*/
typedef enum{
	NORMAL = 0u,
	PHASE_CORRECT_PWM = 64u,
	CTC = 8u,
	FAST_PWM = 72u
}TIMER0_2_WGM_t;

/*Wave Generation Mode Options for Timers 1*/
typedef enum{
	NORMAL_MODE,
	PWM_PHASE_CORRECT_8BITS,
	PWM_PHASE_CORRECT_9BITS,
	PWM_PHASE_CORRECT_10BITS,
	CTC_OCR1ATOP,
	FAST_PWM_8BITS,
	FAST_PWM_9BITS,
	FAST_PWM_10BITS,
	PWM_PHASE_FREQUENCY_CORRECT_ICR1TOP,
	PWM_PHASE_FREQUENCY_CORRECT_OCR1ATOP,
	PWM_PHASE_CORRECT_ICR1TOP,
	PWM_PHASE_CORRECT_OCR1ATOP,
	CTC_ICR1TOP,
	FAST_PWM_ICR1TOP,
	FAST_PWM_OCR1ATOP
}TIMER1_WGM_t;

/*Clock Select Options for Timer 0 & 1*/
typedef enum{
	NO_CLK = 0u,
	CLK_1 = 1u,
	CLK_8 = 2u,
	CLK_64 = 3u,
	CLK_256 = 4u,
	CLK_1024 = 5u,
	EXT_CLK_FALLING_EDGE = 6u,
	EXT_CLK_RISING_EDGE = 7u
}TIMER0_1_CLK_t;

/*Clock Select Options for Timer 2*/
typedef enum{
	NO_SYS_CLK = 0u,
	SYS_CLK_1 = 1u,
	SYS_CLK_8 = 2u,
	SYS_CLK_32 = 3u,
	SYS_CLK_64 = 4u,
	SYS_CLK_128 = 5u,
	SYS_CLK_256 = 6u,
	SYS_CLK_1024 = 7u
}TIMER2_CLK_t;

/*Compare Output Mode for Timers 0 & 2 & OCR1B*/
typedef enum{
	FIRST_MODE = 0u,
	SECOND_MODE = 16u,
	THIRD_MODE = 32u,
	FOURTH_MODE = 48u
}TIMER0_2_OCM_t;

/*Compare Output Mode for Timers 1 OCR1A*/
typedef enum{
	FIRST_MODE_T1 = 0u,
	SECOND_MODE_T1 = 64u,
	THIRD_MODE_T1 = 128u,
	FOURTH_MODE_T1 = 192u
}TIMER1_OCM_t;

typedef enum{
	OCR1A_REG,
	OCR1B_REG
}TIMER1_COMP_REG_t;


typedef enum{
	FALLING,
	RISING
}InCapture_Trigger;

typedef enum{
	NO_INT_SOURCE = 0u,
	TIMER0_OVF_INT = 1u,
	TIMER0_OC_INT = 2u,
	TIMER1_OVF_INT = 4u,
	TIMER1_OCB_INT = 8u,
	TIMER1_OCA_INT = 16u,
	TIMER1_IC_INT = 32u,
	TIMER2_OVF_INT = 64u,
	TIMER2_OC_INT = 128u
}TIMER_INT_SRS_t;

typedef struct{
	TIMER0_2_WGM_t WGM;
	TIMER0_1_CLK_t CLKSelect;
	TIMER0_2_OCM_t OCM;
	TIMER_INT_SRS_t INTSource;
}Timer0_config_t;

typedef struct{
	TIMER1_WGM_t WGM;
	TIMER0_1_CLK_t CLKSelect;
	TIMER1_OCM_t OCMA;
	TIMER0_2_OCM_t OCMB;
	TIMER_INT_SRS_t INTSource;
}Timer1_config_t;

typedef struct{
	TIMER0_2_WGM_t WGM;
	TIMER2_CLK_t CLKSelect;
	TIMER0_2_OCM_t OCM;
	TIMER_INT_SRS_t INTSource;
}Timer2_config_t;

/*General functions to All Timers*/
void Timer_INTEnable(const TIMER_INT_SRS_t Copy_INTSource);

uint8 Timer_SetCallBack(uint8 Copy_u8IntSource,void(*Copy_pvCallBackFunc)(void));

void Timer_INTDisable(TIMER_INT_SRS_t Copy_INTSource);


/*Functions related to timer 0*/
uint8 Timer0_u8Init(const Timer0_config_t* Copy_Config);

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadValue);

void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompMatchValue);

uint8 Timer0_u8GetTimerValue(void);

void Timer0_voidSetPrescaler(TIMER0_1_CLK_t Copy_Clk);

void Timer0_voidSetWaveGenMode(TIMER0_2_WGM_t Copy_WGMode);

void Timer0_voidSetOutputCompMode(TIMER0_2_OCM_t Copy_OCMode);

/*-----------------------------------------------------------------------*/

/*Functions related to Timer 1*/

uint8 Timer1_voidInit(const Timer1_config_t* Copy_Config);

uint16 Timer1_u16GetTimerValue(void);

void Timer1_voidSetPreloadValue(uint16 Copy_u16Value);

void Timer1_voidSetICRPreloadValue(uint16 Copy_u16Value);

uint8 Timer1_voidSetCompareMatchValue(TIMER1_COMP_REG_t Copy_Register,uint8 Copy_u8CompMatchValue);

void Timer1_voidSetPrescaler(TIMER0_1_CLK_t Copy_Clk);

uint8 Timer1_voidSetWaveGenMode(TIMER1_WGM_t Copy_WGMode);

uint8 Timer1_voidSetOutputCompMode(TIMER1_COMP_REG_t Copy_Register,TIMER0_2_OCM_t Copy_OCMode);

void Timer1_voidEnableInCaptureNoiseCanceler(void);

void Timer1_voidDisableInCaptureNoiseCanceler(void);

uint8 Timer1_u8InptCaptureEdgeSelect(InCapture_Trigger Copy_u8TriggerEdge);

uint16 Timer1_GetICR1Value(void);

/*------------------------------------------------------------------------*/

/*Functions related to Timer 2*/
uint8 Timer2_u8Init(const Timer2_config_t* Copy_Config);

void Timer2_voidSetOutputCompMode(TIMER0_2_OCM_t Copy_OCMode);

void Timer2_voidSetWaveGenMode(TIMER0_2_WGM_t Copy_WGMode);

void Timer2_voidSetPrescaler(TIMER2_CLK_t Copy_Clk);

uint8 Timer2_u8GetTimerValue(void);

void Timer2_voidSetPreloadValue(uint8 Copy_u8PreloadValue);

void Timer2_voidSetCompareMatchValue(uint8 Copy_u8CompMatchValue);


#endif
