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

void GpsMTK33x9::testeGpsMTK33x9(){
  Location* loc = getCurrentLocation();
  DataTimer* dat = getCurrentDataTimer();
  unsigned long timer = millis();
    if (millis() - timer > 100) {
    timer = millis(); // reset the timer  
    Serial.print("\nTime: ");
    Serial.print((dat->hour-3), DEC); Serial.print(':');
    Serial.print(dat->minute, DEC); Serial.print(':');
    Serial.print(dat->seconds, DEC); Serial.print('.');
    Serial.print("Date: ");
    Serial.print(dat->day, DEC); Serial.print('/');
    Serial.print(dat->month, DEC); Serial.print("/20");
    Serial.println(dat->year, DEC);
    Serial.print("Fix: "); Serial.print((int)gps->fix);
    Serial.print(" quality: "); Serial.println((int)gps->fixquality);
    Serial.print("Location (in degrees, works with Google Maps): ");
    Serial.println(loc->latitude, 4);
    Serial.print("Location (in degrees, works with Google Maps): ");
    Serial.println(loc->longitude,4);      
    Serial.print("Speed (knots): "); Serial.println(gps->speed);
    Serial.print("Angle: "); Serial.println(loc->angle);
    Serial.print("Altitude: "); Serial.println(loc->altitude);
    Serial.print("Satellites: "); Serial.println((int)gps->satellites);
   free(dat);
   free(loc);
  }
}

