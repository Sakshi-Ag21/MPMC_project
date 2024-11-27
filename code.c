#include "eeprom.h"
#include "i2c.h"
#include "delay.h"
#include <stdutils.h>
#include <stdio.h>
#include <reg51.h>

#ifndef AT24C256
#define AT24C256 256  // Define a constant for AT24C256
#endif

#define C_EepromIdWriteMode_U8 0xA0  // Define EEPROM device ID in write mode

// Define global EEPROM type variable
unsigned int V_EepromType_U16 = AT24C256;

// Function to map SDA and SCL pins to EEPROM IC
void EEPROM_Init(unsigned int v_eepromType_u16)
{
    V_EepromType_U16 = v_eepromType_u16;
}

// Write a Byte
void EEPROM_WriteByte(unsigned int v_eepromAddress_u16, unsigned char v_eepromData_u8)
{
    unsigned char v_eepromLowerAddress_u8;
    unsigned char v_eepromPageNumber_u8;
    unsigned char v_eepromId_u8 = C_EepromIdWriteMode_U8;
    unsigned char v_eepromHigherAddress_u8;

    if (v_eepromAddress_u16 < V_EepromType_U16)
    {
        v_eepromLowerAddress_u8 = v_eepromAddress_u16 & 0xFF; // Extract lower byte

        if (V_EepromType_U16 > 16)
        {
            v_eepromHigherAddress_u8 = (v_eepromAddress_u16 >> 8) & 0xFF; // Extract higher byte
        }
        else
        {
            v_eepromPageNumber_u8 = (v_eepromAddress_u16 >> 8) & 0xFF;
            v_eepromId_u8 |= (v_eepromPageNumber_u8 << 1);
        }

        I2C_Start();
        I2C_Write(v_eepromId_u8);

        if (V_EepromType_U16 > 16)
        {
            I2C_Write(v_eepromHigherAddress_u8);
        }

        I2C_Write(v_eepromLowerAddress_u8);
        I2C_Write(v_eepromData_u8);
        I2C_Stop();

        DELAY_ms(10);
    }
}

// Read a Byte
unsigned char EEPROM_ReadByte(unsigned int v_eepromAddress_u16)
{
    unsigned char v_eepromLowerAddress_u8;
    unsigned char v_eepromPageNumber_u8;
    unsigned char v_eepromData_u8 = 0x00;
    unsigned char v_eepromId_u8 = C_EepromIdWriteMode_U8;
    unsigned char v_eepromHigherAddress_u8;

    if (v_eepromAddress_u16 < V_EepromType_U16)
    {
        v_eepromLowerAddress_u8 = v_eepromAddress_u16 & 0xFF;

        if (V_EepromType_U16 > 16)
        {
            v_eepromHigherAddress_u8 = (v_eepromAddress_u16 >> 8) & 0xFF;
        }
        else
        {
            v_eepromPageNumber_u8 = (v_eepromAddress_u16 >> 8) & 0xFF;
            v_eepromId_u8 |= (v_eepromPageNumber_u8 << 1);
        }

        I2C_Start();
        I2C_Write(v_eepromId_u8);

        if (V_EepromType_U16 > 16)
        {
            I2C_Write(v_eepromHigherAddress_u8);
        }

        I2C_Write(v_eepromLowerAddress_u8);

        I2C_Start();
        I2C_Write(v_eepromId_u8 | 0x01);
        v_eepromData_u8 = I2C_Read(0);
        I2C_Stop();
        DELAY_us(10);
    }
    return v_eepromData_u8;
}

// Function to blink LED
void Blink_LED()
{
    // Assuming LED is connected to P1.0 (you can change this depending on your setup)
    P1 = 0x01;  // Set P1.0 high to turn on the LED
    DELAY_ms(500); // Wait for 500ms
    P1 = 0x00;  // Set P1.0 low to turn off the LED
    DELAY_ms(500); // Wait for 500ms
}

// Main function to test EEPROM read/write
void main()
{
    unsigned int address = 0x0000; // Define EEPROM address
    unsigned int address2 = 0x003B;
    unsigned char readValue;        // Declare the variable

    // Write data to EEPROM
    EEPROM_WriteByte(address, 2); 
    

    // Read back value from address 0x0000
    readValue = EEPROM_ReadByte(address); 

    // Display read value (for debugging)
    printf("%d\n", readValue);          

    // Check if the value at address 0x0000 is 2
    if (readValue != 2)
    {
        while (1) // Infinite loop to blink LED
        {
            Blink_LED();  // Blink the LED
        }
    }

    // If the value is not 2, the program will continue normally (or end, depending on your setup)
}