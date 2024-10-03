#ifndef _UART0_H_
#define _UART0_H_

#define UART_INT_ENABLE 1

//PIN FUNCTIONS
#define TXD0_0_0 FUNC2
#define RXD0_0_1 FUNC2

//BAUD RATE CALCULATION & DIVISOR
#define FOSC      					12000000   //Hz
#define CCLK  	  					5*FOSC
#define PCLK  	  					CCLK/4
#define BAUD  	  					9600
#define DIVISOR   					(PCLK/(16 * BAUD))

//U0LCR BIT DEFINES
#define WORD_LEN_8           0x03 //8_BIT_DATA  
#define DLAB_BIT             7      

//U0LSR BIT DEFINES
#define DR_BIT                0
#define THRE_BIT              5
#define TEMT_BIT              6


void InitUART0(void); /* Initialize Serial Interface       */ 
void UART0_Tx(char ch);  
char UART0_Rx(void); 
void UART0_Str(char *);
void UART0_Str1(unsigned char);
void UART0_Int(unsigned int);
void UART0_Float(float);


#endif
