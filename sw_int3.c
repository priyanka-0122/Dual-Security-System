#include <lpc21xx.h>
#include <string.h>
#include "sw_int3.h"
#include "pin_function_defines.h" 
#include "delay.h"
#include "i2c_eeprom.h"
#include "lcd.h"
#include "keypad.h"

void eint3_isr(void) __irq
{
	u8 password1[5], password2[5], cnt, ch;
	//const u8 password1[5], password2[5];
	//u8 cnt, ch;
	u32 i;
	CmdLCD(CLR_LCD);
	StrLCD("Enter Password:");
	CmdLCD(GO_TO_LINE2_POS0);
	for(i=0; i<4; i++)
		{
			ch = keyscan();
			password1[i]= ch+48;
			delay_ms(500);
			U32LCD(password1[i]);
			//CharLCD('*');
		}
	password1[i]='\0';
	CmdLCD(CLR_LCD);
	StrLCD("ReEnter Password:");	
	for(i=0; i<4; i++)
		{
			ch = keyscan();
			password2[i]= ch+48;
			delay_ms(500);
			U32LCD(password2[i]);
			//CharLCD('*');
		}
	password2[i]='\0';
	
	//comparing both of the entered password
	cnt= strcmp(password1,password2);
	if(cnt == 0)
	{
		//overwriting the new password in eeprom
		i2c_eeprom_page_write(I2C_EEPROM_SA,0x00,password1,4);
		
		//Display password changed
		CmdLCD(CLR_LCD);
		StrLCD("Password changed");
		CmdLCD(GO_TO_LINE2_POS0);
		StrLCD("successfully");
		delay_ms(1000);
	}
	else
	{
		//Keep the old password
		//Display password not changed
		CmdLCD(CLR_LCD);
		StrLCD("Password not");
		CmdLCD(GO_TO_LINE2_POS0);
		StrLCD("changed");
	}
	
	//SSETBIT(EXTINT,3);//clear flag
	SCLRBIT(EXTINT,3);
	VICVectAddr=0;//dummy write;
	delay_ms(100);
}	

void Enable_EINT3(void)
{
	CFGPIN(PINSEL1,EINT3_SW,FUNC4); //CFGPIN(PINSEL0,9,FUNC4);
	SETBIT(IODIR0,EINT3_LED); //SETBIT(IODIR0,EINT3_LED);
	CLRBIT(IOPIN0,EINT3_LED);
	SSETBIT(VICIntEnable,17);	//SSETBIT(VICIntEnable,17);
	VICVectCntl3=0x20|17;			//VICVectCntl3=0x20|17;
	VICVectAddr3=(unsigned)eint3_isr;	//VICVectAddr3=(unsigned)eint3_isr;
	
	//SCLRBIT(EXTINT,3); //default //SCLRBIT(EXTINT,3);
	//EINT3 as EDGE_TRIG
  SETBIT(EXTMODE,3);	//SETBIT(EXTMODE,3);
	//EINT0 as REDGE
  SETBIT(EXTPOLAR,3); //SETBIT(EXTPOLAR,3);
}
