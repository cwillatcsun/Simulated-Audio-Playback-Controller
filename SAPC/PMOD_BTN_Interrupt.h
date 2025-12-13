

#include "TM4C123GH6PM.h"

void PMOD_BTN_Interrupt_Init(void(*task)(uint8_t));

uint8_t PMOD_BTN_Read(void);

void GPIOA_Handler(void);

extern void (*PMOD_BTN_Task)(uint8_t pmod_btn_state);

