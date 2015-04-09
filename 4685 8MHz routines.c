/* Below are the lines to incclude in code to access the routines, copy
and paste!!! You need to copy and paste these so that the routines are declared in your main body of code.
Note that the ony ones that are actually declared in this file are the ones it calls within itself.

void delayms (unsigned long);			//Pass this routine the number of milliseconds to delay
void send(char);						//Pass the value to transmit serially
unsigned char getkey (void);			//Get the value of a key pressed
void serialconfig (void);				//This routine must be called before using any serial transmission
void delaymin (unsigned long);			//Delay for one minute per value sent
unsigned char holdkey (void);			//Constantly returns the current key being held
void rowtwo (void);						//Write a message over row two without clearing
void message (unsigned char []);		//Send an entire message as a string of unsigned characters
void pcmessage (unsigned char []);
void messageone (unsigned char [])		//Send a message to a first reciever
void messagetwo (unsigned char [])		//Send a message to a second reciever
unsigned char eepromread (unsigned int);//Return the value at EEPROM memory location passed to the function
void eepromwrite (unsigned char, unsigned int);	//Pass the function Data,Memorylocation to save the data
												//at the specified location.

Keypad is wirtten to be connected directly to portb

You should be able to change the include file and this code will work on any PIC18
*/
#include <p18f4685.h>
unsigned char key9;

void serialconfig (void)			//Set the chip up for serial transmission
	{
	OSCCON=0b01110000;							//8MHz
	TXSTA=0B00100100;							//Transmit set up							
	SPBRG=51;									//9600 bps
	TXSTAbits.TXEN=1;							//Enable the transmit pin
	RCSTAbits.SPEN=1;							//Enable transmission
	RCSTAbits.CREN=1;							//Enable reception
	TRISC=0b10000000;
}

void keyident2 (unsigned char, unsigned char);	//Keypad layout matrix
char row1 []= "_123A";
char row2 []= "_456B";
char row3 []= "_789C";
char row4 []= "_*0#D";

void delayms (unsigned long time)				//Call with number of ms to delay
	{
		unsigned long i;
		unsigned char j;
		for(i=0; i<time; i++)
			{
			//8 MHz j=130
			_asm
			CLRWDT
			_endasm
			for(j=0; j<130; j++);				//Tune the j comparison to fit your clock speed
		}
}
void delaymin (unsigned long minutes)				//Not fully tuned
	{
		unsigned long i;
		unsigned char j;
		unsigned char k;
		unsigned char l;
		for(i=0; i<minutes; i++)
			{
			for (j=0; k<60; k++)
				{
					for (l=0; l<1000; l++)
						{
						for(j=0; j<130; j++);				//Tune the j comparison to fit your clock speed
					}
			}
		}
}



void send(unsigned char key)								//Base of serial code, send the passed character
	{					
	while(PIR1bits.TXIF==0);					//Make sure/wait for the last byte to be sent
	TXREG=key;									//Load the character into the transmit register	
}


unsigned char getkey (void)								//This routine waits for a button to pressed and 
	{											//determines the row and colum, return with result in key
		key9=0;
		PORTBbits.RB1=1;
		PORTBbits.RB2=1;
		PORTBbits.RB3=1;
		PORTBbits.RB0=0;
			if(PORTBbits.RB4==0) {keyident2(4,4); while(PORTBbits.RB4==0);}
			if(PORTBbits.RB5==0) {keyident2(4,3); while(PORTBbits.RB5==0);}
			if(PORTBbits.RB6==0) {keyident2(4,2); while(PORTBbits.RB6==0);}
			if(PORTBbits.RB7==0) {keyident2(4,1); while(PORTBbits.RB7==0);}
		PORTBbits.RB0=1;
		PORTBbits.RB1=0;
			if(PORTBbits.RB4==0) {keyident2(3,4); while(PORTBbits.RB4==0);}
			if(PORTBbits.RB5==0) {keyident2(3,3); while(PORTBbits.RB5==0);}
			if(PORTBbits.RB6==0) {keyident2(3,2); while(PORTBbits.RB6==0);}
			if(PORTBbits.RB7==0) {keyident2(3,1); while(PORTBbits.RB7==0);}
		PORTBbits.RB1=1;
		PORTBbits.RB2=0;
			if(PORTBbits.RB4==0) {keyident2(2,4); while(PORTBbits.RB4==0);}
			if(PORTBbits.RB5==0) {keyident2(2,3); while(PORTBbits.RB5==0);}
			if(PORTBbits.RB6==0) {keyident2(2,2); while(PORTBbits.RB6==0);}
			if(PORTBbits.RB7==0) {keyident2(2,1); while(PORTBbits.RB7==0);}
		PORTBbits.RB2=1;
		PORTBbits.RB3=0;
			if(PORTBbits.RB4==0) {keyident2(1,4); while(PORTBbits.RB4==0);}
			if(PORTBbits.RB5==0) {keyident2(1,3); while(PORTBbits.RB5==0);}
			if(PORTBbits.RB6==0) {keyident2(1,2); while(PORTBbits.RB6==0);}
			if(PORTBbits.RB7==0) {keyident2(1,1); while(PORTBbits.RB7==0);}
		return key9;
}

unsigned char holdkey (void)					//This routine waits for a button to pressed and 
	{											//determines the row and colum, return with result in key
		key9=0;
		PORTBbits.RB1=1;
		PORTBbits.RB2=1;
		PORTBbits.RB3=1;
		PORTBbits.RB0=0;
			if(PORTBbits.RB4==0) {keyident2(4,4);}
			if(PORTBbits.RB5==0) {keyident2(4,3);}
			if(PORTBbits.RB6==0) {keyident2(4,2);}
			if(PORTBbits.RB7==0) {keyident2(4,1);}
			return key9;
		PORTBbits.RB0=1;
		PORTBbits.RB1=0;
			if(PORTBbits.RB4==0) {keyident2(3,4);}
			if(PORTBbits.RB5==0) {keyident2(3,3);}
			if(PORTBbits.RB6==0) {keyident2(3,2);}
			if(PORTBbits.RB7==0) {keyident2(3,1);}
			return key9;
		PORTBbits.RB1=1;
		PORTBbits.RB2=0;
			if(PORTBbits.RB4==0) {keyident2(2,4);}
			if(PORTBbits.RB5==0) {keyident2(2,3);}
			if(PORTBbits.RB6==0) {keyident2(2,2);}
			if(PORTBbits.RB7==0) {keyident2(2,1);}
			return key9;
		PORTBbits.RB2=1;
		PORTBbits.RB3=0;
			if(PORTBbits.RB4==0) {keyident2(1,4);}
			if(PORTBbits.RB5==0) {keyident2(1,3);}
			if(PORTBbits.RB6==0) {keyident2(1,2);}
			if(PORTBbits.RB7==0) {keyident2(1,1);}
		return key9;
}

void keyident2 (unsigned char row, unsigned char col)
	{
	if (row==1) key9=row1[col];					//These rows determine the key based on row and colum
	if (row==2) key9=row2[col];
	if (row==3) key9=row3[col];
	if (row==4) key9=row4[col];
	delayms(20);
}

void pcmessage (unsigned char display[])	//This routine displays an entire string of ASCII characters
	{									//which are terminated by the ascii null symbol. Simply pass it the
	unsigned char i;					//name of the string without brackets. Function declaration must have
	send (0x0D);
	send (0x0A);
	i=0;
	while ((display[i])!=0x00)
		{
		send (display[i]);
		i++;
	}

}	
	
void message (unsigned char display[])	//This routine displays an entire string of ASCII characters
	{									//which are terminated by the ascii null symbol. Simply pass it the
	unsigned char i;					//name of the string without brackets. Function declaration must have
	send (0xfe);						//Brackets as shown in function definition.
	send (0x01);
	i=0;
	while ((display[i])!=0x00)
		{
		send (display[i]);
		i++;
	}

}
void messageone (unsigned char display[])	//This routine displays an entire string of ASCII characters
	{									//which are terminated by the ascii null symbol. Simply pass it the
	unsigned char i;					//name of the string without brackets. Function declaration must have
	_asm
	BCF		PORTA,4,0
	_endasm

	send (0xfe);						//Brackets as shown in function definition.
	send (0x01);
	i=0;
	while ((display[i])!=0x00)
		{
		send (display[i]);
		i++;
	}
	_asm
	BCF		PORTA,4,0
	_endasm

}
void messagetwo (unsigned char display[])	//This routine displays an entire string of ASCII characters
	{									//which are terminated by the ascii null symbol. Simply pass it the
	unsigned char i;					//name of the string without brackets. Function declaration must have

	_asm
	BSF		PORTA,5,0
	_endasm

	send (0xfe);						//Brackets as shown in function definition.
	send (0x01);
	i=0;
	while ((display[i])!=0x00)
		{
		send (display[i]);
		i++;
	}
	_asm
	BCF		PORTA,5,0
	_endasm

}

void eepromwrite (unsigned char mydata, unsigned int address)
	{
	
	EEADRH=(address/0x100);
	EEADR=address;
	EEDATA=mydata;
	EECON1bits.EEPGD=0;
	EECON1bits.CFGS=0;
	EECON1bits.WREN=1;
	INTCONbits.GIE=0;
	EECON2=0x55;
	EECON2=0xAA;
	EECON1bits.WR=1;
	while(EECON1bits.WR);
	EECON1bits.WREN=0;	
	INTCONbits.GIE=1;
 }

unsigned char eepromread (unsigned int address)
	{
	EEADR=address;

	EEADRH=(address/0x100);

	EECON1bits.EEPGD=0;
	EECON1bits.CFGS=0;
	EECON1bits.RD=1;
	return EEDATA;
}
