#ifndef MCP9808_H
#define MCP9808_H

#include <Arduino.h>

typedef enum {
	res_05 = 0x00,
	res_025 = 0x01,
	res_0125 = 0x02,
	res_00625 = 0x03
} res_t;

class MCPClass
{
private:
	/**
     * @brief Constructor is hidden to enforce a single instance of this class
     * through a singleton.
     */
	MCPClass(){};

public:
	/* Singleton instance */
	static MCPClass &instance(void)
	{
		static MCPClass instance;
		return instance;
	}

	/**
     * @brief Initialize MCP9808 library
     * 
     * @return int 0 if successful, 1 if failed
     */
	int8_t begin(void);
	
	/**
	 * @brief Initialize MCP9808 library with custom I2C address
	 * 
	 * @param address Custom I2C address
	 * @return int 0 if successful, 1 if failed
	 */
	int8_t begin(uint8_t address);

	/**
	 * @brief Read temperature (*C, Celcius)
	 * 
	 * @return float Returned temperature
	 */
	float readTempC(void);
	
	/**
	 * @brief Read temperature (*F, Fahrenheit)
	 * 
	 * @return float Returned temperature
	 */
	float readTempF(void);

	/**
	 * @brief Shutdown MCP9808 (low power mode)
	 * 
	 * @return int 0 if successful, 1 if failed
	 */
	int8_t shutdown(void);

	/**
	 * @brief Wake up MCP9808 (low power mode)
	 * 
	 * @return int 0 if successful, 1 if failed
	 */
	int8_t wake(void);

	/**
	 * @brief Set sensor resolution
	 * 
	 * @param resolution res_t Resolution enum, see header file
	 */
	void setResolution(res_t resolution);

	/**
	 * @brief Get sensor resolution
	 * 
	 * @return int Resolution (factor x1e4), 1 if failed
	 */
	uint16_t getResolution(void);
};

extern MCPClass Mcp9808;
#endif