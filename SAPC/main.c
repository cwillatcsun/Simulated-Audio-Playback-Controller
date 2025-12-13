/*
 * @file main.c
 *
 * @brief Main source code for the Simulated Audio Playback Controller
 *
 * @author Cameron Williams
 */

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "UART0.h"
#include "PMOD_BTN_Interrupt.h"
#include "UART1.h"
#include "string.h"
#include "GPIO.h"

static int s;
static int m;
static uint8_t pausecheck = 0;
static uint8_t counter = 0;

// Declare the user-defined function prototype for PMOD_BTN
void PMOD_BTN_Int_Handler(uint8_t pmod_button_status)
{
	switch(pmod_button_status)
  {
		// BTN0 (PA2) is pressed, restarting the playback
		case 0x04:
		{
			counter = 8;
			EduBase_LEDs_Output(counter);
			s = 0;
			m = 0;
			SysTick_Delay1ms(500); //simulated buffering
			break;
		}

		// BTN1 (PA3) is pressed, skipping ten seconds back
		case 0x08:
		{
			s = s-10;
			counter = 4;
			EduBase_LEDs_Output(counter);
			break;
		}
		
		// BTN2 (PA4) is pressed, pausing or playing the playback
		case 0x10:
		{
			if (pausecheck == 0) {
				counter = 2;
				pausecheck = 1;
			}
			else if (pausecheck == 1) {
				pausecheck = 0;			
				counter = 0;
			}
			break;
		}

		// BTN3 (PA5) is pressed, skipping ten seconds forward
		case 0x20:
		{
			s = s+10;
			counter = 1;
			EduBase_LEDs_Output(counter);
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	// Indicates whether the user is restarting or skipping when paused by ensuring the pause LED stays lit.
	if ((counter == 8 | counter == 4 | counter == 1) && pausecheck == 1) {
		SysTick_Delay1ms(200);
		counter = counter + 2;
	}
	else if ((counter == 8 | counter == 4 | counter == 1) && pausecheck == 0) {
		SysTick_Delay1ms(200);
		counter = 0;
	}
	
	EduBase_LEDs_Output(counter);
}

int main(void)
{
	SysTick_Delay_Init();
	
	UART0_Init();
	
	RGB_LED_Init();
	
	// Initialize the LEDs on the EduBase board (Port B)
	EduBase_LEDs_Init();

	// Call 
	PMOD_BTN_Interrupt_Init(&PMOD_BTN_Int_Handler);
	
	while (1) {
		while (pausecheck == 0) {
			if (m < 3) {	
				if (s == 59) {
					m++;
					s = 0;
				}
				else if (s < 0 & m == 0) {
					s = 0;
				}
				else if (s < 0 & m > 0) {
					m--;
					s = 60+s;
				}
				else if (s > 59) {
					m++;
					s = s-60;
				}
				else
					s++;
				
				if (m == 3) {
					UART0_Output_String("End of File");
					UART0_Output_Newline();
					break;
				}
				else if (m < 0)
					m = 0;
				
				
				UART0_Output_String("Playing -- ");
				UART0_Output_Unsigned_Decimal(m);
				UART0_Output_String(":");
				if (s < 10)
					UART0_Output_String("0");
				UART0_Output_Unsigned_Decimal(s); 
				UART0_Output_Newline();
				SysTick_Delay1ms(200);
			}
		}
		
		while (pausecheck == 1) {
			if (s > 60) {
				m++;
				s = s-60;
			}
			else if (s < 0 & m > 0) {
					m--;
					s = 60+s;
			}
			else if (m == 3) {
				m = 0;
				s = 0;
				UART0_Output_String("End of File");
				UART0_Output_Newline();
				break;
			}
			else if (m < 0)
				m = 0;			
		}
	}
}