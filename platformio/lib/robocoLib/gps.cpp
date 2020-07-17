#include <Arduino.h>
#include <gps.h>
#include <math.h>

float GPS::getDistanceToTarget(){

  float lat1 = currentLocation->latitude * 3.1415927 / 180;
  float lon1 = currentLocation->longitude * 3.1415927 / 180;
  float lat2 = targetLocation->latitude * 3.1415927 / 180;
  float lon2 = targetLocation->longitude * 3.1415927 / 180;
  float Raio_da_terra = 6371000; // km
  float dLat = (lat2 - lat1);    //diferença das latitudes dos pontos em radianos
  float dLon = (lon2 - lon1);    //diferença das longitudes dos pontos em radianos
  float a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  return Raio_da_terra * c; //distancia em metros
}

Location *GPS::getPreviousLocation(){
  return this->previousLocation;
}

void GPS::setTargetLocation(float latitude, float longitude){

  if (this->targetLocation == NULL)
    this->targetLocation = new Location;

  this->targetLocation->latitude = latitude;
  this->targetLocation->longitude = longitude;
}

float angleBetweenLines(float cx0, float cy0, float cx1, float cy1, float tx0, float ty0, float tx1, float ty1){

  float mt, mc, tg = 0, tgg = 0;
  //pra uma reta ser paralela ao eixo y: valores de x precisam ser iguais
  mt = (ty1 - ty0) / (tx1 - tx0); // calculo do coeficiente angular da reta 1.
  tg = 1 / mt; // calculo da tangente da reta 1.
  mc = (cy1 - cy0) / (cx1 - cx0); // calculo do coeficiente angular da reta 2.
  tgg = 1 / mc; // calculo da tangente da reta 2.

  if (mt = !mc){ // verificando se as retas não são paralelas e retornando o angulo em graus.
    float angle = tg - tgg;
    return 180 / M_PI * atan(angle);
  }
  return 0;
}

float GPS::getAngleToTarget(Location *currentLocation){

  // Verifica se tem um previous location != NULL
  if (this->previousLocation == NULL){
    return 0;
  }

  float cx0 = this->previousLocation->longitude;
  float cy0 = this->previousLocation->latitude;
  float cx1 = currentLocation->longitude;
  float cy1 = currentLocation->latitude;
  float tx0 = currentLocation->longitude;
  float ty0 = currentLocation->latitude;
  float tx1 = this->targetLocation->longitude;
  float ty1 = this->targetLocation->latitude;

  return angleBetweenLines(cx0, cy0, cx1, cy1, tx0, ty0, tx1, ty1);
}

void GPS::test(){

  Location *loc = getCurrentLocation();
  DataTimer *dat = getCurrentDataTimer();
  unsigned long timer = millis();

  // Para testar o GPS temporariamente estamos usando os prints no GPSNEO6M.cpp
  
  /*delay(500);
  Serial.print("Testing GPS: ");
  Serial.print(dat->year);
  Serial.print("/");
  Serial.print(dat->month);
  Serial.print("/");
  Serial.print(dat->day);
  Serial.print(" ");
  Serial.print(dat->hour);
  Serial.print(":");
  Serial.print(dat->minute);
  Serial.print(":");
  Serial.print(dat->seconds);
  Serial.println();
  Serial.print("Latitude: ");
  Serial.println(loc->latitude, 6);
  Serial.print("Longitude: ");
  Serial.println(loc->longitude, 6);
  Serial.print("Altitude: ");
  Serial.println(loc->altitude);
  Serial.print("Angle: ");
  Serial.println(loc->angle);
   delay(500);*/

}