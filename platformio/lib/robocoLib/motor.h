#ifndef MOTOR_CPP
#define MOTOR_CPP
#include <Arduino.h>
#include <output.h>
#include <gps.h>

enum MotorDirection{
  CLOCKWISE,
  ANTICLOCKWISE 
};

class Motor{
  
  private:
    int8_t pin1;
    int8_t pin2;
    int8_t pinPwm;  
    Motor* motorLeft,* motorRight;
    
  public:
    Motor(int8_t pin1, int8_t pin2, int8_t pinPwm);
    void stop();
    void move(MotorDirection direction, unsigned char speed);
    void test();
};
#endif