#include <Arduino.h>

#include <sensors.h>


Sensors::Sensors(int8_t pinLum, int8_t pinRxCo2, int8_t pinTxCo2, int8_t pwmCo2) {
  this->pin_A15 = pinLum;
  this->pwmC02 = pwmCo2;
  this->bmp = new Adafruit_BMP280();
  pinMode(pinLum, INPUT);
  this->bmp->begin(0x76);
  //this->serialCO2 = new Mhz(pinRxCo2, pinTxCo2, pwmCo2); // RX, TX
}
Sensors::Sensors(int8_t pinLum, HardwareSerial* serial, int8_t pwmCo2) {
  this->pin_A15 = pinLum;
  this->bmp = new Adafruit_BMP280();
  pinMode(pinLum, INPUT);
  this->bmp->begin(0x76);

  //this->serialCO2->serial; // RX, TX
}
bool Sensors::bmpValid(){
  Serial.println("boaa");
    if(!this->bmp->begin(0x76)) {
      Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
      return false;  
    }else{
      Serial.println("true");
      return true;
    }
}
float Sensors::getLuminosity(){
  int valLum = analogRead(this->pin_A15);
  return(valLum);
}
  
float Sensors::getTemperatureC(){
  return(bmp->readTemperature());
}

float Sensors::getAltitude(){
  return(bmp->readAltitude(1013.25)); // this should be adjusted to your local forcase
}

float Sensors::getAtmosphericPressure(){
 return(bmp->readPressure());
}
/* 
float Sensors::getCO2ppm(){
  byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
  char response[9];
  int prevVal = LOW;
  long ppm = 0.0;
  this->serialCO2->write(cmd,9);
  this->serialCO2->readBytes(response, 9);
  int responseHigh = (int) response[2];
  int responseLow = (int) response[3];
  ppm = (256*responseHigh)+responseLow;
  return (ppm);
}*/
