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

   bool result = true;
   while (this->serial->available()){
      result = this->gps->encode(this->serial->read());
   }
   return result;
}

Location *GpsNEO6M::getCurrentLocation(){

   if (!this->readGps())
      return NULL;
   delete this->previousLocation; // Libera a memória da localização anterior!
   this->previousLocation = this->currentLocation;
   Location *location = new Location();
   
   // Código temporário para teste.
   Serial.println(" ");
   Serial.print((">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Location: "));
   if (this->gps->location.isValid()){
      Serial.print(this->gps->location.lat(), 6); //latitude
      Serial.print((" , "));
      Serial.print(this->gps->location.lng(), 6); //longitude
   }else {
      Serial.print((">>>>>>>>>>>>>>>>>>>>>INVALID>>>>>>>>>>>>>>>>>>"));
   }
   Serial.println(" ");

   //delay(50);

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


   dataTimer->year = this->gps->date.year();
   dataTimer->month = this->gps->date.month();
   dataTimer->day = this->gps->date.day();
   dataTimer->hour = this->gps->time.hour();
   dataTimer->minute = this->gps->time.minute();
   dataTimer->seconds = this->gps->time.second();

   return dataTimer;
}