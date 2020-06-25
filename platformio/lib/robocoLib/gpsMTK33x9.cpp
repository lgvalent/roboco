#include <Arduino.h>
#include <gpsMTK33x9.h>
#include <math.h>

GpsMTK33x9::GpsMTK33x9(int8_t pinRx, int8_t pinTx)
{
  this->targetLocation = NULL;
  this->previousLocation = NULL;

  this->gps = new Adafruit_GPS(new SoftwareSerial(pinRx, pinTx));
  setup();
}

GpsMTK33x9::GpsMTK33x9(HardwareSerial *serial)
{
  this->targetLocation = NULL;
  this->previousLocation = NULL;

  this->gps = new Adafruit_GPS(serial);
  setup();
}

void GpsMTK33x9::setup()
{
  this->gps->begin(9600);
  this->gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  this->gps->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  this->gps->sendCommand(PGCMD_ANTENNA);
}

boolean GpsMTK33x9::readGps()
{
  if (!this->gps->newNMEAreceived())
  {
    delay(10); //Lucio 20190516: Por quê é necessário este delay? Por causa do SoftwareSerial? Fazer um teste sem este delay, ou com delay(1)
    this->gps->read();
  }
  return this->gps->parse(this->gps->lastNMEA());
}

Location* GpsMTK33x9::getCurrentLocation(){
  if(!this->readGps())
    return NULL;
  this->previousLocation = this->currentLocation;

  Location* location = new Location();
  location->longitude = this->gps->longitudeDegrees;
  location->latitude = this->gps->latitudeDegrees;
  location->altitude = this->gps->altitude;
  location->angle = getAngleToTarget(location);
  location->time = millis();

  this->currentLocation = location;
  return location;
}

DataTimer *GpsMTK33x9::getCurrentDataTimer()
{
  if (!this->readGps())
    return NULL;

  DataTimer *dataTimer = new DataTimer();
  dataTimer->day = this->gps->day;
  dataTimer->month = this->gps->month;
  dataTimer->year = this->gps->year;
  dataTimer->hour = this->gps->hour;
  dataTimer->minute = this->gps->minute;
  dataTimer->seconds = this->gps->seconds;

  return dataTimer;
}

