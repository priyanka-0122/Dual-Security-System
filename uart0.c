#include <LPC21xx.H>  /* LPC21xx definitions         */

#include "pin_function_defines.h"
#include "uart0.h"
#include "types.h"
#include "defines.h"

char rec_buff[25],dummy;
unsigned char k=0,ch1,r_flag;

extern unsigned char buf[25]; 

void UART0_isr(void) __irq
{
  if((U0IIR & 0x04)) //check if receive interrupt
  {
		ch1 = U0RBR;	/* Read to Clear Receive Interrupt */
		if(k<25)
			rec_buff[k++] = ch1; 
  }
  else
  {
      dummy=U0IIR; //Read to Clear transmit interrupt
  
  }
   VICVectAddr = 0; /* dummy write */
}


void InitUART0 (void) 						/*   Initialize Serial Interface     */ 
{  
  CFGPIN(PINSEL0,0,TXD0_0_0);   	/* Enable RxD0 and TxD0 */
	CFGPIN(PINSEL0,1,RXD0_0_1); 
  
	U0LCR=(1<<DLAB_BIT)|WORD_LEN_8; /* 8 bits, no Parity, 1 Stop bit */
  
	U0DLL = DIVISOR;           			/* 9600 Baud Rate @ CCLK/4 VPB Clock */
  U0DLM = DIVISOR>>8;
  
	CLRBIT(U0LCR,DLAB_BIT);         /* DLAB = 0  */
  
  #if UART_INT_ENABLE > 0

  VICIntSelect = 0x00000000; // IRQ
  VICVectAddr0 = (unsigned)UART0_isr;
  VICVectCntl0 = 0x20 | 6; /* UART0 Interrupt */
  VICIntEnable = 1 << 6;   /* Enable UART0 Interrupt */
 
  U0IER = 0x03;       /* Enable UART0 RX and THRE Interrupts */   
             
  #endif
						
}


void UART0_Tx(char sByte) /* Write character to Serial Port    */ 
{
	while((READBIT(U0LSR,TEMT_BIT))==0);
	U0THR=sByte;
}

char UART0_Rx(void)  /* Read character from Serial Port   */
{
  while((READBIT(U0LSR,DR_BIT))==0);
	return U0RBR;
}

void UART0_Str(char *s)
{
   while(*s)
       UART0_Tx(*s++);
}

void UART0_Str1(unsigned char n)
{
 	unsigned char j;   
    for(j=0;j<n;j++)
    {
        UART0_Tx(buf[j]);
    }   
}

void UART0_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
  int i=0;
  if(n==0)
  {
    UART0_Tx('0');
		return;
  }
  else
  {
     while(n>0)
	 {
	   a[i++]=(n%10)+48;
	   n=n/10;
	 }
	 --i;
	 for(;i>=0;i--)
	 {
	   UART0_Tx(a[i]);
	 }
   }
}

void UART0_Float(float f)
{
  int x;
  float temp;
  x=f;
  UART0_Int(x);
  UART0_Tx('.');
  temp=(f-x)*100;
  x=temp;
  UART0_Int(x);
}
