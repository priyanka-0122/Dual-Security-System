#include <lpc21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "LCD_defines.h"
#include "lcd.h"

void WriteLCD(u8 dat)
{
	WRITEBYTE(IOPIN0,LCD_DATA,dat);
	SETBIT(IOSET0,LCD_EN);
	delay_us(1);
	SETBIT(IOCLR0,LCD_EN);
	delay_ms(2);
}

void CmdLCD(u8 cmd)
{
	SETBIT(IOCLR0,LCD_RS);
	WriteLCD(cmd);
}

void CharLCD(u8 c)
{
	SETBIT(IOSET0,LCD_RS);
	WriteLCD(c);
}

void InitLCD(void)
{
	WRITEBYTE(IODIR0,LCD_DATA,0xFF);
	SETBIT(IODIR0,LCD_RS);
	SETBIT(IODIR0,LCD_EN);
	
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(5);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(0x38);
	CmdLCD(0x08);
	CmdLCD(0x01);
	CmdLCD(0x06);
	CmdLCD(0x0f);
}

void StrLCD(u8 *p)
{
	while(*p)
		CharLCD(*p++);
}

void U32LCD(u32 n)
{
	u8 a[10];
	s8 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n>0)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		   CharLCD(a[i]);
	}
}

void S32LCD(s32 n)
{
  if(n<0)
	{
		CharLCD('-');
		n=-n;
	}
	U32LCD(n);
}
