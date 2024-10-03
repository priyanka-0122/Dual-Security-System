#ifndef __SW_INT3_H__
#define __SW_INT3_H__

#include "defines.h"

#define EINT3_LED 21
#define EINT3_SW	20

void eint3_isr(void) __irq;
void Enable_EINT3(void);

#endif
