#include <LPC21XX.h>
#include <string.h>
#include "delay.h"
#include "i2c_eeprom.h"
#include "i2c.h"
#include "keypad.h"
#include "lcd.h"
#include "sw_int3.h"
#include "uart0.h"
#include "R305.h"

#define	LED1	5
#define	LED2	6

u8 ch, cnt, password[5];
//s8 ch, cnt, password[5];
u32 i;
u8 p[9] __attribute__((at(0x40000040)))="";
//s8 p[9] __attribute__((at(0x40000040)))="";


int main()
{
	 u32 pageid;
	 u8 *character;
	 init_i2c();
	 InitUART0();
	 InitLCD();
	 Enable_EINT3();

	 //SETTING LED AS OUTPUT
	 SETBIT(IODIR0,LED1);
	 SETBIT(IODIR0,LED2);
	
	 //CLEARING LED
	 CLRBIT(IOPIN0,LED1);
	 CLRBIT(IOPIN0,LED2);
	
	 //Setting password
   CmdLCD(CLR_LCD);
	 //StrLCD("Set Password");
	 strcpy(character, "Set FingerPrint\n");
	 StrLCD(character);
	 CmdLCD(GO_TO_LINE2_POS0);
	 for( i=0; i<4; i++)
		{
			ch = keyscan();
			password[i] = ch+48;
			U32LCD(password[i]);
			CharLCD('*');
			delay_ms(500);
		}
		password[i]='\0';
		
		//writing the password in eeprom
		i2c_eeprom_page_write(I2C_EEPROM_SA,0x00,password,4);
		
	  //Set Fingerprint
	  CmdLCD(CLR_LCD);
	  CmdLCD(GO_TO_LINE1_POS0);
	  //StrLCD("Set FingerPrint");
		strcpy(character, "Set FingerPrint\n");
		StrLCD(character);
	  CmdLCD(GO_TO_LINE1_POS0);
	  StrLCD("Enter ID: ");
	  pageid = keyscan();
	  CmdLCD(GO_TO_LINE2_POS0);
	  U32LCD(pageid);
	  delay_ms(500);
	  if(pageid>0 && pageid <10)
		 {
			 enroll(pageid);
		 }
	  CmdLCD(CLR_LCD);
	  while(1)
	   {
			 CmdLCD(CLR_LCD);
			 CmdLCD(GO_TO_LINE1_POS0);
			 StrLCD("Enter password");
			 CmdLCD(GO_TO_LINE2_POS0);
			 for(i=0; i<4; i++)
				{
					ch = keyscan();
					password[i] = ch + 48;
					U32LCD(password[i]);
					//CharLCD("password[i]");
					//CharLCD("*");
					delay_ms(500);
				}
			 password[i]='\0';
			 delay_ms(1000);
			 i2c_eeprom_seq_read(I2C_EEPROM_SA,0x00,p,4);
	
			 cnt = strcmp(p,password);
			 if(cnt==0)
				{
					CmdLCD(CLR_LCD);
					CmdLCD(GO_TO_LINE1_POS0);
					StrLCD("CORRECT PASSWORD");
					delay_ms(1000);
					break;
				}
			 else
				{
					CmdLCD(GO_TO_LINE1_POS0);
					StrLCD("WRONG PASSWORD");
					delay_ms(1000);
				}
			}
	
		//Ask for fingerprint*/
		while(1)
		{
			CmdLCD(CLR_LCD);
			CmdLCD(GO_TO_LINE1_POS0);
			StrLCD("PLACE FINGER");
			CmdLCD(GO_TO_LINE2_POS0);
			S32LCD(search_fp()-1);
			if((search_fp()-1) == 1)
			{
				CmdLCD(CLR_LCD);
				CmdLCD(GO_TO_LINE1_POS0);
				StrLCD("Fingerprint");
				CmdLCD(GO_TO_LINE2_POS0);
				StrLCD("matched");
				delay_ms(500);
				SETBIT(IOSET0,LED1);
				break;
			}
			else
			{
				CmdLCD(CLR_LCD);
				CmdLCD(GO_TO_LINE1_POS0);
				StrLCD("Fingerprint");
				CmdLCD(GO_TO_LINE2_POS0);
				StrLCD("not matched");
				SETBIT(IOSET0,LED2);
			}
		}
		
		//Perform the task
		//SETBIT(IOSET0,LED1);
}
