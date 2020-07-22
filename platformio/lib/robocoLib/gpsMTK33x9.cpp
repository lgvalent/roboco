#include <Arduino.h>
#include <gpsMTK33x9.h>
#include <math.h>

GpsMTK33x9::GpsMTK33x9(int8_t pinRx, int8_t pinTx){

  this->gps = new Adafruit_GPS(new SoftwareSerial(pinRx, pinTx));
  setup();
}

GpsMTK33x9::GpsMTK33x9(HardwareSerial *serial){

  this->gps = new Adafruit_GPS(serial);
  setup();
}

void GpsMTK33x9::setup(){

  this->gps->begin(9600);
  this->gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  this->gps->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  this->gps->sendCommand(PGCMD_ANTENNA);
}

boolean GpsMTK33x9::readGps(){

  if (!this->gps->newNMEAreceived()){
    delay(10); //Lucio 20190516: Por quê é necessário este delay? Por causa do SoftwareSerial? Fazer um teste sem este delay, ou com delay(1)
    this->gps->read();
  }
  return this->gps->parse(this->gps->lastNMEA());
}

Location* GpsMTK33x9::getCurrentLocation(){
  
  if(!this->readGps())
    return NULL;

  *(this->previousLocation)=*(this->currentLocation); // guardando currentLocation
  
  this->currentLocation->longitude = this->gps->longitudeDegrees;
  this->currentLocation->latitude = this->gps->latitudeDegrees;
  this->currentLocation->altitude = this->gps->altitude;
  this->currentLocation->angle = getAngleToTarget(this->currentLocation);
  this->currentLocation->time = millis();

  return this->currentLocation;
  
}

DateTime *GpsMTK33x9::getCurrentDateTime(){

  if (!this->readGps())
    return NULL;

  this->currentDateTime->year = 2000 + this->gps->year;
  this->currentDateTime->month = this->gps->month;
  this->currentDateTime->day = this->gps->day;
  this->currentDateTime->hour = this->gps->hour;
  this->currentDateTime->minute = this->gps->minute;
  this->currentDateTime->seconds = this->gps->seconds;

  return this->currentDateTime;
}