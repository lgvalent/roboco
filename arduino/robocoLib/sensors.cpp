#include <Arduino.h>
#include "sensors.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(pinTxCo2,pinRxCo2); // RX, TX
byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
char response[9];
int prevVal = LOW;
long ppm = 0.0;

Sensor::Sensor(int8_t pinLum) {
  this->bpm = new Adafruit_BMP280();
  this->pinA15 = pinLum;
  pinMode(A15, OUTPUT);
  this->stop();
}

float Sensor::getLuminosity(){
  int valLum = analogRead(pinA15);
  return(valLum);
}
  
float Sensor::getTemperature(){
  return(bmp.readTemperature());
}

float Sensor::getAltitude(){
  return(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
}

float Sensor::getAtmosphericPressure(){
 return(bmp.readPressure());
}

float sensor::getCO2ppm(){
  mySerial.write(cmd,9);
  mySerial.readBytes(response, 9);
  int responseHigh = (int) response[2];
  int responseLow = (int) response[3];
  ppm = (256*responseHigh)+responseLow;
  return (ppm);
}
