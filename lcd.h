#ifndef __LCD_H__
#define __LCD_H__

#include "types.h"
#include "defines.h"
#include "LCD_defines.h"

//primary driver prototypes for HD44780 controller
void InitLCD(void);
void WriteLCD(u8);
void CmdLCD(u8);
void CharLCD(u8);
//secondary driver prototypes for HD44780 controller
void StrLCD(u8 *);
void U32LCD(u32);
void S32LCD(s32);

#endif
