#include "sensor.h"

float sensor_read_temperature(void) {
	return sensor.temp();
}

int sensor_compare_temperature(float threshold) {
	float temp = sensor_read_temperature();
	if (temp < threshold) return -1;
	if (temp > threshold) return 1;
	return 0;
}
