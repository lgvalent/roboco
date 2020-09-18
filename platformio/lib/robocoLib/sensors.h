#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <QMC5883LCompass.h>
#include <SoftwareSerial.h>
#include <MHZ19.h>

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
    static enum SensorType{LUMINOSITY, PRESSURE, ALTITUDE, TEMPERATURE, CO2, COMPASS} SENSOR_TYPE;
    static String SENSOR_TYPE_NAMES[];

  public:
    virtual SensorType getType() = 0;
    virtual String read() = 0;
    String getTypeName(); 
    boolean calibrate();
};

class Co2Sensor: public Sensor {

  private:
    Stream* serial;
    MHZ19* mhz19;

  public:
    Co2Sensor(int8_t pinRx, int8_t pinTx);
    SensorType getType();
    String read();
    boolean calibrate();
};

class LuminositySensor: public Sensor{

  private:
    int8_t pin;

  public:
    LuminositySensor(int8_t pin);
    SensorType getType();
    String read();
    boolean calibrate();
};

class TemperatureSensor: public Sensor{

  private:
    Adafruit_BMP280* sensor;

  public:
    TemperatureSensor(Adafruit_BMP280* sensor); 
    SensorType getType(); 
    String read();
    boolean calibrate();
};

class PressureSensor: public Sensor{

  private:
    Adafruit_BMP280* sensor;

  public:
    PressureSensor(Adafruit_BMP280* sensor); 
    SensorType getType();
    String read();
     boolean calibrate();
};

class AltitudeSensor: public Sensor{
  
  private:
    Adafruit_BMP280* sensor;

  public:
    AltitudeSensor(Adafruit_BMP280* sensor); 
    SensorType getType(); 
    String read(); 
    boolean calibrate();
};

class CompassSensor: public Sensor{
  
  private:
    QMC5883LCompass* sensor;

  public:
    CompassSensor(QMC5883LCompass* sensor); 
    SensorType getType(); 
    String read(); 
    boolean calibrate();
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
    boolean calibrate();
    void stabilizationOfSensors();  // estado de estabilização dos sensores PRECISA SER IMPLEMENTADO
};
#endif