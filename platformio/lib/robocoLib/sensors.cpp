#include <Arduino.h>
#include <sensors.h>

String Sensor::SENSOR_TYPE_NAMES[] = {"Luminosity", "Pressure","Altitude", "Temperature", "CO2" };

String Sensor::getTypeName(){
  return SENSOR_TYPE_NAMES[this->getType()];
}

boolean Sensor::calibrate(){
   return true;
}

Co2Sensor::Co2Sensor(int8_t pinRx, int8_t pinTx){

  SoftwareSerial *softwareSerial = new SoftwareSerial(pinRx, pinTx);
  softwareSerial->begin(9600);
  this->serial = softwareSerial;
  this->mhz19 = new MHZ19();
  mhz19->begin(*Co2Sensor::serial);
}

Sensor::SensorType Co2Sensor::getType(){
  return CO2;
}

String Co2Sensor ::read(){
  // Código de leitura Serial
  return String(this->mhz19->getCO2(false));
}; 
 
boolean Co2Sensor::calibrate(){
  // Código de calibração do sensor!! DUrará horas??? 
  this->mhz19->autoCalibration(false);
  return true;
}; 
 
LuminositySensor::LuminositySensor(int8_t pin){
  pinMode(pin, INPUT);
};

Sensor::SensorType LuminositySensor::getType(){
  return LUMINOSITY;
};

String LuminositySensor:: read(){
  return String(analogRead(this->pin));
};

boolean LuminositySensor::calibrate(){
  return true;
};

TemperatureSensor::TemperatureSensor(Adafruit_BMP280 *sensor){
  
  this->sensor = sensor;
};

Sensor::SensorType TemperatureSensor::getType(){
  return TEMPERATURE;
};

String TemperatureSensor::read(){
  return String(this->sensor->readTemperature());
};

boolean TemperatureSensor::calibrate(){
  return true;
};

PressureSensor::PressureSensor(Adafruit_BMP280 *sensor){

  this->sensor = sensor;
};

Sensor::SensorType PressureSensor::getType(){
  return PRESSURE;
};

String PressureSensor::read(){
  return String(this->sensor->readPressure());
};

boolean PressureSensor::calibrate(){
  return true;
};

AltitudeSensor::AltitudeSensor(Adafruit_BMP280 *sensor){

  this->sensor = sensor;
};

Sensor::SensorType AltitudeSensor::getType(){
  return ALTITUDE;
};

String AltitudeSensor::read(){
  return String(this->sensor->readAltitude(1013.25));
}

boolean AltitudeSensor::calibrate(){
  return true;
};

Sensors::Sensors(int8_t maxNumberOfSensors) : size(maxNumberOfSensors){
  this->sensors = new Sensor *[maxNumberOfSensors];
}

int8_t Sensors::getSize(){
  return this->size;
};

void Sensors::addSensor(int index, Sensor *sensor){
  this->sensors[index] = sensor;
};

Sensor *Sensors::getSensor(int index){
  return this->sensors[index];
};

void Sensors::test(){

  Serial.println("Testing Sensors...");
  for (int index = 0; index < 5; index++){
    Sensor *sensor = this->getSensor(index);
    Serial.print(sensor->getTypeName());
    Serial.print(":");
   Serial.println(sensor->read());
  }
}

boolean Sensors::calibrate(){

  Serial.println("Calibrating Sensors...");
  for (int i = 0; i < this->getSize();i++){
    Sensor *sensor = this->getSensor(i);
    Serial.print(sensor->getTypeName());
    Serial.print(":");
    Serial.println(sensor->calibrate());
  }

  return true;
}