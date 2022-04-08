#include <mcp9808.h>

#define SerialDebug Serial3 // Add this to print via Serial

int8_t err = 0;

void setup(void) {
    /* Initialize serial interface */
    SerialDebug.begin(115200);

    /* Initialize MCP9808 library */
    err = Mcp9808.begin(0x18); // Rev1
    // err = Mcp9808.begin(); // Rev2
    if (err) {
        SerialDebug.println("Error: could not start MCP9808 library");
    }
}

void loop(void) {
    SerialDebug.println("I'm awake");

    /* Shut down MCP9808 (set in low power mode) */
    err = Mcp9808.shutdown();
    if (err) {
        SerialDebug.println("Error: could not shutdown MCP9808");
    }

    SerialDebug.println("Sleeping zzzzZZZZZ");
    delay(500);

    /* Wake up MCP9808 */
    err = Mcp9808.wake();
    if (err) {
        SerialDebug.println("Error: could not wake MCP9808");
    }
}