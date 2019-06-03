#include <Arduino.h>

#include <output.h>

Output::Output(int8_t pinLed0, int8_t pinLed1, int8_t pinLed2){
    this->pinLed0=pinLed0;
    this->pinLed1=pinLed1;
    this->pinLed2=pinLed2;
  
    pinMode(pinLed0, OUTPUT);
    pinMode(pinLed1, OUTPUT);
    pinMode(pinLed2, OUTPUT);
}

void Output::setLed0(boolean on){
        digitalWrite(pinLed0, on?HIGH:LOW);
}

void Output::setLed1 (boolean on){
        digitalWrite(pinLed1, on?HIGH:LOW);
}

void Output::setLed2(boolean on){
        digitalWrite(pinLed2, on?HIGH:LOW);
}

      // Testing LEDs
        this->output->setLed0(true);
        delay(DELAY);
        this->output->setLed0(false);
        this->output->setLed1(true);
        delay(DELAY);
        this->output->setLed1(false);
        this->output->setLed2(true);
        delay(DELAY);
        this->output->setLed2(false);
