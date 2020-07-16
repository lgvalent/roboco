#include <Arduino.h>
#include <gpsNEO6M.h>
#include <math.h>
#include <SoftwareSerial.h>

GpsNEO6M::GpsNEO6M(int8_t pinRx, int8_t pinTx){
   
   this->targetLocation = NULL;
   this->previousLocation = NULL;

   SoftwareSerial *softwareSerial = new SoftwareSerial(pinRx, pinTx);
   softwareSerial->begin(9600);
   this->serial = softwareSerial;

   this->gps = new TinyGPSPlus();

   setup();
}

GpsNEO6M::GpsNEO6M(HardwareSerial *serial){

   this->targetLocation = NULL;
   this->previousLocation = NULL;
   // serial->begin(115200);
   serial->begin(9600);
   this->serial = serial;

   this->gps = new TinyGPSPlus();
   setup();
}

void GpsNEO6M::setup(){
   // ???
}

boolean GpsNEO6M::readGps(){

   char caracter;
   boolean result = true;
   while (this->serial->available() > 0){
      caracter = this->serial->read();
      if(!this->gps->encode(caracter)){
         // displayInfo(); /// getCurrentLocation()
         result = false;
         break;
      };
      if ((millis() > 5000 ) && (this->gps->charsProcessed() < 10) ){
         Serial.println("No Gps detected");
         while (true);
      }
   }
   return result;
}

Location *GpsNEO6M::getCurrentLocation(){

   if (!this->readGps())
      return NULL;


   this->previousLocation = this->currentLocation;
   Location *location = new Location();

   location->longitude =  this->gps->location.lng();
   location->latitude =  this->gps->location.lat();
   location->angle = getAngleToTarget(location);
   location->time = millis();
   this->currentLocation = location;

   return location;
}

DataTimer *GpsNEO6M::getCurrentDataTimer(){

   if (!this->readGps())
      return NULL;

   DataTimer *dataTimer = new DataTimer();

   dataTimer->year = this->gps->date.year();
   dataTimer->month = this->gps->date.month();
   dataTimer->day = this->gps->date.day();
   dataTimer->hour = this->gps->time.hour();
   dataTimer->minute = this->gps->time.minute();
   dataTimer->seconds = this->gps->time.second();

   return dataTimer;
}