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

   if (!this->readGps())
      return NULL;

   // Código temporário para teste.
   Serial.println(" ");
   Serial.print((">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Location: "));
   if (this->gps->location.isValid()){
      *(this->previousLocation)=*(this->currentLocation); // guardando currentLocation
      Serial.print(this->gps->location.lat(), 6); //latitude
      Serial.print((" , "));
      Serial.print(this->gps->location.lng(), 6); //longitude
   }else {
      Serial.print((">>>>>>>>>>>>>>>>>>>>>INVALID>>>>>>>>>>>>>>>>>>"));
   }
   Serial.println(" ");

   //delay(50);

   this->currentLocation->longitude =  this->gps->location.lng();
   this->currentLocation->latitude =  this->gps->location.lat();
   this->currentLocation->angle = getAngleToTarget(this->currentLocation);
   this->currentLocation->time = millis();

   return this->currentLocation;
}

DateTime *GpsNEO6M::getCurrentDateTime(){

   if (!this->readGps())
      return NULL;

   // Código temporário para teste.
   Serial.print(("------------------------------- Date: "));
   if (this->gps->date.isValid()) {
      Serial.print(this->gps->date.day()); //dia
      Serial.print(("/"));
      Serial.print(this->gps->date.month()); //mes
      Serial.print(("/"));
      Serial.print(this->gps->date.year()); //ano
   } else {
      Serial.print(("---------------------INVALID--------------------"));
   }
   delay(50);

   Serial.println((""));
   Serial.print(("++++++++++++++++++++++++++++++++++++ Time:  "));
   if (this->gps->time.isValid()){
      if (this->gps->time.hour() < 10)
         Serial.print(("0"));
         Serial.print(this->gps->time.hour()); //hora
          Serial.print((":"));
      if (this->gps->time.minute() < 10)
         Serial.print(("0"));
         Serial.print(this->gps->time.minute()); //minuto
         Serial.print((":"));
      if (this->gps->time.second() < 10)
         Serial.print(("0"));
         Serial.print(this->gps->time.second()); //segundo
         Serial.print(("."));
      if (this->gps->time.centisecond() < 10)
         Serial.print(("0"));
         Serial.print(this->gps->time.centisecond());
   } else {
      Serial.print(("+++++++++++++++++++++++INVALID++++++++++++++++++++"));
   }
   delay(50);
   Serial.println(" ");


   this->currentDateTime->year = this->gps->date.year();
   this->currentDateTime->month = this->gps->date.month();
   this->currentDateTime->day = this->gps->date.day();
   this->currentDateTime->hour = this->gps->time.hour();
   this->currentDateTime->minute = this->gps->time.minute();
   this->currentDateTime->seconds = this->gps->time.second();

   return this->currentDateTime;
}