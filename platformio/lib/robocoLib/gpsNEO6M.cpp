#include <Arduino.h>
#include <gpsNEO6M.h>
#include <math.h>
#include <SoftwareSerial.h>

GpsNEO6M::GpsNEO6M(int8_t pinRx, int8_t pinTx){
   
   SoftwareSerial *softwareSerial = new SoftwareSerial(pinRx, pinTx);
   softwareSerial->begin(9600);
   this->serial = softwareSerial;

   this->gps = new TinyGPSPlus();

   setup();
}

GpsNEO6M::GpsNEO6M(HardwareSerial *serial){

   serial->begin(9600);
   this->serial = serial;

   this->gps = new TinyGPSPlus();
   setup();
}

void GpsNEO6M::setup(){
   // ???
}

boolean GpsNEO6M::readGps(){

   bool result = true;
   while (this->serial->available()){
      result = this->gps->encode(this->serial->read());
   }
   return result;
}

Location *GpsNEO6M::getCurrentLocation(){

   if (this->gps->location.isValid()){
      *(this->previousLocation)=*(this->currentLocation); // guardando currentLocation
      this->currentLocation->longitude =  this->gps->location.lng();
      this->currentLocation->latitude =  this->gps->location.lat();
      this->currentLocation->altitude = this->gps->altitude.meters();
   }else {
      return NULL;
   }

   this->currentLocation->angle = this->getAngleToTarget();

   return this->currentLocation;
}

DateTime *GpsNEO6M::getCurrentDateTime(){

   if (this->gps->date.isValid()) {
      this->currentDateTime->day = this->gps->date.day();
      this->currentDateTime->month = this->gps->date.month();
      this->currentDateTime->year = this->gps->date.year();
   } else {
      return NULL;
   }

   if (this->gps->time.isValid()){
         this->currentDateTime->hour = this->gps->time.hour()-3;
         this->currentDateTime->minute = this->gps->time.minute();
         this->currentDateTime->seconds = this->gps->time.second();
   } else {
      return NULL;
   }

   return this->currentDateTime;
}