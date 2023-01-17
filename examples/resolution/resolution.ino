#include <mcp9808.h>

#define SerialDebug Serial3 // Add this to print via Serial

void setup(void) {
    SerialDebug.begin(115200);

    // Initialize MCP9808 library
    // const int8_t error = Mcp9808.begin(0x18); // Rev1
    const int8_t error = Mcp9808.begin(); // Rev2
    if (error) {
        SerialDebug.println("Error: could not start MCP9808 library");
    }

    // Set output resolution to +0.125*C
    Mcp9808.setResolution(res_0125);
}

void loop(void) {
    const float celsius = Mcp9808.readTempC();
    const float fahrenheit = Mcp9808.readTempF();
    const uint16_t resolution = Mcp9808.getResolution();

    SerialDebug.printf("Temperature (*C): %f\r\n", (double)celsius);
    SerialDebug.printf("Temperature (*F): %f\r\n", (double)fahrenheit);

    // NB: resolution is given in x10000 format
    SerialDebug.printf("Resolution: %d\r\n", resolution);

    delay(2000);
}
