/**
 * @file UART0.c
 *
 * @brief Source code for the UART0 driver.
 *
 * This file contains the function definitions for the UART0 driver.
 *
 * @note For more information regarding the UART module, refer to the
 * Universal Asynchronous Receivers / Transmitters (UARTs) section
 * of the TM4C123GH6PM Microcontroller Datasheet.
 *   - Link: https://www.ti.com/lit/gpn/TM4C123GH6PM
 *
 * @note Assumes that the frequency of the system clock is 50 MHz.
 *
 * @author Aaron Nanas
 * @editor Cameron Williams
 */

#include "UART0.h"

void UART0_Init(void)
{
	// Enable the clock to the UARTO module by setting the
	// RO bit (Bit 0) in the RCGCUART register
	SYSCTL->RCGCUART |= 0x01;
	
	// Enable the clock to Port A by setting the
	// R0 bit (Bit 0) in the RCGCGPIO register
	SYSCTL->RCGCGPIO |= 0x01;
	
	// Disable the UARTO module before configuration by clearing
	// the UARTEN bit (Bit 0) in the CTL register
	UART0->CTL &= ~0x0001;
	
	// Configure the UARTO module to use the system clock (50 MHz)
	// divided by 16 by clearing the HSE bit (Bit 5) in the CTL register
	UART0->CTL &= ~0x0020;
	
	// Set the baud rate by writing to the DIVINT field (Bits 15 to 0)
	// and the DIVFRAC field (Bits 5 to 0) in the IBRD and FBRD registers, respectively.
	// The integer part of the calculated constant will be written to the IBRD register,
	// while the fractional part will be written to the FBRD register.
	// BRD = (System Clock Frequency) / (16 * Baud Rate)
	// BRDI = (50,000,000) / (16 * 115200) = 27.12673611 (IBRD = 27)
	// BRDF = ((0.12673611 * 64) + 0.5) = 8.611 (FBRD = 8)
	UART0->IBRD = 27;
	UART0->FBRD = 8;
	
	// Write the rest of the initialization function below
	// Refer to the Pre-Lab section.
	// Configure the data length of the UART packet to be 8 bits by writing a value of
	// 0x3 to the WLEN field (Bits 6 to 5) in the LCRH register.
	UART0->LCRH |= 0x60;
	
	// Enable the Transmit FIFO and the Receive FIFO by setting the FEN bit (Bit 4)
	// in the LCRH register.
	UART0->LCRH |= 0x10;
	
	// Select one stop bit to be transmitted at the end of a UART frame by clearing
	// the STP2 bit (Bit 3) in the LCRH register.
	UART0->LCRH &= ~0x08;
	
	// Disable the parity bit by clearing the PEN bit (Bit 1) in the LCRH register.
	UART0->LCRH &= ~0x02;
	
	// Enable the UART0 module after configuration by setting the UARTEN bit
	// (Bit 0) in the CTL register.
	UART0->CTL |= 0x01;
	
	// Select the alternate function for the PA1 and PA0 pins by setting Bits 1 to 0
	// in the AFSEL register. The pins will be configured as TX and RX pins, respectively.
	GPIOA->AFSEL |= 0x03;
	
	// Clear the PMC1 (Bits 7 to 4) and PMC0 (Bits 3 to 0) fields in the PCTL register
	// for Port A before configuration.
	GPIOA->PCTL &= ~0x000000FF;
	
	// Configure the PA1 pin to operate as a U0TX pin by writing 0x1 to the PMC1
	// field (Bits 7 to 4) in the PCTL register.
	GPIOA->PCTL |= 0x00000010;
	
	// Configure the PA0 pin to operate as a U0RX pin by writing 0x1 to the
	// PMC0 field (Bits 3 to 0) in the PCTL register.
	GPIOA->PCTL |= 0x00000001;
	
	// Enable the digital functionality for the PA1 and PA0 pins by setting Bits
	// 1 to 0 in the DEN register.
	GPIOA->DEN |= 0x03;

}

char UART0_Input_Character(void)
{	
	while((UART0->FR & UART0_RECEIVE_FIFO_EMPTY_BIT_MASK) != 0);
	
	return (char)(UART0->DR & 0xFF);
}

void UART0_Output_Character(char data)
{
	while((UART0->FR & UART0_TRANSMIT_FIFO_FULL_BIT_MASK) != 0);
	
	UART0->DR = data;
}

void UART0_Input_String(char *buffer_pointer, uint16_t buffer_size) 
{
	int length = 0;
	char character = UART0_Input_Character();
	
	while (character != UART0_CR)
	{
		if (character == UART0_BS)
		{
			if (length)
			{
				buffer_pointer--;
				length--;
				UART0_Output_Character (UART0_BS);
			}
		}
		else if (length < buffer_size)
		{
			*buffer_pointer = character;
			buffer_pointer++;
			length++;
			UART0_Output_Character (character);
		}
		character = UART0_Input_Character();
	}
	*buffer_pointer = 0;
}

void UART0_Output_String(char *pt)
{
	while (*pt)
	{
		UART0_Output_Character(*pt);
		pt++;
	}
}

uint32_t UART0_Input_Unsigned_Decimal(void)
{
	uint32_t number = 0;
	uint32_t length = 0;
	char character = UART0_Input_Character();
	// Accepts until <enter> is typed
	// The next line checks that the input is a digit, 0-9.
	// If the character is not 0-9, it is ignored and not echoed
	while (character != UART0_CR)
	{
    if ((character >= '0') && (character <= '9'))
    {
			// "number" will overflow if it is above 4,294,967,295
			number = (10 * number) + (character - '0');
			length++;
			UART0_Output_Character(character);
    }
    // If the input is a backspace, then the return number is
    // changed and a backspace is outputted to the screen
		else if ((character == UART0_BS) && length)
    {
			number /= 10;
			length--;
			UART0_Output_Character(character);
    }
    character = UART0_Input_Character();
	}
	return number;
}

void UART0_Output_Unsigned_Decimal(uint32_t n)
{
	// Use recursion to convert decimal number
	// of unspecified length as an ASCII string
	if (n >= 10)
	{
		UART0_Output_Unsigned_Decimal (n / 10);
		n = n % 10;
	}
	// n is between 0 and 9
	UART0_Output_Character (n + '0');
}

void UART0_Output_Newline(void)
{
	UART0_Output_Character (UART0_CR);
	UART0_Output_Character (UART0_LF);
}
