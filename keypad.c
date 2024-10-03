#include <lpc21xx.h>
#include "defines.h"

/* Keypad pin connections */
//rows are connected to P1.16 to P1.19
#define row0 16
#define row1 17
#define row2 18
#define row3 19

//cols are connected to P1.20 to P1.23
#define col0 20
#define col1 21
#define col2 22
#define col3 23

//keypad lookup table
unsigned char keypad_lut[4][4] = {0,  1,  2,  3,
																	4,  5,  6,  7,
																	8,  9, 10, 11,
																 12, 13, 14, 15};

							
unsigned int colscan(void)																	
{
	unsigned int c0,c1,c2,c3,retval;
	
	c0 = READBIT(IOPIN1,col0); //reading column 0 status and store it in c0
	c1 = READBIT(IOPIN1,col1); //reading column 1 status and store it in c1
	c2 = READBIT(IOPIN1,col2); //reading column 2 status and store it in c2
	c3 = READBIT(IOPIN1,col3); //reading column 3 status and store it in c3
	
	retval = (c0&c1&c2&c3);
	return retval;
}


void initrows(void)
{
	WRITENIBBLE(IODIR1,row0,0x0F); 	//configuring the rows port pins as output port pins
	WRITENIBBLE(IOCLR1,row0,0x0F); 	//initially making all rows to zero
}


void initcols(void)
{
	WRITENIBBLE(IOSET1,col0,0x0F); 	//initially making all columns to one 
}


/* keyscan() function is used to find out the which switch 
it is pressed from user and return the equivalent value from keypad lookup table*/
unsigned char keyscan(void) //keyscan function definition
{
	unsigned char row,col;
	initrows();	//rows initialisation 
	initcols();	//columns initialisation
	
	while(colscan() == 1);	//waiting for switch press
	
	while(1)   //row identification process
	{
		SETBIT(IOCLR1,row0);
		SETBIT(IOSET1,row1);
		SETBIT(IOSET1,row2);
		SETBIT(IOSET1,row3);
		if(colscan() == 0)
		{
			row = 0;
			break;
		}
		
		SETBIT(IOCLR1,row1);
		SETBIT(IOSET1,row0);
		SETBIT(IOSET1,row2);
		SETBIT(IOSET1,row3);
		if(colscan() == 0)
		{
			row = 1;
			break;
		}
		
		SETBIT(IOCLR1,row2);
		SETBIT(IOSET1,row0);
		SETBIT(IOSET1,row1);
		SETBIT(IOSET1,row3);
		if(colscan() == 0)
		{
			row = 2;
			break;
		}
		SETBIT(IOCLR1,row3);
		SETBIT(IOSET1,row0);
		SETBIT(IOSET1,row1);
		SETBIT(IOSET1,row2);
		if(colscan() == 0)
		{
			row = 3;
			break;
		}
	}
	
	//column identification process
	if((READBIT(IOPIN1,col0)) == 0)
		col = 0;
	else if((READBIT(IOPIN1,col1)) == 0)
		col = 1;
	else if((READBIT(IOPIN1,col2)) == 0)
		col = 2;
	else if((READBIT(IOPIN1,col3)) == 0)
		col = 3;
	
	while(colscan() == 0);	//waiting for switch release
	
	return keypad_lut[row][col];	//return the switch equivalent value from defined keypad lookup table
}
