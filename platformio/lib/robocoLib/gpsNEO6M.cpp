#include <Arduino.h>
#include <gpsNEO6M.h>
#include <math.h>
#include <SoftwareSerial.h>

GpsNEO6M::GpsNEO6M(int8_t pinRx, int8_t pinTx)
{
   this->targetLocation = NULL;
   this->previousLocation = NULL;

   SoftwareSerial *softwareSerial = new SoftwareSerial(pinRx, pinTx);
   softwareSerial->begin(9600);
   this->serial = softwareSerial;

   this->gps = new TinyGPS();

   setup();
}

GpsNEO6M::GpsNEO6M(HardwareSerial *serial)
{
   this->targetLocation = NULL;
   this->previousLocation = NULL;

   serial->begin(9600);
   this->serial = serial;

   this->gps = new TinyGPS();
   setup();
}

void GpsNEO6M::setup()
{
}

boolean GpsNEO6M::readGps()
{
   int caracter;
   while (this->serial->available())
   {
      caracter = this->serial->read();
      this->gps->encode(caracter);
   }

   return this->gps->encode(caracter);
}

Location *GpsNEO6M::getCurrentLocation()
{
   if (!this->readGps())
      return NULL;

   this->previousLocation = this->currentLocation;
   Location *location = new Location();

   this->gps->f_get_position(&location->latitude, &location->longitude);
   this->gps->f_altitude(); // altitude em metros
   location->angle = getAngleToTarget(location);
   location->time = millis();
   this->currentLocation = location;
   return location;
}

DataTimer *GpsNEO6M::getCurrentDataTimer()
{
   if (!this->readGps())
      return NULL;

   DataTimer *dataTimer = new DataTimer();

   //this->gps->crack_datetime(&dataTimer->year, &dataTimer->month, &dataTimer->day, &dataTimer->hour, &dataTimer->minute, &dataTimer->seconds, &hundredths, &fix_age);
   // Usando o exemplo dado no documento da biblioteca TinyGPS. Porém ele utiliza dois parametros (hundredths, fix_age) que não estamos usando no gps.h

   unsigned long date, hour;
   this->gps->get_datetime(&date, &hour);

   dataTimer->day = (date / 10000);
   dataTimer->month = ((date % 1000) / 100);
   dataTimer->year = (date % 100);
   dataTimer->hour = (hour / 1000000);
   dataTimer->minute = ((hour % 1000000) / 10000);
   dataTimer->seconds = ((hour % 10000) / 100);

   return dataTimer;
}