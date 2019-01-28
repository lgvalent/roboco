#ifndef SENSOR_CPP
#define SENSOR_CPP
#include <Arduino.h>
enum SensorDirection{
  CLOCKWISE_,
  ANTICLOCKWISE_ 
};

class Sensor{
  private:
    int8_t pin1;
    int8_t pin2;
    int8_t pinPwm;  
  public:
    Sensor(int8_t pin1, int8_t pin2, int8_t pinPwm);
    void stop();
    void move(SensorDirection direction,unsigned char speed);  
};
#endif
