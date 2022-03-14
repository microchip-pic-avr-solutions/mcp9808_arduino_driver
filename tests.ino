// TODO: add license header
#include "mcp9808.h"

#define POINTER_CONFIG 0x01		  // MCP9808 configuration register
#define POINTER_MANUF_ID 0x06	  // Manufacture ID
#define POINTER_DEVICE_ID 0x07	  // Device ID
#define POINTER_RESOLUTION 0x08   // Sensor resolution

// #define TEST_BEGIN
// #define TEST_TEMP
// #define TEST_SHUTDOWN
// #define TEST_WAKE
// #define TEST_SET_ALERT
// #define TEST_DISABLE_ALERT
// #define TEST_SET_RES
// #define TEST_GET_RES

#define SerialDebug Serial3 // Add this to print via Serial

int err, celc, fehr, res = 0;
uint16_t reg = 0;

void setup(void) {
    SerialDebug.begin(115200);

    err = mcp9808.begin();    
    if (err < 0) {
        SerialDebug.println("Error: could not start MCP9808 library");
    }
}

void loop(void) {
#ifdef TEST_BEGIN
	SerialDebug.printf("%04x\n", mcp9808.reg_read16(POINTER_MANUF_ID)); // 0x0054
	SerialDebug.printf("%04x\n", mcp9808.reg_read16(POINTER_DEVICE_ID)); // 0x0400
	SerialDebug.printf("%04x\n\n", mcp9808.reg_read16(POINTER_CONFIG)); // 0x00
#endif

#ifdef TEST_TEMP
    celc = (int)mcp9808.read_temp_c();
    fehr = (int)mcp9808.read_temp_f();
    res = mcp9808.get_resolution();

    SerialDebug.printf("Temp (*C): %d\n", celc);
    SerialDebug.printf("Temp (*F): %d\n", fehr);
    SerialDebug.printf("Resolution: %d\n", res);
#endif

#ifdef TEST_SHUTDOWN
    err = mcp9808.shutdown();
    if (err < 0) {
        SerialDebug.println("Error: could not shutdown MCP9808");
    }

    /* Check if SHDN (b'8) bit is set */
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    if (reg & (1 << 8)) {
        SerialDebug.println("SHDN bit set");
    } else {
        SerialDebug.println("SHDN bit not set");
    }
#endif

#ifdef TEST_WAKE
    err = mcp9808.wake();
    if (err < 0) {
        SerialDebug.println("Error: could not wake MCP9808");
    }

    /* Check if SHDN (b'8) bit is set */
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    // SerialDebug.printf("%04x", reg);
    if (reg & (1 << 8)) {
        SerialDebug.println("Device waked up");
    } else {
        SerialDebug.println("Device still in shutdown mode");
    }
#endif

#ifdef TEST_SET_ALERT
    /* Comparator mode, active low, alert output not critical */
    mcp9808.reg_write16(POINTER_CONFIG, 0x00);
    err = mcp9808.set_alert(false, false, false);
    if (err < 0) {
        SerialDebug.println("Error: could not set alert");
    }
    
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    // SerialDebug.printf("%04x\n", reg); 
    if (!(reg & (1 << 3))) { // Check if alert config is set
        SerialDebug.println("Error: alert output not set");
    } else if (reg & (1 << 0)) { // Check comparator/interrupt mode
        SerialDebug.println("Error: interrupt mode set, should be comparator mode");
    } else if (reg & (1 << 1)) { // Check active-low/active-high
        SerialDebug.println("Error: active-high set, should be active-low");
    } else if (reg & (1 << 2)) { // Check alert output critical/non-critical
        SerialDebug.println("Error: alert output critical set, should be non-critical");
    }

    /* Comparator mode, active low, alert output critical */
    mcp9808.reg_write16(POINTER_CONFIG, 0x00);
    err = mcp9808.set_alert(false, false, true);
    if (err < 0) {
        SerialDebug.println("Error: could not set alert");
    }
    
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    if (!(reg & (1 << 3))) { // Check if alert config is set
        SerialDebug.println("Error: alert output not set");
    } else if (reg & (1 << 0)) { // Check comparator/interrupt mode
        SerialDebug.println("Error: interrupt mode set, should be comparator mode");
    } else if (reg & (1 << 1)) { // Check active-low/active-high
        SerialDebug.println("Error: active-high set, should be active-low");
    } else if (reg & (0 << 2)) { // Check alert output critical/non-critical
        SerialDebug.println("Error: alert output non-critical set, should be critical");
    }
    
    /* Comparator mode, active high, alert output not critical */
    mcp9808.reg_write16(POINTER_CONFIG, 0x00);
    err = mcp9808.set_alert(false, true, false);
    if (err < 0) {
        SerialDebug.println("Error: could not set alert");
    }
    
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    if (!(reg & (1 << 3))) { // Check if alert config is set
        SerialDebug.println("Error: alert output not set");
    } else if (reg & (1 << 0)) { // Check comparator/interrupt mode
        SerialDebug.println("Error: interrupt mode set, should be comparator mode");
    } else if (reg & (0 << 1)) { // Check active-low/active-high
        SerialDebug.println("Error: active-low set, should be active-high");
    } else if (reg & (1 << 2)) { // Check alert output critical/non-critical
        SerialDebug.println("Error: alert output critical set, should be non-critical");
    }

    /* Comparator mode, active high, alert output critical */
    mcp9808.reg_write16(POINTER_CONFIG, 0x00);
    err = mcp9808.set_alert(false, true, true);
    if (err < 0) {
        SerialDebug.println("Error: could not set alert");
    }
    
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    if (!(reg & (1 << 3))) { // Check if alert config is set
        SerialDebug.println("Error: alert output not set");
    } else if (reg & (1 << 0)) { // Check comparator/interrupt mode
        SerialDebug.println("Error: interrupt mode set, should be comparator mode");
    } else if (reg & (0 << 1)) { // Check active-low/active-high
        SerialDebug.println("Error: active-low set, should be active-high");
    } else if (reg & (0 << 2)) { // Check alert output critical/non-critical
        SerialDebug.println("Error: alert output non-critical set, should be critical");
    }

    /* Interrupt mode, active low, alert output not critical */
    mcp9808.reg_write16(POINTER_CONFIG, 0x00);
    err = mcp9808.set_alert(true, false, false);
    if (err < 0) {
        SerialDebug.println("Error: could not set alert");
    }
    
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    if (!(reg & (1 << 3))) { // Check if alert config is set
        SerialDebug.println("Error: alert output not set");
    } else if (reg & (0 << 0)) { // Check comparator/interrupt mode
        SerialDebug.println("Error: comparator mode set, should be interrupt mode");
    } else if (reg & (1 << 1)) { // Check active-low/active-high
        SerialDebug.println("Error: active-high set, should be active-low");
    } else if (reg & (1 << 2)) { // Check alert output critical/non-critical
        SerialDebug.println("Error: alert output critical set, should be non-critical");
    }

    /* Interrupt mode, active low, alert output critical */
    mcp9808.reg_write16(POINTER_CONFIG, 0x00);
    err = mcp9808.set_alert(true, false, true);
    if (err < 0) {
        SerialDebug.println("Error: could not set alert");
    }
    
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    if (!(reg & (1 << 3))) { // Check if alert config is set
        SerialDebug.println("Error: alert output not set");
    } else if (reg & (0 << 0)) { // Check comparator/interrupt mode
        SerialDebug.println("Error: comparator mode set, should be interrupt mode");
    } else if (reg & (1 << 1)) { // Check active-low/active-high
        SerialDebug.println("Error: active-high set, should be active-low");
    } else if (reg & (0 << 2)) { // Check alert output critical/non-critical
        SerialDebug.println("Error: alert output non-critical set, should be critical");
    }

    /* Interrupt mode, active high, alert output not critical */
    mcp9808.reg_write16(POINTER_CONFIG, 0x00);
    err = mcp9808.set_alert(true, true, false);
    if (err < 0) {
        SerialDebug.println("Error: could not set alert");
    }
    
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    if (!(reg & (1 << 3))) { // Check if alert config is set
        SerialDebug.println("Error: alert output not set");
    } else if (reg & (0 << 0)) { // Check comparator/interrupt mode
        SerialDebug.println("Error: comparator mode set, should be interrupt mode");
    } else if (reg & (0 << 1)) { // Check active-low/active-high
        SerialDebug.println("Error: active-low set, should be active-high");
    } else if (reg & (1 << 2)) { // Check alert output critical/non-critical
        SerialDebug.println("Error: alert output critical set, should be non-critical");
    }

    /* Interrupt mode, active high, alert output critical */
    mcp9808.reg_write16(POINTER_CONFIG, 0x00);
    err = mcp9808.set_alert(true, true, true);
    if (err < 0) {
        SerialDebug.println("Error: could not set alert");
    }
    
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    if (!(reg & (1 << 3))) { // Check if alert config is set
        SerialDebug.println("Error: alert output not set");
    } else if (reg & (0 << 0)) { // Check comparator/interrupt mode
        SerialDebug.println("Error: comparator mode set, should be interrupt mode");
    } else if (reg & (0 << 1)) { // Check active-low/active-high
        SerialDebug.println("Error: active-low set, should be active-high");
    } else if (reg & (0 << 2)) { // Check alert output critical/non-critical
        SerialDebug.println("Error: alert output non-critical set, should be critical");
    }
#endif

#ifdef TEST_DISABLE_ALERT
    // SerialDebug.printf("%04x\n", reg); 
    reg = mcp9808.reg_read16(POINTER_CONFIG);
    mcp9808.reg_write16(POINTER_CONFIG, (reg | (1 << 3))); // Enable alerts
    delay(10);

    err = mcp9808.disable_alert();
    if (err < 0) {
        SerialDebug.println("Error: could not disable alert");
    }
#endif

#ifdef TEST_SET_RES
    mcp9808.set_resolution(res_05);
	uint8_t val = mcp9808.reg_read8(POINTER_RESOLUTION);
    if (val != res_05) {
        SerialDebug.println("Error: could not set resolution 0.5");
    }
    
    mcp9808.set_resolution(res_025);
	val = mcp9808.reg_read8(POINTER_RESOLUTION);
    if (val != res_025) {
        SerialDebug.println("Error: could not set resolution 0.25");
    }
    
    mcp9808.set_resolution(res_0125);
	val = mcp9808.reg_read8(POINTER_RESOLUTION);
    if (val != res_0125) {
        SerialDebug.println("Error: could not set resolution 0.125");
    }

    mcp9808.set_resolution(res_00625);
	val = mcp9808.reg_read8(POINTER_RESOLUTION);
    if (val != res_00625) {
        SerialDebug.println("Error: could not set resolution 0.0625");
    }
#endif

#ifdef TEST_GET_RES
    mcp9808.set_resolution(res_05);
    res = mcp9808.get_resolution();
    if (res != 5000) {
        SerialDebug.println("Error: could not get resolution 0.5");
        SerialDebug.printf("%d\n", res); 
    }

    mcp9808.set_resolution(res_025);
    res = mcp9808.get_resolution();
    if (res != 2500) {
        SerialDebug.println("Error: could not get resolution 0.25");
        SerialDebug.printf("%d\n", res); 
    }

    mcp9808.set_resolution(res_0125);
    res = mcp9808.get_resolution();
    if (res != 1250) {
        SerialDebug.println("Error: could not get resolution 0.125");
        SerialDebug.printf("%d\n", res); 
    }

    mcp9808.set_resolution(res_00625);
    res = mcp9808.get_resolution();
    if (res != 625) {
        SerialDebug.println("Error: could not get resolution 0.0625");
        SerialDebug.printf("%d\n", res); 
    }
#endif

    delay(1000);
}