[![MCHP](images/microchip.png)](https://www.microchip.com)

# Microchip MCP9808 Digital Temperatur Sensor Driver - AVR-IoT Cellular Mini
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/microchip-pic-avr-solutions/mcp9808_arduino_driver?logo=data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAACXBIWXMAAA7DAAAOwwHHb6hkAAAAGXRFWHRTb2Z0d2FyZQB3d3cuaW5rc2NhcGUub3Jnm%2B48GgAACc5JREFUaIHlmXtwVNUdxz%2B%2Fcze7ySbZPHkFoYENDwkwpVio2AqiolZ56tgZ30Jbp5axKAJCwfC2Su0gpeig0toi6piiFdTp0AFGRUWLVIsCgfCK8jIJkGSz2ce9p39s2Oyyrxsfnen0O3Nn7vnd3%2Fec3%2B%2Fc3%2F2d3zkX%2Fsch30QnurLS2RgIVFhKD1XoARZykYgUobXRPkibFk6LliNoc09QG%2F%2FqfvBgvYD%2BumN%2FZQd0ZaWzIRy4Dm3dBDIGKAOUzVFbRbNLa6qdYmzw1NTUJ9FSQBHQkL6rTuJ0ZXl3CTl%2BIeh7gG7pdLW2NcFtWljXJb9ohuzaFWqXXQQ8AFjAOeAxIJCMbNuBk0OH5jr8vhkIM4nMzDcM%2BWVpzcE17Y2pRMKrDPgCOADsSMay9cobB3gvc7T5PkRYKiJFIoKdq5NYcubiPt9pvz8JdAH%2BCZS0O5EUaR3QYHzZz%2FugpdkGXAyRsLB7dQ662DTVEzoSFW8C%2B9qNfxc4koqVcpp0ZaWzMdS2WsNPY%2FUiM6tBS7s09X2nfQDQ%2BsbSA4c22lVP6oAePjyrofnMOpDbEgidCI3OvwUA6pwqa5hn37602ec8EkJIg2poObsqmfEJEIlcXxEpvpVeIR1apm0mmAQHGvp770VzT3qaxjFyJJ7qjeSvfwFjUGVU3rE0pZ99o2dPcletJn%2F9BrIuHRU3EVozrb6i4nI7DsR5ebqiYphS1tsguSkJIqh%2B%2FfFseBGVnw%2BA1VDPuSmT0KdOxbuZIoQkLw%2FPSy9jeCsiAr%2BfpttvIbxnT6zap81B85I%2BR460pXMg%2Bgb0mDEOpawn0xkPoF0ucpc%2FguTlRbONFJfgnjcfrTNnKQD3nLmovt4OeXY27qrF4HTG6lbmOdXcdLbEOdB44tgdICMzEdz3zcBROThBnnXV1TjHjctEx3nNtThvvClBbgweTPYdd8YLNQ%2BeGtBnaLr%2BBOBweXl2vtPYA3jPMzuiq%2BPeceko8p9ZhxhG0s7M48dpmjwBfe5chHlBCBk9yvBUb0RKSpJb4%2FdzbuINmMeOxUrfKu3Z%2B0rZvj2cjKIA8pzGpA7jo37F3UtJCbnLHklpPIBRVkbOAzOTPhPDIHfZ8tTGA%2BTkkFu16MIxLm%2F4%2FNjPU1GUBhFkaupeAaXIXVCFUVaWVg3AddPNOC75frzxImTfdTeOUZdl5Dsu%2ByGuiZPiZFqxtMHr7ZXUtPoBA3qA%2FmG8WMfdS34%2Bjh9cmnFwiMy0%2B%2BEqcLliRlE4J022xQfImTkL1aVLrAlFptIrk60NxuzigvEi8pMLzIi%2FDwTQLS1kjR5jayVWJaVgmYQ%2F%2BKDdAI2uq8M5foKthU%2FcblTXLoS2bIm1YqCvuPDTFY1nP4sbS4RRGXsEAtUvE%2F7wQzuqAGRPnYbRv3%2B0HdrxDsFNr9nmO68fT9aP4tYyEZHHmwYOjPuIlCBJ0lQkhJzjJ8D5DyocpnVRFTqYdF%2BRAMlx4354IaIimVprTeuKx9ANtkocEME9fwEqLz9W2jtgBpfGCozZJcVLAM8FbLIuH03eylXo%2BnrM9hVSn2lElMIxYqS9UOpRhq6vJ7zn3xF%2Bqw%2Fd2IDzqqvt%2BVBQiDizCO%2BI28sMm1VSuH1F49mjEEmjXROIpaXkLlmGGAY5989Ede8efeZ%2F9hnMmv32DBAh51f3Y5SVRQu34KbXCO94x9aGSERw3Xo7xuAhsTJDiVp9vKzMfd6BrAtGJXfxUlS3yHZXFRTgnje%2F4%2BNra6N1ySJ0OOm6kgBVVIR7ztwOvmXhW7II3eqzNwlOJ7lVC8HhiBUPceVlzwIwZhUXLYydMdett5F9511xnRh9%2B2IdPED44AEA9IkTqJJSjCFDbBlheL2Y%2B%2Fdh1tZG%2BGfPgmnaWhcAVNdu0NJMaPdHUZmGETO7Fm2SL%2Fv19QFuAMfAi%2FFseBHc7oRO9MmTnJsyEauxMdKpx4Pnb5tRPXrYMsI6cZymieOxmpoAEKcLzwsvYiSpq5LC18K5KZMwjx6NdWKLMbukaCpQLNnZ5D%2B1FtUj%2BWoreXkoTwHBbVsj5EAA6%2FgXOK%2F7sb3cnp%2BP5LgJv%2F1WRGCaWDX7cU2c3JHp0sHpxOjdm9Cbb3B%2Br6o0rcbs4qJrRUk%2F95yHyLryqrR9GIMGEd79EVZdHQDWkcM4KiowKvplNgBwDKok%2FP57WCdORPgnT6IKC3B8d5gtvlFejnXkcEcSUXq3EpGPssZcgeuWzDtIRMiZfl80hWrLwveb5ZGYtuWBA%2FfDVYgrOyry%2F34V1uef2%2BPTvpcoLo40tHrXmHfFWJX32Io7JD8%2FPfM8tEXg%2BfVgWZFmSws0N5N1xVhbdFXaBfythHftivCDQay6OpzX32C%2FzCgsIrRtaxBlTVcF1dXvSrduJ%2BxZD8FNmxJSaKD6ZcIf7LTbBTn3Tsco6xlth7ZvI%2Fj6Ztt85%2BQpZI0d%2B2bp%2FsM1SkRagVfsEM1P9%2BBfszpBrk2T1sULwe%2B3ZYBZW4vV2FFSRMqMR9GNNssMpch99LdrBbSKtNXTgJmW1NKCb84sdCB5LWTW1uJ%2Fem3mwQMBfPPnotvi9%2BrWqVP4f%2Fe4PQfggOHx%2FAM69sQfi8gbKdW1xrd8KeGDB9OoaNqefQZz3960I%2FufWIm5b1%2FSZ4G%2FVhN%2B%2F70MtgPwuIgEod0BEdEisgAIJdMOvr6Z4KuZo0wH2iKhZCZ%2FmeGdO2n7y3Mpj1u01rQuWQytremG2auU%2BtP5RvRUQkQ%2BBhIC3Kqri9Q%2B7VknE8K7dxN4YUOicS3N%2BObPQ4eSzlEU5qFa%2FGufSvnYsqwZIhKN47iTOaVUFfBJVBAM4pszC6v9lMEOtNb4V62MLlbtQvyPLMesO5aaGMNv%2B%2BM6zL1JQ%2FEPDodjS6wgzgERaVZK3QqcAfCvWU04poCyC6upCd%2B8h9DNzaA1gT8%2FR%2BAV2wfO6EAgIRS11juUUnNFJC7%2Bkq4coVBonLXz%2FVebfzYtx27ZfCFEBCkpQQoLsQ4dsh2CsXz3rxfguu12gBql1GgROZmgl6qDhhGXTLPOND4FOFLpfNtQngI81Rv3O8rLx4lI0vhLu3af7ue9S9BrgJxvxcLM%2BCyrV%2FmEwq1ba1MpZCw%2BvqwoH42o9UT%2BHP43scllOO%2FO9KPD1k%2BEk15vV0PpJ4Cbsfsv%2BKvjrIheUFJz%2BEnJVB3Qid%2BsGqSxos%2FVlpLlaL7XGa5NtGn0S4alFpTU1tbZJXXaCD18eFZ905lrBJmOcCVf%2FyM%2FC%2Fp5sFaX1hxJXmOkwdeaxQavt5c2rIlayzhgBFAKZNofBoFjAm8Dm8M5vr93%2F%2BSUvSOKJPjGwuBARYWrQOteWkyvIBeJqGK0dhM55msWdL0lHBWHdaB079HTduL7%2FwL%2FAZqJ1CYE5LswAAAAAElFTkSuQmCC&style=flat-square)](https://github.com/microchip-pic-avr-solutions/mcp9808_arduino_driver/releases/latest)


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
* @return int 0 if successful, 1 if failed 
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
 * @return int 0 if successful, 1 if failed
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
* @return int 0 if successful, 1 if failed 
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
* @return int 0 if successful, 1 if failed 
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
 * @return int Resolution (factor x1e4), 1 if failed
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
err = Mcp9808.begin(); // Rev2
```
<br/>

---
References:<br/>
[1] [https://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf](https://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf)