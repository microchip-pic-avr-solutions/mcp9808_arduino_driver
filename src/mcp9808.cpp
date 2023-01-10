#include "mcp9808.h"

#include <Wire.h>

#define WIRE Wire1
// #define SerialDebug Serial5 // Cellular
#define SerialDebug Serial3 // Cellular Mini
// #define DEBUG

#define MCP_I2C_ADDRESS_DEFAULT 0x19
#define POINTER_CONFIG          0x01 // MCP9808 configuration register
#define POINTER_UPPER_TEMP      0x02 // Upper alert boundary
#define POINTER_LOWER_TEMP      0x03 // Lower alert boundery
#define POINTER_CRIT_TEMP       0x04 // Critical temperature
#define POINTER_AMBIENT_TEMP    0x05 // Ambient temperature
#define POINTER_MANUF_ID        0x06 // Manufacture ID
#define POINTER_DEVICE_ID       0x07 // Device ID
#define POINTER_RESOLUTION      0x08 // Sensor resolution

/* Global variables */
static uint8_t I2C_ADDRESS;

void regWrite8(uint8_t reg_ptr, uint8_t data);
void regWrite16(uint8_t reg_ptr, uint16_t data);
uint8_t regRead8(uint8_t reg_ptr);
uint16_t regRead16(uint8_t reg_ptr);

/* Singleton instance. Used by rest of library */
MCPClass Mcp9808 = MCPClass::instance();

/* Internal function for initialzing library. Called by begin() functions */
static int8_t initialize(void) {
    WIRE.begin();

    if (regRead16(POINTER_MANUF_ID) != 0x0054) {
#ifdef DEBUG
        SerialDebug.println("Error: could not read manufacturer ID");
#endif
        return 1;
    } else if (regRead16(POINTER_DEVICE_ID) != 0x0400) {
#ifdef DEBUG
        SerialDebug.println("Error: could not read device ID");
#endif
        return 1;
    }

    regWrite16(POINTER_CONFIG, 0x00);
    return 0;
}

/**
 * @brief Initialize MCP9808 library
 *
 * @return int 0 if successful, 1 if failed
 */
int8_t MCPClass::begin(void) {
    I2C_ADDRESS = MCP_I2C_ADDRESS_DEFAULT;
    return initialize();
}

/**
 * @brief Initialize MCP9808 library with custom I2C address
 *
 * @param address Custom I2C address
 * @return int 0 if successful, 1 if failed
 */
int8_t MCPClass::begin(uint8_t address) {
    I2C_ADDRESS = address;
    return initialize();
}

/**
 * @brief Read temperature (*C, Celcius)
 *
 * @return float Returned temperature
 */
float MCPClass::readTempC(void) {
    /* Read ambient temperature register */
    uint16_t temp_register_value = regRead16(POINTER_AMBIENT_TEMP);

    uint8_t upper_byte = temp_register_value >> 8;
    uint8_t lower_byte = (temp_register_value & 0xFF);

    /* Clear flags */
    upper_byte = upper_byte & 0x1F;

    /* Check sign of temperature data */
    if ((upper_byte & 0x10) == 0x10) {  // T_A < 0
        upper_byte = upper_byte & 0x0F; // Clear sign
        return (256.0 - (upper_byte * 16.0 + lower_byte / 16.0)) * -1;
    } else { // T_A >= 0
        return (upper_byte * 16.0 + lower_byte / 16.0);
    }
}

/**
 * @brief Read temperature (*F, Fahrenheit)
 *
 * @return float Returned temperature (x100 scale)
 */
float MCPClass::readTempF(void) {
    float temp = readTempC();

    /* Convert *C to *F */
    return ((temp * 1.8) + 32.0);
}

/**
 * @brief Shutdown MCP9808 (low power mode)
 *
 * @return int 0 if successful, 1 if failed
 */
int8_t MCPClass::shutdown(void) {
    uint16_t reg =
        regRead16(POINTER_CONFIG); // Get current value of CONFIG register

    /* Check if bits 7 and 6 (lock bits) are set */
    if (!((reg & (1 << 7)) && (reg & (1 << 6)))) {
        regWrite16(POINTER_CONFIG, reg | (1 << 8)); // Set bit 8 (SHDN
    } else {
#ifdef DEBUG
        SerialDebug.println("Error: lock bits are set");
#endif
        return 1;
    }

    return 0;
}

/**
 * @brief Wake up MCP9808 (low power mode)
 *
 * @return int 0 if successful, 1 if failed
 */
int8_t MCPClass::wake(void) {
    /* Get current value of CONFIG register */
    uint16_t reg = regRead16(POINTER_CONFIG);

    /* Check if shutdown bit is set */
    if (reg & (1 << 8)) {
        regWrite16(POINTER_CONFIG, reg | (0 << 8)); // Clear bit 8 (SHDN)
    } else {
#ifdef DEBUG
        SerialDebug.println("Error: shutdown (SHDN) bit not set");
#endif
        return 1;
    }

    return 0;
}

/**
 * @brief Set sensor resolution
 *
 * @param resolution res_t Resolution enum, see mcp9808.h
 */
void MCPClass::setResolution(res_t resolution) {
    regWrite8(POINTER_RESOLUTION, (0x00 | resolution));
}

/**
 * @brief Get sensor resolution
 *
 * @return int Resolution (factor x1e4), 1 if failed
 */
uint16_t MCPClass::getResolution(void) {
    /* Get current value of RESOLUTION register */
    uint8_t reg = regRead8(POINTER_RESOLUTION);

    /* Return resolution (factor x1e4) */
    switch (reg) {
    case res_05:
        return 5000;
        break;
    case res_025:
        return 2500;
        break;
    case res_0125:
        return 1250;
        break;
    case res_00625:
        return 625;
        break;
    default:
#ifdef DEBUG
        SerialDebug.println("Error: resolution not in list");
#endif
        return 1;
    }
}

/**
 * @brief 8-bit write procedure
 *
 * @param reg_ptr Register pointer
 * @param data 8-bit data
 */
void regWrite8(uint8_t reg_ptr, uint8_t data) {
    WIRE.beginTransmission(I2C_ADDRESS);

    WIRE.write(reg_ptr); // Register pointer
    WIRE.write(data);    // 8-bit Data

    WIRE.endTransmission();
}

/**
 * @brief 16-bit write procedure
 *
 * @param reg_ptr Register pointer
 * @param data 16-bit data (MSB, LSB)
 */
void regWrite16(uint8_t reg_ptr, uint16_t data) {
    WIRE.beginTransmission(I2C_ADDRESS);

    WIRE.write(reg_ptr);     // Register pointer
    WIRE.write(data >> 8);   // MSB data
    WIRE.write(data & 0xFF); // LSB data

    WIRE.endTransmission();
}

/**
 * @brief 8-bit read procedure
 *
 * @param reg_ptr Register pointer
 * @return uint8_t Returned data
 */
uint8_t regRead8(uint8_t reg_ptr) {
    /* Variables */
    uint8_t ret;

    /* Write new register pointer */
    WIRE.beginTransmission(I2C_ADDRESS);
    WIRE.write(reg_ptr); // Register pointer
    WIRE.endTransmission();

    /* Read data byte */
    WIRE.requestFrom((uint8_t)I2C_ADDRESS, (size_t)1);
    while (WIRE.available()) { ret = WIRE.read(); }

    return ret;
}

/**
 * @brief 16-bit read procedure
 *
 * @param reg_ptr Register pointer
 * @return uint16_t Returned data
 */
uint16_t regRead16(uint8_t reg_ptr) {
    /* Variables */
    unsigned char rx_data[2];

    /* Write new register pointer */
    WIRE.beginTransmission(I2C_ADDRESS);
    WIRE.write(reg_ptr); // Register pointer
    WIRE.endTransmission();

    /* Read data byte */
    WIRE.requestFrom((uint8_t)I2C_ADDRESS, (size_t)2);
    int i = 0;
    while (WIRE.available()) {
        rx_data[i] = WIRE.read();
        i++;
    }

    return (rx_data[0] << 8) | rx_data[1];
}
