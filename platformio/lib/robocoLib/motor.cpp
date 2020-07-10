#include <Arduino.h>
#include <motor.h>

Motor::Motor(int8_t pin1, int8_t pin2, int8_t pinPwm){

  this->pin1=pin1;
  this->pin2=pin2;
  this->pinPwm=pinPwm;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pinPwm, OUTPUT);
  this->stop();
}

void Motor::stop(){
  analogWrite(pinPwm, 0);
}

void Motor::move(MotorDirection direction, unsigned char speed){
  
  if(direction == CLOCKWISE){
     digitalWrite(pin1, HIGH);
     digitalWrite(pin2, LOW);   
  }else{
     digitalWrite(pin1, LOW);
     digitalWrite(pin2, HIGH);
  }
  analogWrite(pinPwm, speed);
}

void Motor::test(){
    Serial.print("Testing Motor: ");
    for (int i = 1; i <= 255; i++){
        move(CLOCKWISE, i);
        move(ANTICLOCKWISE, i);
    }
}