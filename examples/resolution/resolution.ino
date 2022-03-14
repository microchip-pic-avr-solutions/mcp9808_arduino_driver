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
    /* Set output resolution to +0.125*C */
    mcp9808.set_resolution(res_0125);

    /* Get celcius value from sensor */
    celc = (int)mcp9808.read_temp_c();
    /* Get fahrenheit value from sensor */
    fehr = (int)mcp9808.read_temp_f();
    /* Get resolution of sensor */
    res = mcp9808.get_resolution();

    /* Print temperature values and sensor resolution via serial interface */
    SerialDebug.printf("Temp (*C): %d\n", celc);
    SerialDebug.printf("Temp (*F): %d\n", fehr);
    SerialDebug.printf("Resolution: %d\n\n", res); // NB: resolution is given in x10000 format

    delay(100);
}