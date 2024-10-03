#ifndef __I2C_H__
#define __I2C_H__

#include "types.h"
#include "uart0.h"

#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr

//defines for pin function selection
#define SCL_EN  0x00000010
#define SDA_EN  0x00000040

//defines for I2C_SPEED Configuration 
#define I2C_SPEED 100000    //Hz
#define LOADVAL   ((PCLK/I2C_SPEED)/2) //PCLK calculated in uart0.h

//bit defines for I2CONSET sfr
#define   AA_BIT 2
#define   SI_BIT 3
#define  STO_BIT 4
#define  STA_BIT 5
#define I2EN_BIT 6

void init_i2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_write(u8);
u8   i2c_read(void);
u8 i2c_ack(void);
u8 i2c_nack(void);
u8 i2c_masterack(void);

#endif
