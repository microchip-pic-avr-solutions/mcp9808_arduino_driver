// TODO: add license header
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
     * @return int 0 if successful, -1 if failed
     */
	int begin(void);

	/**
	 * @brief Read temperature (*C, Celcius)
	 * 
	 * @return float Returned temperature
	 */
	float read_temp_c(void);
	
	/**
	 * @brief Read temperature (*F, Fahrenheit)
	 * 
	 * @return float Returned temperature
	 */
	float read_temp_f(void);

	/**
	 * @brief Shutdown MCP9808 (low power mode)
	 * 
	 * @return int 0 if successful, -1 if failed
	 */
	int shutdown(void);

	/**
	 * @brief Wake up MCP9808 (low power mode)
	 * 
	 * @return int 0 if successful, -1 if failed
	 */
	int wake(void);

	// /**
	//  * @brief Set alerts
	//  * 
	//  * @param comp_int_toggle int Toggle between Comparator (0) or Interrupt (1) output mode
	//  * @param active_low_high_toggle int Toggle between Active low (0) or Active high (1) output polarity
	//  * @param alert_crit Use alert output as critical temperature (0 if false, 1 if true)
	//  * @return int 0 if successful, -1 if failed
	//  */
	// int set_alert(bool comp_int_toggle, bool active_low_high_toggle, bool alert_crit);

	// /**
	//  * @brief Disable alerts
	//  * 
	//  * @return int 0 if successful, -1 if failed
	//  */
	// int disable_alert(void);

	// int set_temp_limit(int upper, int lower, int crit, bool lock);

	/**
	 * @brief Set sensor resolution
	 * 
	 * @param resolution res_t Resolution enum, see header file
	 */
	void set_resolution(res_t resolution);

	/**
	 * @brief Get sensor resolution
	 * 
	 * @return int Resolution (factor x1e4), -1 if failed
	 */
	int get_resolution(void);


////// Read/write procedures //////
	/**
	 * @brief 8-bit write procedure
	 * 
	 * @param reg_ptr Register pointer
	 * @param data 16-bit data (MSB, LSB)
	 */
	void reg_write8(uint8_t reg_ptr, uint8_t data);

	/**
	 * @brief 16-bit write procedure
	 * 
	 * @param reg_ptr Register pointer
	 * @param data 8-bit data
	 */
	void reg_write16(uint8_t reg_ptr, uint16_t data);
	
	/**
	 * @brief 8-bit read procedure
	 * 
	 * @param reg_ptr Register pointer
	 * @return uint8_t Returned data
	 */
	uint8_t reg_read8(uint8_t reg_ptr);

	/**
	 * @brief 16-bit read procedure
	 * 
	 * @param reg_ptr Register pointer
	 * @return uint16_t Returned data
	 */
	uint16_t reg_read16(uint8_t reg_ptr);
};

extern MCPClass mcp9808;
#endif