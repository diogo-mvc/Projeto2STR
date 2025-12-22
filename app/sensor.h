#ifndef APP_SENSOR_H
#define APP_SENSOR_H



#include "../drivers/LM75B/LM75B.h"
#include "../helper/pin_definition.h"

#ifdef __cplusplus
extern "C" {
#endif

// Reads the current temperature from the LM75B sensor
float sensor_read_temperature(void);

// Compares the current temperature to a threshold
// Returns: -1 if below, 0 if equal, 1 if above
int sensor_compare_temperature(float threshold);

//Writes the accelerometer values in the global variables
int sensor_read_gravity(void);


#ifdef __cplusplus
}
#endif

#endif // APP_SENSOR_H