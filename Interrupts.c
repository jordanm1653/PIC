/******************************************************************
 *	Interrupts
 *--------------------
 *	Jordan Millington
 *	2013-04-22
 *
 *****************************************************************/	

#include <p18f4685.h>				//Tell compiler which chip I am using 


#pragma config MCLRE=OFF, WDT=OFF, OSC=IRCIO67, LVP=OFF, PBADEN=OFF



#pragma interrupt my_isr				//"My Interrupt Service Routine
void my_isr (void){						//Handle the interrupt
//When any interrupt occurs the code comes here. Here you will need to determine
//which flag cause the interrupt and handle it from there.
if(INTCONbits.RBIF==1){

	//Some Code
	
	INTCONbits.RBIF=0;			//Must be cleared in software
	}
}


#pragma code high_vector=0x0008		//Non-changeable intterupt vector at 0x0008
void my_hivect_int (void)
	{
	//Use an assembly command to save space in memory at 0x0008
	_asm
	GOTO my_isr						//Go to where i want to handle the interrupt
	_endasm

	}

#pragma code

void main (void){
	
	INTCON2bits.RBPU=0;				//Enable PORTB pull up resistors
	INTCONbits.RBIE=1;				//Enable the PORTB change interrupt
	INTCONbits.PEIE=1;				//Enable the periphrial interrupts
	INTCONbits.GIE=1;				//Enable all (global) interrupts

	while(1){
	
	//Some Code
	
	}	
	while(1);
}
