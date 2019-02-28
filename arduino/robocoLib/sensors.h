#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>

class Sensors{
  private:
    int8_t pin_A15;
    Adafruit_BMP280* bmp;
  public:
    Sensors(int8 pinLum);
	float getTemperatureC();
	float getCO2ppm();
	float getAltitude();
	float getAtmosphericPressure();
	float getLuminosity();
};
#endif
