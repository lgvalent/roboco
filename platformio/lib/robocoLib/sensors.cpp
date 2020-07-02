#include <Arduino.h>

#include <sensors.h>

String Sensor::SENSOR_TYPE_NAMES[] = {"Pressure", "Altitude", "Temperature", "Luminosity", "CO2"};

Sensors::Sensors(int8_t maxNumberOfSensors) : size(maxNumberOfSensors)
{
  this->sensors = new Sensor *[maxNumberOfSensors];
}

int8_t Sensors::getSize()
{
  return this->size;
};

void Sensors::addSensor(int index, Sensor *sensor)
{
  this->sensors[index] = sensor;
};

Sensor *Sensors::getSensor(int index)
{
  return this->sensors[index];
};

void Sensors::test()
{
  Serial.println("Testing Sensors...");
  for (int i = 0; i < this->getSize(); i++)
  {
    Sensor *sensor = this->getSensor(i);
    Serial.print(sensor->getTypeName());
    Serial.print(":");
    Serial.println(sensor->read());
  }
}
