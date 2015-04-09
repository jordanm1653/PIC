/*
 * Interrupts.c
 *
 * Demonstraton code describing the process of using interrupts
 * 
 * CHIP: PIC 18F4685
 * COMPILER: mplab c18
 *
 * DATE CREATED: 04.22.2013
 * AUTHOR: Jordan Millington
 */

#include <p18f4685.h>	/* Chip Library */

/*
 * Pre-proccessor Configurations
 * @ MCLRE - Master clear enable
 * @ WDT - Watch dog timer
 * @ OSC - Oscillator
 * @ LVP - Low voltage programming
 * @ PBADEN - Port B analog to digital enable
 */
#pragma config MCLRE=OFF, WDT=OFF, OSC=IRCIO67, LVP=OFF, PBADEN=OFF

/*
 * Interrupt Service Routine
 * Any interrupt will be directed here
 */
#pragma interrupt my_isr
void my_isr (void)
{

	/* Check for Port B interrupt flag (RBIF) */
	if(INTCONbits.RBIF==1){

		//Some Code

		/*
		 * Clear interrupt flag
		 */
		INTCONbits.RBIF=0;
	}
}

/* 
 * Pre-processor declaration of interrupt vector
 * memory address: 0x0008
 */
#pragma code high_vector=0x0008
void my_hivect_int (void)
{
	/*
	 * Inline assembly to save space in memory
	 * GOTO interrupt service routine
	 */
	_asm
	GOTO my_isr
	_endasm
}

/*
 * Pre-processor - Declare beginning of code
 */
#pragma code

void main (void)
{
	/*
	 * INTERRUPT INITIALIZATION
	 * INTCON Register:
	 * @ RBIE:	Enable PORTB change interrupts
	 * @ PEIE:	Enable peripheral inturrupts
	 * @ GIE:	Enable global interrupts
	 * INTCON2 Register:
	 * @ RBPU:	Enable pull up resistors
	 */
	INTCONbits.RBIE=1;
	INTCONbits.PEIE=1;
	INTCONbits.GIE=1;
	INTCON2bits.RBPU=0;

	while(1){

		/* Some Code */
	}
	while(1);
}
