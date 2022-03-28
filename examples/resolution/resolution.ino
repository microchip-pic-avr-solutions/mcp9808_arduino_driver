#include <mcp9808.h>

#define SerialDebug Serial3 // Add this to print via Serial

int8_t err, celc, fehr = 0;
uint16_t res = 0;

void setup(void) {
    /* Initialize serial interface */
    SerialDebug.begin(115200);

    /* Initialize MCP9808 library */
    err = Mcp9808.begin();    
    if (err < 0) {
        SerialDebug.println("Error: could not start MCP9808 library");
    }
}

void loop(void) {
    /* Set output resolution to +0.125*C */
    Mcp9808.setResolution(res_0125);

    /* Get celcius value from sensor */
    celc = (int)Mcp9808.readTempC();
    /* Get fahrenheit value from sensor */
    fehr = (int)Mcp9808.readTempF();
    /* Get resolution of sensor */
    res = Mcp9808.getResolution();

    /* Print temperature values and sensor resolution via serial interface */
    SerialDebug.printf("Temp (*C): %d\n", celc);
    SerialDebug.printf("Temp (*F): %d\n", fehr);
    SerialDebug.printf("Resolution: %d\n\n", res); // NB: resolution is given in x10000 format

    delay(100);
}