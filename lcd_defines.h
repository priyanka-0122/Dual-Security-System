#ifndef __LCD_DEFINES_H__
#define __LCD_DEFINES_H__

#define LCD_DATA					8
#define	LCD_RS						16	
#define	LCD_RW						17
#define	LCD_EN						18
#define	CLR_LCD						0x01
#define	DSP_ON_CUR_BLK		0x0f
#define	DSP_ON_CUR_ON			0x0e
#define	DSP_ON_CUR_OFF		0x0c
#define	SHIFT_CUR_RT			0x06
#define	SHIFT_DSP_RT			0x18
#define	GO_TO_LINE1_POS0	0x80
#define	GO_TO_LINE2_POS0	0xc0
#define	GO_TO_LINE3_POS0	0x94
#define	GO_TO_LINE4_POS0	0x14
#define	SET_CUR_CGRAM			0x40
#define	FUN_8BIT_LINE			0x30
#define	FUN_8BIT_2LINES		0x38
#define	FUN_4BIT_2LINES		0x28
#define	DSP_OFF						0x08

#endif
