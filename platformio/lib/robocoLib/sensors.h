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
    virtual String read() = 0;
    String getTypeName(); 
};

class Mhz19: public Sensor {

  private:
    int8_t pwmPin;
    Stream* serial;

  public:
<<<<<<< HEAD
    Mhz19(Stream *serial);
    Mhz19(int8_t pwmPin); 
    String read();
    SensorType getType();
=======
  Mhz19(Stream *serial){this->serial = serial;};
  Mhz19(int8_t pwmPin){this->pwmPin = pwmPin;};
  String read(){
    // Código de leitura via PWM ou Serial???
    return String(0);
  };
  SensorType getType(){return CO2;};
>>>>>>> bda4bd7ff543a7595e44b19e3e7806a53f485e6a
};

class Ldr: public Sensor{

  private:
    int8_t pin;

  public:
    Ldr(int8_t pin);
    SensorType getType();
    String read();
};

class TemperatureSensor: public Sensor{

  private:
    Adafruit_BMP280* sensor;

  public:
    TemperatureSensor(Adafruit_BMP280* sensor); 
    SensorType getType(); 
    String read();
};

class PressureSensor: public Sensor{

  private:
    Adafruit_BMP280* sensor;

  public:
    PressureSensor(Adafruit_BMP280* sensor); 
    SensorType getType();
    String read();
};

class AltitudeSensor: public Sensor{
  
  private:
    Adafruit_BMP280* sensor;

  public:
    AltitudeSensor(Adafruit_BMP280* sensor); 
    SensorType getType(); 
    String read(); 
};

class Sensors{

  private:
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