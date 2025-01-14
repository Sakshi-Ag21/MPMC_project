#ifndef _I2C_H
#define _I2C_H

#include <reg51.h>
#include "stdutils.h"


/***************************************************************************************************
                               SCL and SDA pin configuration
***************************************************************************************************/                               
sbit SCL_PIN = P2^0; //SCL Connected to P0.6
sbit SDA_PIN = P2^2; //SDA Connected to P0.7

#define SCL_Direction SCL_PIN
#define SDA_Direction SDA_PIN
//






/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t value);
uint8_t I2C_Read(uint8_t);
//

#endif