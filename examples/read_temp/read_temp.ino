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
}

void loop(void) {
    const float celsius = Mcp9808.readTempC();
    const float fahrenheit = Mcp9808.readTempF();

    SerialDebug.printf("Temperature (*C): %f\r\n", (double)celsius);
    SerialDebug.printf("Temperature (*F): %f\r\n", (double)fahrenheit);

    delay(2000);
}