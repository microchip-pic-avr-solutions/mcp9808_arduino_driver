[![MCHP](images/microchip.png)](https://www.microchip.com)

# Microchip MCP9808 Digital Temperatur Sensor Driver - AVR-IoT Cellular Mini

## Description

Low-level Arduino driver for the MCP9808 Digital Temperature Sensor [1] mainly focused on the 
AVR-IoT Cellular Mini development kit.

## Install

You can clone this library to the Arduino library folder, usually located in the **Arduino > Libraries** folder.

```
cd <path-to-library-folder>
git clone <https-link-to-repo>
```

## Usage

After installation, add this line to the top of your *.ino* file;

```c
#include <mcp9808.h>
```

This adds the library header file to your project, which includes all of the library functions and data types.

You also need to run the [Begin](#begin) command in order to initialize the library. 
See the [Available Commands](#available-commands) section for more information

<br/>

## Available commands

List of the commands available for the MCP9808 library. 

### Begin
There are 2 ways to initialize the MCP9808 library:

```c
/** 
* @brief Initialize MCP9808 library 
* 
* @return int 0 if successful, -1 if failed 
*/
int8_t begin(void);
```

This command initializes the MCP9808 library by starting a *TWI* instance, checks for the correct manufacturer and 
device ID, and wipes the configuration register.

<br/>

```c
/**
 * @brief Initialize MCP9808 library with custom I2C address
 * 
 * @param address Custom I2C address
 * @return int 0 if successful, -1 if failed
 */
int8_t begin(uint8_t address);
```

This command initializes the MCP9808 library in a similar way to the command above, with an exception of the user being
able to feed a custom I2C sensor address to the library.

<br/>

### Read temperature

```c
/** 
* @brief Read temperature (*C, Celcius) 
* 
* @return float Returned temperature 
*/
float readTempC(void);
```

```c
/** 
* @brief Read temperature (*F, Fahrenheit) 
* 
* @return float Returned temperature 
*/
float readTempF(void);
```

These functions return the temperature, either in Celsius or Fahrenheit, which is measured by the sensor. 
These values are returned as a *float* data type but can be cast into an integer (*int*) for most purposes.

<br/>

### Low power mode

```c
/** 
* @brief Shutdown MCP9808 (low power mode) 
* 
* @return int 0 if successful, -1 if failed 
*/
int8_t shutdown(void);
```

This command sets the device in a low-power (shutdown) mode.

The datasheet [1] states the following about Shutdown mode

> Shutdown mode disables all power-consuming activities (including temperature sampling operations) while leaving the serial interface active. This mode is selected by setting bit 8 of CONFIG to ‘1’. In this mode, the device consumes ISHDN. It remains in this mode until bit 8 is cleared to ‘0’ to enable *Continuous Conversion* mode or until power is recycled. 

> In Shutdown mode, all registers can be read or written. However, the serial bus activity increases the shutdown current. In addition, if the device is in shutdown while the Alert pin is asserted, the device will retain the active state during shutdown. This increases the shutdown current due to the additional Alert output current

<br/>

```c
/** 
* @brief Wake up MCP9808 (low power mode) 
* 
* @return int 0 if successful, -1 if failed 
*/
int8_t wake(void);
```
This command “wakes” the device up from low-power (shutdown) mode. 

<br/>

### Alerts

**The alert functionality of the MCP9808 is currently not supported by this library.**
**There is a plan to support this in the future.**

<br/>

### Resolution
```c
typedef enum {
	res_05 = 0x00,
	res_025 = 0x01,
	res_0125 = 0x02,
	res_00625 = 0x03
} res_t;
```
The available resolutions are listed in the struct above. MCP9808 supports the following resolutions:

- +0.5*C
- +0.25*C
- +0.125*C
- +0.0625*C (default)

<br/>

```c
/**
 * @brief Set sensor resolution
 * 
 * @param resolution res_t Resolution enum, see header file
 */
void setResolution(res_t resolution);
```

This command sets the device resolution based on the resolution enumeration given as an input. 

<br/>

```c
/**
 * @brief Get sensor resolution
 * 
 * @return int Resolution (factor x1e4), -1 if failed
 */
uint16_t getResolution(void);
```
This command returns the resolution as an integer with a factor of 1*(10^4).

This means that a resolution like +0.25*C is returned as the integer value *2500*.
A resolution of 0.0625 is returned as the integer value *625* etc.

<br/>

### Read/Write (8 and 16-bit)

```c
/**
 * @brief 8-bit write procedure
 * 
 * @param reg_ptr Register pointer
 * @param data 16-bit data (MSB, LSB)
 */
void regWrite8(uint8_t reg_ptr, uint8_t data);
```

```c
/**
 * @brief 8-bit read procedure
 * 
 * @param reg_ptr Register pointer
 * @return uint8_t Returned data
 */
uint8_t regRead8(uint8_t reg_ptr);
```

```c
/**
 * @brief 16-bit write procedure
 * 
 * @param reg_ptr Register pointer
 * @param data 8-bit data
 */
void regWrite16(uint8_t reg_ptr, uint16_t data);
```

```c
/**
 * @brief 16-bit read procedure
 * 
 * @param reg_ptr Register pointer
 * @return uint16_t Returned data
 */
uint16_t regRead16(uint8_t reg_ptr);
```
These commands are abstraction functions for reading/writing to 8 and 16-bit registers in the MCP9808. 

These commands are mostly meant for internal use in the commands mentioned above but are available through 
the library header file for general use. We do not recommend using these functions for functionality like 
reading temperature, low-power mode etc, but rather use the dedicated functions like [read_temp](#read-temperature), 
[shutdown](#low-power-mode), [wake](#low-power-mode) and similar. 

<br/>

## Examples

Examples can be found in the **examples** folder. There are 3 examples available:

- *low_power* - Example of using the low-power functionality of the sensor device.
- *read_temp* - Example of getting a temperature reading from the sensor (in degrees Celsius and Fahrenheit) and 
sending that data through a serial interface.
- *resolution* - Example of setting and retrieving resolution configuration from the sensor device.

<br/>

__NOTE: The driver is written with Rev2 of the Cellular Mini board in mind, but the examples listed above
can easily be switched between Rev1 and Rev2 by commmenting/uncommenting the following lines in the examples:__
```c
/* Initialize MCP9808 library */
err = Mcp9808.begin(0x18); // Rev1
// err = Mcp9808.begin(); // Rev2
```
<br/>

---
References:<br/>
[1] [https://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf](https://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf)