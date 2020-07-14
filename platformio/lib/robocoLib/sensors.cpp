#include <Arduino.h>
#include <sensors.h>

String Sensor::SENSOR_TYPE_NAMES[] = {"Pressure", "Altitude", "Temperature", "Luminosity", "CO2"};

String Sensor::getTypeName(){
   SENSOR_TYPE_NAMES[this->getType()];
}

boolean Sensor::calibrate(){
   return true;
}

Mhz19::Mhz19(Stream *serial){
  this->serial = serial;
}


String Mhz19 ::read(){
  // Código de leitura via PWM ou Serial??? 
  return String(0);
}; 
 
boolean Mhz19::calibrate(){
  // Código de calibração do sensor!! DUrará horas??? 
  return true;
}; 
 
Sensor::SensorType Mhz19::getType(){
  return CO2;
};

Ldr::Ldr(int8_t pin){
  pinMode(pin, INPUT);
};

String Ldr:: read(){
  return String(analogRead(this->pin));
};

Sensor::SensorType Ldr::getType(){
  return LUMINOSITY;
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

PressureSensor::PressureSensor(Adafruit_BMP280 *sensor){
  this->sensor = sensor;
};

Sensor::SensorType PressureSensor::getType(){
  return PRESSURE;
};

String PressureSensor::read(){
  return String(this->sensor->readPressure());
};

AltitudeSensor::AltitudeSensor(Adafruit_BMP280 *sensor){
  this->sensor = sensor;
};

Sensor::SensorType AltitudeSensor::getType(){
  return ALTITUDE;
};

String AltitudeSensor::read(){
  return String(this->sensor->readAltitude());
}

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
  for (int i = 0; i < this->getSize(); i++){
    Sensor *sensor = this->getSensor(i);
    Serial.print(sensor->getTypeName());
    Serial.print(":");
    Serial.println(sensor->read());
  }
}

boolean Sensors::calibrate(){

  Serial.println("Calibrating Sensors...");
  for (int i = 0; i < this->getSize(); i++){
    Sensor *sensor = this->getSensor(i);
    Serial.print(sensor->getTypeName());
    Serial.print(":");
    Serial.println(sensor->calibrate());
  }
}