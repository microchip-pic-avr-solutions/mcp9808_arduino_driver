#include "mcp9808.h"

#include <Wire.h>

#define SerialDebug Serial3
// #define DEBUG

#define I2C_ADDRESS 0x18
#define POINTER_CONFIG 0x01		  // MCP9808 configuration register
#define POINTER_UPPER_TEMP 0x02	  // Upper alert boundary
#define POINTER_LOWER_TEMP 0x03	  // Lower alert boundery
#define POINTER_CRIT_TEMP 0x04	  // Critical temperature
#define POINTER_AMBIENT_TEMP 0x05 // Ambient temperature
#define POINTER_MANUF_ID 0x06	  // Manufacture ID
#define POINTER_DEVICE_ID 0x07	  // Device ID
#define POINTER_RESOLUTION 0x08   // Sensor resolution

/* Singleton instance. Used by rest of library */
MCPClass Mcp9808 = MCPClass::instance();

/**
 * @brief Initialize MCP9808 library
 * 
 * @return int 0 if successful, -1 if failed
 */
int8_t MCPClass::begin(void)
{
	Wire1.begin();

	if (regRead16(POINTER_MANUF_ID) != 0x0054)
	{
#ifdef DEBUG
        SerialDebug.println("Error: could not read manufacturer ID");
#endif
		return -1;
	}
	else if (regRead16(POINTER_DEVICE_ID) != 0x0400)
	{
#ifdef DEBUG
        SerialDebug.println("Error: could not read device ID");
#endif
		return -1;
	}

	regWrite16(POINTER_CONFIG, 0x00);
	return 0;
}

/**
 * @brief Read temperature (*C, Celcius)
 * 
 * @return float Returned temperature
 */
float MCPClass::readTempC(void)
{
	/* Read ambient temperature register */
	uint16_t temp = regRead16(POINTER_AMBIENT_TEMP);
	
	uint8_t upper_byte = temp >> 8;
	uint8_t lower_byte = (temp & 0xFF);
	
	/* Clear flags */
	upper_byte = upper_byte & 0x1F;

	/* Check sign of temperature data */	
	if ((upper_byte & 0x10) == 0x10) { // T_A >= 0
		upper_byte = upper_byte  & 0x0F; // Clear sign	
		temp = 256 - (upper_byte * 16 + lower_byte / 16);
	} else { // T_A < 0
		temp = (upper_byte * 16 + lower_byte / 16);
	}

	return temp;
}

/**
 * @brief Read temperature (*F, Fahrenheit)
 * 
 * @return float Returned temperature (x100 scale)
 */
float MCPClass::readTempF(void)
{
	float temp = readTempC();

	/* Convert *C to *F */
	return (((temp * 9) / 5) + 32);
}

/**
 * @brief Shutdown MCP9808 (low power mode)
 * 
 * @return int 0 if successful, -1 if failed
 */
int8_t MCPClass::shutdown(void) {
	uint16_t reg = regRead16(POINTER_CONFIG); // Get current value of CONFIG register

	/* Check if bits 7 and 6 (lock bits) are set */
	if (!((reg & (1 << 7)) && (reg & (1 << 6)))) {
		regWrite16(POINTER_CONFIG, reg | (1 << 8)); // Set bit 8 (SHDN 
	} else {
#ifdef DEBUG
        SerialDebug.println("Error: lock bits are set");
#endif
		return -1;
	}

	return 0;	
}

/**
 * @brief Wake up MCP9808 (low power mode)
 * 
 * @return int 0 if successful, -1 if failed
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
		return -1;
	}

	return 0;	
}

// /**
//  * @brief Set alerts
//  * 
//  * @param comp_int_toggle int Toggle between Comparator (0) or Interrupt (1) output mode
//  * @param active_low_high_toggle int Toggle between Active low (0) or Active high (1) output polarity
//  * @param alert_crit Use alert output as critical temperature (0 if false, 1 if true)
//  * @return int 0 if successful, -1 if failed
//  */
// int MCPClass::set_alert(bool comp_int_toggle, bool active_low_high_toggle, bool alert_crit) {
// 	/* Get current value of CONFIG register */
// 	uint16_t reg = regRead16(POINTER_CONFIG);

// 	/* Enable alerts */
// 	regWrite16(POINTER_CONFIG, (reg | (1 << 3)));

// 	/* Set Comparator or Interrupt output mode */
// 	reg = regRead16(POINTER_CONFIG);
// 	if(comp_int_toggle) {
// 		regWrite16(POINTER_CONFIG, (reg | (1 << 0))); // Enable Interrupt output mode
// 	} else {
// 		regWrite16(POINTER_CONFIG, (reg & ~(1 << 0))); // Enable Comparator output mode
// 	}

// 	/* Set active high/low output polarity */
// 	reg = regRead16(POINTER_CONFIG);
// 	if(active_low_high_toggle) {
// 		regWrite16(POINTER_CONFIG, (reg | (1 << 1))); // Enable Active-high output polarity
// 	} else {
// 		regWrite16(POINTER_CONFIG, (reg & ~(1 << 1))); // Enable Active-low output polarity
// 	}

// 	/* Use alert output as critical temperature if window lock is not set */
// 	reg = regRead16(POINTER_CONFIG);
// 	if (!(reg & (1 << 6))) {
// 		if(alert_crit) {
// 			regWrite16(POINTER_CONFIG, (reg | (1 << 2))); // Enable alert output critical
// 		} else {
// 			regWrite16(POINTER_CONFIG, (reg & ~(1 << 2))); // Enable alert output non-critical
// 		}
// 	} else {
// #ifdef DEBUG
//         SerialDebug.println("Error: window lock is set");
// #endif
// 		return -1;
// 	}

// 	/* Check if alert output is asserted */
// 	reg = regRead16(POINTER_CONFIG);
// 	if (!(reg & (1 << 4))) {
// #ifdef DEBUG
//         SerialDebug.println("Error: alert output not asserted");
// #endif
// 		return -1;
// 	}

// 	return 0;
// }

// /**
//  * @brief Disable alerts
//  * 
//  * @return int 0 if successful, -1 if failed
//  */
// int MCPClass::disable_alert(void) {
// 	/* Get current value of CONFIG register */
// 	uint16_t reg = regRead16(POINTER_CONFIG);

// 	/* Disable alerts */
// 	// reg = regRead16(POINTER_CONFIG);
//     // SerialDebug.printf("%04x\n", reg); 
	
// 	regWrite16(POINTER_CONFIG, (reg & ~(1 << 3)));
	
// 	/* Check if alert output is asserted */
// 	reg = mcp9808.regRead16(POINTER_CONFIG);
// 	if (reg & (1 << 4)) {
// #ifdef DEBUG
//         SerialDebug.println("Error: alert output set");
// #endif
// 		return -1;
// 	}

// 	return 0;
// }

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
 * @return int Resolution (factor x1e4), -1 if failed
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
			return -1;
	}
}


/**
 * @brief 8-bit write procedure
 * 
 * @param reg_ptr Register pointer
 * @param data 8-bit data
 */
void MCPClass::regWrite8(uint8_t reg_ptr, uint8_t data)
{
	Wire1.beginTransmission(I2C_ADDRESS);

	Wire1.write(reg_ptr); // Register pointer
	Wire1.write(data);	 // 8-bit Data

	Wire1.endTransmission();
}

/**
 * @brief 16-bit write procedure
 * 
 * @param reg_ptr Register pointer
 * @param data 16-bit data (MSB, LSB)
 */
void MCPClass::regWrite16(uint8_t reg_ptr, uint16_t data)
{
	Wire1.beginTransmission(I2C_ADDRESS);

	Wire1.write(reg_ptr);   // Register pointer
	Wire1.write(data >> 8); // MSB data
	Wire1.write(data & 0xFF); // LSB data

	Wire1.endTransmission();
}

/**
 * @brief 8-bit read procedure
 * 
 * @param reg_ptr Register pointer
 * @return uint8_t Returned data
 */
uint8_t MCPClass::regRead8(uint8_t reg_ptr)
{
	/* Variables */
	uint8_t ret;

	/* Write new register pointer */
	Wire1.beginTransmission(I2C_ADDRESS);
	Wire1.write(reg_ptr); // Register pointer
	Wire1.endTransmission();

	/* Read data byte */
	Wire1.requestFrom(I2C_ADDRESS, 1, 0x01);
	while (Wire1.available())
	{
		ret = Wire1.read();
	}

	return ret;
}

/**
 * @brief 16-bit read procedure
 * 
 * @param reg_ptr Register pointer
 * @return uint16_t Returned data
 */
uint16_t MCPClass::regRead16(uint8_t reg_ptr)
{
	/* Variables */
	unsigned char rx_data[2];

	/* Write new register pointer */
	Wire1.beginTransmission(I2C_ADDRESS);
	Wire1.write(reg_ptr); // Register pointer
	Wire1.endTransmission();

	/* Read data byte */
	Wire1.requestFrom(I2C_ADDRESS, 2, 0x01);
	int i = 0;
	while (Wire1.available())
	{
		rx_data[i] = Wire1.read();
		i++;
	}

	return (rx_data[0] << 8) | rx_data[1];
}
