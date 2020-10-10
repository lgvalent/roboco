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
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  analogWrite(pinPwm, 0);
  //delay (2000);
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
    int i=0;
    for (i = 1; i <= 255; i++){
        Serial.println ("primeiro for:");
        Serial.println (i);
        move(CLOCKWISE, i);
        i=i+10;
        
    }
    for(i=1; i<= 255; i++){
        Serial.println ("segundo for:");
        Serial.println (i);
        move(ANTICLOCKWISE, i);
        i=i+10;
        
      }
      stop();
}