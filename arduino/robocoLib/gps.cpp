#include <Arduino.h>
#include <gps.h>
#include <math.h>

GPS::GPS(int8_t pinRx, int8_t pinTx){
  this->targetLocation = NULL;
  this->previousLocation = NULL;

  this->gps = new Adafruit_GPS(new SoftwareSerial(pinRx, pinTx));
  setup();
}

GPS::GPS(HardwareSerial* serial){
  this->targetLocation = NULL;
  this->previousLocation = NULL;

  this->gps = new Adafruit_GPS(serial);
  setup();
}
void GPS::setup(){
  this->gps->begin(9600);
  this->gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  this->gps->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  this->gps->sendCommand(PGCMD_ANTENNA);
}
boolean GPS::readGps(){  
  if(!this->gps->newNMEAreceived()){
    Serial.print("oie");
    delay(10); //Lucio 20190516: Por quê é necessário este delay? Por causa do SoftwareSerial? Fazer um teste sem este delay, ou com delay(1)
    this->gps->read();
  }
  return this->gps->parse(this->gps->lastNMEA());
}
float GPS::getDistanceToTarget(){
  float lat1 = currentLocation->latitude * 3.1415927 / 180;
  float lon1 = currentLocation->longitude * 3.1415927 / 180;
  float lat2 = targetLocation->latitude * 3.1415927 / 180;
  float lon2 = targetLocation->longitude * 3.1415927 / 180;
  float Raio_da_terra = 6371000; // km
  float dLat = (lat2-lat1); //diferenÃ§a das latitudes dos pontos em radianos
  float dLon = (lon2-lon1); //diferenÃ§a das longitudes dos pontos em radianos
  float a = sin(dLat/2) * sin(dLat/2) + cos(lat1) * cos(lat2) * sin(dLon/2) * sin(dLon/2);
  float c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  distancia = Raio_da_terra * c; //distancia em metros
  Serial.println(distancia,6);
}

}

Location* GPS::getPreviousLocation(){
  return this->previousLocation;
}

Location* GPS::getCurrentLocation(){
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

DataTimer* GPS::getCurrentDataTimer(){
  Serial.print("ACORDAAA");
  if(!this->readGps())
    return NULL;

  DataTimer* dataTimer = new DataTimer();
  dataTimer->day = this->gps->day;
  dataTimer->month = this->gps->month;
  dataTimer->year = this->gps->year;
  dataTimer->hour = this->gps->hour;
  dataTimer->minute = this->gps->minute;
  dataTimer->seconds = this->gps->seconds;

  return dataTimer;
}

void GPS::setTargetLocation(float latitude, float longitude){
  if (this->targetLocation == NUUL)
    this->targetLocation = new Location;

  this->targetLocation.latitude = latitude;
  this->targetLocation.longitude = longitude;
}

float GPS::getAngleToTarget(Location* currentLocation){

  // Verifica se tem um previous location != NULL
  if(this->previousLocation == NULL){
      return 0;
  }
  
 float cx0 = this->currentLocation.longitude;
 float cy0 = this->currentLocation.latitude;
 float cx1 = this->currentLocation.longitude;
 float cy1 = this->currentLocation.latitude;
 float tx0 = this->targetLocation.longitude;
 float ty0 = this->targetLocation.latitude;
 float tx1 = this->targetLocation.longitude;
 float ty1 = this->targetLocation.latitude;
  
float angleBetweenLines(float cx0, float cy0, float cx1, float cy1, float tx0, float ty0, float tx1, float ty1){
 	
	//pra uma reta ser paralela ao eixo y: valores de x precisam ser iguais 
	
float tg = 0;
	
	
		
	if(cx0 == cx1){
		float mt = (ty1-ty0)/(tx1-tx0);
		float tg = 1/mt;
		return 180/M_PI * atan(tg);
	}
    
  if (tx0 == tx1){
    float mc = (cy1-cy0)/(cx1-cx0);
    float tg = 1/mc;
    return 180/M_PI * atan(tg);	
	}

	if (cx0 != cx1 && tx0 != tx1){
 		float mc = (cy1-cy0)/(cx1-cx0);
		float mt = (ty1-ty0)/(tx1-tx0);
		float tg = ((mt - mc)/(1+mc*mt));	
		return 180/M_PI * atan(tg);
	}
}


  }     // Calculo do algulo usando: Posicao atual, posicao anterior e Alvo
  // Senao retorna 0
}

void GPS::testeGps(){
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
