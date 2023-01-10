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
    SerialDebug.println("I'm awake");

    // Shut down MCP9808 (set in low power mode)
    int8_t error = Mcp9808.shutdown();
    if (error) {
        SerialDebug.println("Error: could not shutdown MCP9808");
    }

    SerialDebug.println("Sleeping....");
    delay(2000);

    // Wake up MCP9808
    error = Mcp9808.wake();
    if (error) {
        SerialDebug.println("Error: could not wake MCP9808");
    }
}