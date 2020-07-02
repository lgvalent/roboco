#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

class Unit{
  public:
    String description;
};

class SensorValue{
  public:
    float value;
    Unit unit;
};

class Sensor{
  protected:
    static enum SensorType{PRESSURE=0, ALTITUDE, TEMPERATURE, LUMINOSITY, CO2} SENSOR_TYPE;
    static String SENSOR_TYPE_NAMES[];
  public:
    virtual SensorType getType() = 0;
    
    String getTypeName(){return Sensor::SENSOR_TYPE_NAMES[this->getType()];};
    
    virtual String read() = 0;
    // virtual SensorValue readValue() = 0;
};

class Mhz19: public Sensor {
  int8_t pwmPin;
  Stream* serial;
  public:
  Mhz19(Stream *serial){this->serial = serial;};
  Mhz19(int8_t pwmPin){this->pwmPin = pwmPin;};
  String read(){
    // Código de leitura via PWM ou Serial???
    return String(0);
  };
  SensorType getType(){return CO2;};
};

class Ldr: public Sensor{
  int8_t pin;
  public:
    Ldr(int8_t pin){
      pinMode(pin, INPUT);
      this->pin = pin;
    };
    SensorType getType(){return LUMINOSITY;};
    
    String read(){
      return String(analogRead(this->pin));
    };
};

class TemperatureSensor: public Sensor{
  Adafruit_BMP280* sensor;
  public:
    TemperatureSensor(Adafruit_BMP280* sensor){this->sensor = sensor;};
    SensorType getType(){return TEMPERATURE;};

    String read(){ 
      return String(this->sensor->readTemperature());
    };
};

class PressureSensor: public Sensor{
    Adafruit_BMP280* sensor;
  public:
    PressureSensor(Adafruit_BMP280* sensor){this->sensor = sensor;};
    SensorType getType(){return PRESSURE;};
    
    String read(){ 
      return String(this->sensor->readPressure());
    };
};

class AltitudeSensor: public Sensor{
    Adafruit_BMP280* sensor;
  public:
    AltitudeSensor(Adafruit_BMP280* sensor){this->sensor = sensor;};
    SensorType getType(){return ALTITUDE;};
    
    String read(){ 
      return String(this->sensor->readAltitude());
    };
};

class Sensors{
  Sensor** sensors;
  int8_t size;
  public:
    Sensors(int8_t maxNumberOfSensors);
    int8_t getSize();
    void addSensor(int index, Sensor* sensor);
    Sensor* getSensor(int index);
    void test();
};
#endif
