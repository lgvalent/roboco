#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>

class Sensors{
  private:
//    int8_t pin1;
//    int8_t pin2;
//    int8_t pinPwm;  
  public:
    Sensors(/* Coloque os dados que precisam para configurar os sensores pinos, seriais, etcs*/ );
    float getTemperatureC();
    float getCO2Ppm();
    float getRelativeHumidity();
	float getAtmosphericPressure();
	float getLuminosity();
};
#endif
