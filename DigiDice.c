/************************************************
*	Digital Dice Source Code
*	Jordan Millington
*	Modified from Zach Athertons Original Code
*	
*	Code verified: 03/24/13
*
*	------------------------------------
*
*	Initital Setups:
*	-Set the chip to a blazing 32MHz, this is for the timer operation in getting a "random number"
*	-Make all of Port B pins digital as to remove any issue
*	-Enable Port B Pull up resistors so that the button sinks the input pin when pressed.
*	-Start timer 3 - this will be running all the time at the clock frequency... more on this later
*	
*	Getting a "Random Number":
*	-As soon as button has been pressed grab the first 3 insignificant bits of the current timer3 value
*		With the timer running at clock speed, the lowest bits are the quickest changing therefore less
*		likely to have any "pattern". 
*		The 3 least significant bits give me 0-7, I need 0-5 for numbers in the dice array.
*	-Keep grabbing the timer value until it is a number between 0-5 (the do while loop)
*	-After I grab a legitimate dice number, store it then just cycle through all the dice numbers on the 
*		display until the button is released.
*	-After the button has been released, cycle through a coulple more times then show the stored "roll" value.
*
*************************************************/
#include <p18f2685.h>
//#include <P18f2620.h>

#include <stdlib.h>

#pragma config MCLRE=OFF, OSC=IRCIO67, LVP=OFF, PBADEN=OFF, WDT=ON //pragma for PIC18f2685

//#pragma config MCLRE=OFF, OSC=INTIO67, LVP=OFF, PBADEN=OFF, WDT=ON //pragma for PIC18F2620

#pragma config WDTPS=64

#define Button PORTBbits.RB0

unsigned char diceval[] = {0b01000000,0b10000001,0b11000001,0b10001101,0b11001101,0b10111111};
unsigned int rollspd,l,i,j;
unsigned char val;
unsigned char x;
unsigned char myval;

void main (void){

    OSCCON=0b01110011;						//Speed up and run 'stable'
    OSCTUNEbits.PLLEN=1;					//32MHz whoa
    ADCON1=0x0f;                            //All digital, had trouble with one light
    INTCON2bits.RBPU=0;                     //Pull up them pins!
    T3CONbits.TMR3ON = 1;                   //Start timer
    TRISA=0x00;                             //PortA all outputs for the LEDs
    PORTA=0x0f;                             //PortA all high just in case
    TRISB=0xff;                             //PortB inputs for the push button
    j=5000;                                 //How long does it take to see? Look below
    PORTA=0xff;                             //Initial state
    while(0){
        PORTA=diceval[2];
    }
    while(1){
        while(Button == 1){                 //Wait for button to be pressed... do it
            _asm
            CLRWDT
            _endasm
        }
		while(Button == 0){                 //Oh Snap! Button is pressed!
            _asm
            CLRWDT
            _endasm
			
            do{                             //Do as I say!
                val = TMR3L&0b00000111;		//Get a random number
            }while(val>5);                  //Wait for a legit dice roll
			
            x++;                            //'Roll' dice while button is down
            if(x>5)x=0;                     //5 High No More!
            myval = diceval[x];             //Where am I?
            PORTA=myval;                   	//Show current 'roll'
            for (i=0;i<10000;i++);          //Slow down I cant see!
        }
        for (l=0;l<5;l++){					//Roll is done, show a fake roll
            for(x=0;x<6;x++){
                _asm
                CLRWDT
                _endasm
                PORTA=diceval[x];			//Roll some dice
                for (i=0;i<j;i++);			//Slow down I cant see!
                }
            }
        PORTA=diceval[val];                 //Show the real final result without knowing
    }
}