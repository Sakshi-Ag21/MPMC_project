#ifndef _EEPROM_H
#define _EEPROM_H

#include "stdutils.h"

/***************************************************************************************************
                             Commonly used Eeprom macros/Constants
***************************************************************************************************/
#define AT24C01  128u    /* 1024  bits = 128    Bytes*/
#define AT24C02  256u    /* 2048  bits = 256    Bytes*/
#define AT24C04  512u    /* 4096  bits = 512    Bytes*/
#define AT24C08  1024u   /* 8192  bits = 1024  Bytes*/
#define AT24C16  2048u  /* 16384  bits = 2048  Bytes*/
#define AT24C32  4096u  /* 32768  bits = 4096  Bytes*/
#define AT24C64  8192u  /* 65536  bits = 8192  Bytes*/
#define AT24C128 16384u /* 128K   bits = 16384 Bytes*/
#define AT24C256 32768u /* 256K   bits = 32768 Bytes*/



#define C_EepromIdWriteMode_U8 0xA0u
#define C_EepromIdReadMode_U8  0xA1u 
//




/***************************************************************************************************
                 PreCompile configurations to enable/disable the functions
****************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring its respective macros to 1/0.
 2. By default all the API's are disabled. 
***************************************************************************************************/
#define    ENABLE_EEPROM_WriteNBytes   0
#define    ENABLE_EEPROM_ReadNBytes    0
#define    ENABLE_EEPROM_WriteString   1
#define    ENABLE_EEPROM_ReadString    1
#define    ENABLE_EEPROM_Erase         0
//


/***************************************************************************************************
                             Function Prototypes
****************************************************************************************************/
void EEPROM_Init(uint16_t v_eepromType_u16);
void EEPROM_WriteByte(uint16_t v_eepromAddress_u16, uint8_t v_eepromData_u8);
uint8_t EEPROM_ReadByte(uint16_t v_eepromAddress_u16);
void EEPROM_WriteNBytes(uint16_t v_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16);
void EEPROM_ReadNBytes(uint16_t v_eepromAddress_16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16);
void EEPROM_WriteString(uint16_t v_eepromAddress_u16, uint8_t *ptr_string_u8);
void EEPROM_ReadString(uint16_t v_eepromAddress_u16, uint8_t *ptr_destStringAddress_u8);
void EEPROM_Erase(void);
//

#endif