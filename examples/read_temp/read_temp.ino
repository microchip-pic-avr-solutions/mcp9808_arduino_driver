#include <mcp9808.h>
#define SerialDebug Serial3 // Add this to print via Serial

int8_t err, celc, fehr = 0;
uint16_t res = 0;

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
    /**
     * NOTE: read_temp_* functions returns float value.
     * Casting to int in order to print value via serial interface
     */
    /* Get celcius value from sensor */
    celc = (int)Mcp9808.readTempC();
    /* Get fahrenheit value from sensor */
    fehr = (int)Mcp9808.readTempF();

    /* Print temperature values via serial interface */
    SerialDebug.printf("Temp (*C): %d\n", celc);
    SerialDebug.printf("Temp (*F): %d\n\n", fehr);
    
    delay(100);
}