#include <Arduino.h>

#include <gps.h>

GPS::GPS(int8_t pinRx, int8_t pinTx){
  this->gps = new Adafruit_GPS(new SoftwareSerial(pinRx, pinTx));
  setup();
}
GPS::GPS(HardwareSerial* serial){
  this->gps = new Adafruit_GPS(serial);
  setup();
}
void GPS::setup(){
  this->gps->begin(9600);
  this->gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  this->gps->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  this->gps->sendCommand(PGCMD_ANTENNA);
}
boolean GPS::readGps(){
  while(!this->gps->newNMEAreceived()){
    delay(10); //Lucio 20190516: Por quê é necessário este delay? Por causa do SoftwareSerial? Fazer um teste sem este delay, ou com delay(1)
    this->gps->read();
  }
  return this->gps->parse(this->gps->lastNMEA());
}

Location* GPS::getCurrentLocation(){
  if(!this->readGps())
    return NULL;

  Location* location = new Location();
  location->longitude = this->gps->longitudeDegrees;
  location->latitude = this->gps->latitudeDegrees;
  location->altitude = this->gps->altitude;
  location->angle = this->gps->angle;

  return location;
}

DataTimer* GPS::getCurrentDataTime(){
  if(!this->readGps())
    return NULL;

  DataTimer* dataTimer = new DataTimer();
  dataTimer->day = this->gps->day;
  dataTimer->month = this->gps->month;
  dataTimer->year = this->gps->year;
  dataTimer->hour = this->gps->hour;
  dataTimer->minute = this->gps->minute;
  dataTimer->seconds = this->gps->seconds;

  return dataTimer;
}
