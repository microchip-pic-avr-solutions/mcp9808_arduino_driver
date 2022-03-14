#include <mcp9808.h>
#define SerialDebug Serial3 // Add this to print via Serial

int err, celc, fehr, res = 0;

void setup(void) {
    /* Initialize serial interface */
    SerialDebug.begin(115200);

    /* Initialize MCP9808 library */
    err = mcp9808.begin();    
    if (err < 0) {
        SerialDebug.println("Error: could not start MCP9808 library");
    }
}

void loop(void) {
    /**
     * NOTE: read_temp_* functions returns float value.
     * Casting to int in order to print value via serial interface
     */
    /* Get celcius value from sensor */
    celc = (int)mcp9808.read_temp_c();
    /* Get fahrenheit value from sensor */
    fehr = (int)mcp9808.read_temp_f();

    /* Print temperature values via serial interface */
    SerialDebug.printf("Temp (*C): %d\n", celc);
    SerialDebug.printf("Temp (*F): %d\n", fehr);
    
    delay(100);
}