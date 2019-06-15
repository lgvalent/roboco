#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>


class Sensors : public Mhz{
  private:
    int8_t pin_A15; // SENSOR LDR
    Adafruit_BMP280* bmp;
    Mhz* sensorCo2;
  public:
    Sensors(int8_t pinLum, int8_t pinRxCo2, int8_t pinTxCo2, int8_t pwmCo2);
    Sensors(int8_t pinLum, HardwareSerial* serial, int8_t pwmCo2);
    float getTemperatureC();
    float getCO2ppm();
    float getAltitude();
    float getAtmosphericPressure();
    float getLuminosity();
    bool bmpValid();
};
class Mhz{
  private:
  int8_t pwm;
  Mhz* serial;
  public:
  Mhz(int8_t rx, int8_t tx, int8_t pwm);
  Mhz(HardwareSerial* serial);

};
#endif
