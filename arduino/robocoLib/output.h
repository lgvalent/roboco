#ifndef OUTPUT_H
#define OUTPUT_H
#include <Arduino.h>

class Output{
  private:
  public:
    Output(int8_t pinLed0, int8_t pinLed1, int8_t pinLed2);
    void setLed0(boolean on);  
    void setLed1(boolean on);  
    void setLed2(boolean on);  
};
#endif
