/******************************************************************
 
 *	Lab 9 - Interfacing 3x4 matrix keypad using interrupts
 
 *	Jordan Millington
 *	Keypad:				96AB2-102-R										
 *	4 Digit 7 segment:	LDQ-M286RI - Common (+)		
 
 *****************************************************************/	

//#include <p18f4580.h>				//Tell compiler which chip I am using
#include <p18f4685.h>

/*
 *	CONFIG SETTINGS
 *
 *	Turn off Master Clear
 *	Enable the internal Oscillator 
 *	Disable low voltage programming to prevent noise
 *	Disable watch dog timer
 *	Disable PORTB analog to digital conversion
 */

#pragma config MCLRE=OFF, OSC=IRCIO67, PWRT=OFF, WDT=OFF, BOREN=OFF, LVP=OFF, PBADEN=OFF, DEBUG=OFF,LPT1OSC = OFF

/*
 *
 *	Below is the array for displaying digits on the 7 segment 
 *	display.
 *	The display used shares common (+), Voltage provided from 
 *	PORTC.
 *	Writing 0 to a pin on PORTD will turn on the corresponding 
 *	segment.
 *	The segments are arranged A-G & Decimal Point: A->RD7 D.P.->RD0.
 *
 */
unsigned char myarray [17] = {0b00000010,0b10011111,0b00100101,0b00001101,
							  0b10011001,0b01001001,0b11000001,0b00011111,
							  0b00000001,0b00011001,0b00010001,0b11000001,
							  0b11100101,0b10000101,0b01100001,0b01110001,
							  0b11111111};

/* Matrix array for my keypad isr.*/

unsigned char mybutton [4][4] = {1,2,3,10, 
								 4,5,6,11, 
								 7,8,9,12,
								 0,0,0,13};

unsigned char key,i;


#pragma interrupt my_isr				//"My Interrupt Service Routine
void my_isr (void){						//Handle the interrupt
//When any interrupt occurs the code comes here. Here you will need to determine
//which flag cause the interrupt and handle it from there.
if(INTCONbits.RBIF==1){
	PORTBbits.RB1=1;
	PORTBbits.RB2=1;
	PORTBbits.RB3=1;
	PORTBbits.RB0=0;
		if(PORTBbits.RB4==0) {key=mybutton[0][0]; while(PORTBbits.RB4==0);}	//1
		if(PORTBbits.RB5==0) {key=mybutton[0][1]; while(PORTBbits.RB5==0);}	//2
		if(PORTBbits.RB6==0) {key=mybutton[0][2]; while(PORTBbits.RB6==0);}	//3
		if(PORTBbits.RB7==0) {key=mybutton[0][3]; while(PORTBbits.RB7==0);}	//A
	PORTBbits.RB0=1;
	PORTBbits.RB1=0;
		if(PORTBbits.RB4==0) {key=mybutton[1][0]; while(PORTBbits.RB4==0);} //4
		if(PORTBbits.RB5==0) {key=mybutton[1][1]; while(PORTBbits.RB5==0);} //5
		if(PORTBbits.RB6==0) {key=mybutton[1][2]; while(PORTBbits.RB6==0);} //6
		if(PORTBbits.RB7==0) {key=mybutton[1][3]; while(PORTBbits.RB7==0);} //B
	PORTBbits.RB1=1;
	PORTBbits.RB2=0;
		if(PORTBbits.RB4==0) {key=mybutton[2][0]; while(PORTBbits.RB4==0);} //7
		if(PORTBbits.RB5==0) {key=mybutton[2][1]; while(PORTBbits.RB5==0);} //8
		if(PORTBbits.RB6==0) {key=mybutton[2][2]; while(PORTBbits.RB6==0);} //9
		if(PORTBbits.RB7==0) {key=mybutton[2][3]; while(PORTBbits.RB7==0);} //C
	PORTBbits.RB2=1;
	PORTBbits.RB3=0;
		if(PORTBbits.RB4==0) {key=mybutton[3][0]; while(PORTBbits.RB4==0);} //0
		if(PORTBbits.RB5==0) {key=mybutton[3][1]; while(PORTBbits.RB5==0);} //0
		if(PORTBbits.RB6==0) {key=mybutton[3][2]; while(PORTBbits.RB6==0);} //0
		if(PORTBbits.RB7==0) {key=mybutton[3][3]; while(PORTBbits.RB7==0);} //D

PORTB=0xf0;

INTCONbits.RBIF=0;
}
}


//Memory adress 0x0008 is reserved as the interrupt vector on the chip in hardware
//This vector is small so the function must be small.
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
	
	TRISB=0xF0;						//Set PORTB high inputs and PORTB low output
	PORTB=0xF0;						//Tie PORTB low bits to ground
	TRISD=0x00;						//Make PORTD outputs
	TRISC=0x00;						//Make PORTC outputs
	INTCON2bits.RBPU=0;				//Enable PORTB pull up resistors
	INTCONbits.RBIE=1;				//Enable the PORTB change interrupt
	INTCONbits.PEIE=1;				//Enable the periphrial interrupts
	INTCONbits.GIE=1;				//Enable all (global) interrupts

	while(1){
	PORTC=0x80;						//Turn on Digit 1 
	PORTD=myarray[key];				//Output 'key' to PORTB as a value 
	
	}		
}
