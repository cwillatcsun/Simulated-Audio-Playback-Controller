/**
 * @file UART1.c
 *
 * @brief Source code for the UART1 driver.
 *
 * This file contains the function definitions for the UART1 driver.
 *
 * @note For more information regarding the UART module, refer to the
 * Universal Asynchronous Receivers / Transmitters (UARTs) section
 * of the TM4C123GH6PM Microcontroller Datasheet.
 *   - Link: https://www.ti.com/lit/gpn/TM4C123GH6PM
 *
 * @note Assumes that the frequency of the system clock is 50 MHz.
 *
 * @author Cameron Williams and Ashraf Abdelgawad
 */

/*
#include "UART1.h"

void UART1_Init(void)
{
	// Enable the clock to the UART1 module by setting the
	// R1 bit (Bit 1) in the RCGCUART register
	SYSCTL->RCGCUART |= 0x02;
	
	// Enable the clock to Port A by setting the
	// R1 bit (Bit 1) in the RCGCGPIO register
	SYSCTL->RCGCGPIO |= 0x02;
	
	// Disable the UART1 module before configuration by clearing
	// the UARTEN bit (Bit 0) in the CTL register
	UART1->CTL &= ~0x0001;
	
	// Configure the UART1 module to use the system clock (50 MHz)
	// divided by 16 by clearing the HSE bit (Bit 5) in the CTL register
	UART1->CTL &= ~0x0020;
	
	// Set the baud rate by writing to the DIVINT field (Bits 15 to 0)
	// and the DIVFRAC field (Bits 5 to 0) in the IBRD and FBRD registers, respectively.
	// The integer part of the calculated constant will be written to the IBRD register,
	// while the fractional part will be written to the FBRD register.
	// BRD = (System Clock Frequency) / (16 * Baud Rate)
	// BRDI = (50,000,000) / (16 * 115200) = 325.5208333 (IBRD = 325)
	// BRDF = ((0.5208333 * 64) + 0.5) = 33.8333312 (FBRD = 33)
	UART1->IBRD = 325;
	UART1->FBRD = 33;
	
	// Write the rest of the initialization function below
	// Refer to the Pre-Lab section.
	// Configure the data length of the UART packet to be 8 bits by writing a value of
	// 0x3 to the WLEN field (Bits 6 to 5) in the LCRH register.
	UART1->LCRH |= 0x60;
	
	// Enable the Transmit FIFO and the Receive FIFO by setting the FEN bit (Bit 4)
	// in the LCRH register.
	UART1->LCRH |= 0x10;
	
	// Select one stop bit to be transmitted at the end of a UART frame by clearing
	// the STP2 bit (Bit 3) in the LCRH register.
	UART1->LCRH &= ~0x08;
	
	// Disable the parity bit by clearing the PEN bit (Bit 1) in the LCRH register.
	UART1->LCRH &= ~0x02;
	
	// Enable the UART1 module after configuration by setting the UARTEN bit
	// (Bit 0) in the CTL register.
	UART1->CTL |= 0x01;
	
	// Select the alternate function for the PB1 and PB0 pins by setting Bits 1 to 0
	// in the AFSEL register. The pins will be configured as TX and RX pins, respectively.
	GPIOB->AFSEL |= 0x03;
	
	// Clear the PMC1 (Bits 7 to 4) and PMC0 (Bits 3 to 0) fields in the PCTL register
	// for Port B before configuration.
	GPIOB->PCTL &= ~0x000000FF;
	
	// Configure the PB1 pin to operate as a U1TX pin by writing 0x1 to the PMC1
	// field (Bits 7 to 4) in the PCTL register.
	GPIOB->PCTL |= 0x00000010;
	
	// Configure the PB0 pin to operate as a U1RX pin by writing 0x1 to the
	// PMC0 field (Bits 3 to 0) in the PCTL register.
	GPIOB->PCTL |= 0x00000001;
	
	// Enable the digital functionality for the PB1 and PB0 pins by setting Bits
	// 1 to 0 in the DEN register.
	GPIOB->DEN |= 0x03;
}
char UART1_Input_Character(void)
{	
	while((UART1->FR & UART1_RECEIVE_FIFO_EMPTY_BIT_MASK) != 0);
	
	return (char)(UART1->DR & 0xFF);
}

void UART1_Output_Character(char data)
{
	while((UART1->FR & UART1_TRANSMIT_FIFO_FULL_BIT_MASK) != 0);
	
	UART1->DR = data;
}

void UART1_Input_String(char *buffer_pointer, uint16_t buffer_size) 
{
	int length = 0;
	char character = UART1_Input_Character();
	
	while (character != UART1_CR)
	{
		if (character == UART1_BS)
		{
			if (length)
			{
				buffer_pointer--;
				length--;
				UART1_Output_Character (UART1_BS);
			}
		}
		else if (length < buffer_size)
		{
			*buffer_pointer = character;
			buffer_pointer++;
			length++;
			UART1_Output_Character (character);
		}
		character = UART1_Input_Character();
	}
	*buffer_pointer = 0;
}

void UART1_Output_String(char *pt)
{
	while (*pt)
	{
		UART1_Output_Character(*pt);
		pt++;
	}
}


void UART1_Output_Newline(void)
{
	UART1_Output_Character (UART1_CR);
	UART1_Output_Character (UART1_LF);
}
*/
