#include<Arduino.h>


#include "gps.h"

#define GPSECHO  true
GPS::GPS(int8_t pinRx, int8_t pinTx){
    this->gps = new Adafruit_GPS(new SoftwareSerial(pinRx,pinTx));
    iniciando();
}
GPS::GPS(HardwareSerial * serial){
      this->gps = new Adafruit_GPS(serial);
      iniciando();
}
void GPS::iniciando(){
  this->gps->begin(9600);
  this->gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  this->gps->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  this->gps->sendCommand(PGCMD_ANTENNA);
}
void GPS::readGps(){
  bool x = false;
  char c=0;
  while(x == false){
    delay(10);
    c = this->gps->read();
    /*if (GPSECHO){ 
      if(c=='$'){
        Serial.println();
      }
      Serial.print(c);
    }*/
  if (this->gps->newNMEAreceived()) {
    x = true;
    if (!this->gps->parse(this->gps->lastNMEA())){
		  //receber sentença correta
      }
    }
  }
}

Location* GPS::getCurrentLocation(){
  Location* location = new Location();
  this->readGps();
    location->longitude = this->gps->longitudeDegrees;
    location->latitude = this->gps->latitudeDegrees;
    location->altitude = this->gps->altitude;
    location->angle = this->gps->angle;
  
  return location; 

}

DataTimer* GPS::getCurrentDataTimer(){
  DataTimer* dataTimer = new DataTimer();
  this->readGps();
    dataTimer->day = gps->day;
    dataTimer->month = gps->month;
    dataTimer->year = gps->year;
    dataTimer->hour  = gps->hour;
    dataTimer->minute = gps->minute;
    dataTimer->seconds = gps->seconds;

  return dataTimer;
}
void GPS::testeGps(){
  Location* loc = getCurrentLocation();
  DataTimer* dat = getCurrentDataTimer();
    if (millis() - timer > 2000) {
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
