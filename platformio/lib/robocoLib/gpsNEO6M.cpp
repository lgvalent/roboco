#include <Arduino.h>
#include <gpsNEO6M.h>
#include <math.h>

GpsNEO6M::GpsNEO6M(int8_t pinRx, int8_t pinTx)
{
    this->targetLocation = NULL;
    this->previousLocation = NULL;
    this->gpsSwSerial = new SoftwareSerial(pinRx, pinTx);
    this->use_sw_serial = true;
    this->gps = new TinyGPS();
    setup();
}

GpsNEO6M::GpsNEO6M(HardwareSerial *serial)
{
    this->targetLocation = NULL;
    this->previousLocation = NULL;
    this->gpsHwSerial = serial; 
    this->use_sw_serial = false;
    this->gps = new TinyGPS();
    setup();
}

void GpsNEO6M::setup()
{
   if (this->use_sw_serial){ 
     this->gpsSwSerial->begin(9600);
      } else {
         this->gpsHwSerial->begin(9600);
      }
}

boolean GpsNEO6M::readGps()
{ int caracter;
   if (this->use_sw_serial){
      while(this->gpsSwSerial->available()){
         caracter = this->gpsSwSerial->read();
         this->gps->encode(caracter);
      }
   }else{
       while(this->gpsHwSerial->available()){
         caracter = this->gpsHwSerial->read();
         this->gps->encode(caracter);  
      }
   } 
 return this->gps->encode(caracter);
}

Location* GpsNEO6M::getCurrentLocation(){
   if(!this->readGps())
     return NULL;

   this->previousLocation = this->currentLocation;
   Location* location = new Location();


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