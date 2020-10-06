#include <Arduino.h>
#include <gps.h>
#include <math.h>

void GPS::setCompassSensor(Sensor* compassSensor){
  if(compassSensor->getType() == COMPASS){
    this->compassSensor = compassSensor;
    Serial.println (compassSensor->getType());
  }
  else
    Serial.println("Sensor is not a COMPASS type.");
}

Sensor* GPS::getCompassSensor(){
  return this->compassSensor;
}
   
float GPS::getDistanceToTarget(){

  float lat1 = currentLocation->latitude * PI / 180;     // atual
  float lon1 =  currentLocation->longitude * PI / 180;
  float lat2 = targetLocation->latitude * PI / 180;      // alvo
  float lon2 = targetLocation->longitude * PI / 180;
  float Raio_da_terra = 6371; // km
  float dLat = (lat2 - lat1);    //diferença das latitudes dos pontos em radianos
  float dLon = (lon2 - lon1);    //diferença das longitudes dos pontos em radianos
  float a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  Serial.println ("currentLocation Latitude / longitude: ");
  Serial.println (currentLocation->latitude, 6);
  Serial.println (currentLocation->longitude, 6);
  Serial.println ("targetLocation Latitude / longitude: ");
  Serial.println (targetLocation->latitude, 6);
  Serial.println (targetLocation->longitude, 6);
  Serial.println ("Distancia: ");
  Serial.println ((Raio_da_terra* c) *1000);
  return (Raio_da_terra* c) *1000; //distancia em metros
}

Location *GPS::getPreviousLocation(){
  return this->previousLocation;
}

Location* GPS::getTargetLocation(){
  return this->targetLocation;
}

void GPS::setTargetLocation(float latitude, float longitude){

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

float GPS::getAngleToTarget(){

  if (this->compassSensor != NULL){

    // Compute the forward azimuth
    // SOURCE:
    // **************************************************
    
    float currentLongitudeRad = radians(currentLocation->longitude);
    float currentLatitudeRad = radians(currentLocation->latitude);
    float targetLongitudeRad = radians(this->targetLocation->longitude);
    float targetLatitudeRad = radians(this->targetLocation->latitude);

    float angleToTarget = atan2(sin(targetLongitudeRad - currentLongitudeRad) * cos(targetLatitudeRad),
                                cos(currentLatitudeRad) * sin(targetLatitudeRad) - sin(currentLatitudeRad) * cos(targetLatitudeRad) * cos(targetLongitudeRad - currentLongitudeRad));

    angleToTarget = angleToTarget * 180 / PI; // Convert from radians to degrees

    return angleToTarget;

  }else{
    //Verifica se tem um previous location != NULL
    if (this->previousLocation == NULL){
      return 0;
    }
    float cx0 = this->previousLocation->longitude; // anterior
    float cy0 = this->previousLocation->latitude;

    float cx1 = currentLocation->longitude; // atual
    float cy1 = currentLocation->latitude;
    float tx0 = currentLocation->longitude;
    float ty0 = currentLocation->latitude;

    float tx1 = this->targetLocation->longitude; // alvo
    float ty1 = this->targetLocation->latitude;
  
    return angleBetweenLines(cx0, cy0, cx1, cy1, tx0, ty0, tx1, ty1);
  }
}

boolean GPS::test(){

  Location *loc = getCurrentLocation();
  DateTime *dat = getCurrentDateTime();

  if(loc != NULL && dat != NULL){  // verificação da leitura 

    Serial.println(" ");
    Serial.println("Testing GPS: ");
    Serial.print("Date: ");
    Serial.print(dat->day);
    Serial.print("/");
    Serial.print(dat->month);
    Serial.print("/");
    Serial.print(dat->year);
    Serial.println(" ");
    Serial.print("Time: ");
    Serial.print(dat->hour);
    Serial.print(":");
    Serial.print(dat->minute);
    Serial.print(":");
    Serial.print(dat->seconds);
    Serial.println();
    Serial.print("Latitude: ");
    Serial.println(loc->latitude, 9);
    Serial.print("Longitude: ");
    Serial.println(loc->longitude, 9);
    Serial.print("Altitude: ");
    Serial.println(loc->altitude);
    Serial.print("Angle: ");
    Serial.println(loc->angle);
    return true;
  } else {
    return false;
  }
}