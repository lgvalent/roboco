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
  
    unsigned char comando = 0, pwm = 0;
    Serial.println("TESTING MOTOR");

    while (comando != 1){
        Serial.print("MOTOR TEST");
        Serial.print("ENTER THE COMAND");
        while (Serial.available()){
            comando = Serial.read();
            Serial.print("MOTOR TEST");
            Serial.print("comando : ");
            Serial.println(comando - 48);
            switch (comando){
                case '2':
                    Serial.print("BACK");
                    this->motorRight->move(ANTICLOCKWISE, pwm);
                    this->motorLeft->move(ANTICLOCKWISE, pwm);
                    delay(2000);
                    this->motorRight->stop();
                    this->motorLeft->stop();
                    break;

                case '4':
                    Serial.print("LEFT");
                    this->motorRight->move(CLOCKWISE, pwm);
                    this->motorLeft->move(ANTICLOCKWISE, pwm);
                    delay(2000);
                    this->motorRight->stop();
                    this->motorLeft->stop();
                    break;

                case '6':
                    Serial.print("RIGHT");
                    this->motorRight->move(ANTICLOCKWISE, pwm);
                    this->motorLeft->move(CLOCKWISE, pwm);
                    delay(2000);
                    this->motorRight->stop();
                    this->motorLeft->stop();
                    break;
                case '8':
                    Serial.print("FORWARD");
                    this->motorRight->move(CLOCKWISE, pwm);
                    this->motorLeft->move(CLOCKWISE, pwm);
                    delay(2000);
                    this->motorRight->stop();
                    this->motorLeft->stop();
                    break;
                case '1':
                    comando = 1;
                    break;
                case '7':
                    if (pwm > 50)
                        pwm = pwm - 51;
                    Serial.print(" PWM : ");
                    Serial.print(String(pwm));
                    Serial.print("PWM : ");
                    Serial.println(pwm);
                    delay(1000);
                    break;
                case '9':
                    if (pwm < 205)
                        pwm = pwm + 51;
                    Serial.print(" PWM : ");
                    Serial.print(String(pwm));
                    Serial.print("PWM : ");
                    Serial.println(pwm);
                    delay(1000);
                    break;
            }
        }
    }
    Serial.println("saindo");
    Serial.print("EXISTING");
    Serial.print("MOTOR TEST");
    delay(2000);
}