#ifndef OUTPUT_H
#define OUTPUT_H
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Output{

  private:
      int8_t pinLed0;
      int8_t pinLed1;
      int8_t pinLed2;
      LiquidCrystal_I2C* lcd;
  
  public:
    Output(int8_t pinLed0, int8_t pinLed1, int8_t pinLed2);
    void lcdPrint(String p,uint8_t column, uint8_t line);
    void lcdClear();
    //void lcdAutoScroll(boolean on);
    void setLed0(boolean on);  
    void setLed1(boolean on);  
    void setLed2(boolean on);
    void test();   
};
#endif