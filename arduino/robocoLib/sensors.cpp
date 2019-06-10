#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include <SoftwareSerial.h>

#include <sensors.h>


Sensors::Sensors(int8_t pinLum, int8_t pinRxCo2, int8_t pinTxCo2) {
  this->pin_A15 = pinLum;
  this->bmp = new Adafruit_BMP280();
  pinMode(pinLum, OUTPUT);

  this->serialCO2 = new SoftwareSerial(pinRxCo2, pinTxCo2); // RX, TX
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
}
