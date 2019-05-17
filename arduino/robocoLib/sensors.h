#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <Adafruit_BMP280.h>

class Sensors{
  private:
    int8_t pin_A15;
    Adafruit_BMP280* bmp;
    SoftwareSerial* serialCO2;

  public:
    Sensors(int8_t pinLum, int8_t pinRxCo2, int8_t pinTxCo2);
    float getTemperatureC();
    float getCO2ppm();
    float getAltitude();
    float getAtmosphericPressure();
    float getLuminosity();
};
#endif
