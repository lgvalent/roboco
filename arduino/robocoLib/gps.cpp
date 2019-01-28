#include <Arduino.h>
#include "sensor.h"

Sensor::Sensor(int8_t pin1, int8_t pin2, int8_t pinPwm){
  this->pin1=pin1;
  this->pin2=pin2;
  this->pinPwm=pinPwm;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pinPwm, OUTPUT);
  this->stop();
}

void Sensor::stop(){
  analogWrite(pinPwm, 0);
}
void Sensor::move(SensorDirection direction,unsigned char speed){
  
  if(direction == CLOCKWISE_){
     digitalWrite(pin1, HIGH);
     digitalWrite(pin2, LOW);   
  }else{
     digitalWrite(pin1, LOW);
     digitalWrite(pin2, HIGH);
  }
  analogWrite(pinPwm, speed);
}

