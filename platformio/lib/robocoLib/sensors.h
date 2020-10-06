#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
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

enum SensorType{LUMINOSITY, PRESSURE, ALTITUDE, TEMPERATURE, CO2, COMPASS};

class Sensor{
  protected:
    static String SENSOR_TYPE_NAMES[];
  public:
    virtual SensorType getType() = 0;
    virtual String read() = 0;
    String getTypeName(); 
    boolean calibrate();
};

#include <MHZ19.h>
class Co2Sensor: public Sensor {

  private:
    Stream* serial;
    MHZ19* mhz19;

  public:
    Co2Sensor(int8_t pinRx, int8_t pinTx);
    Co2Sensor(HardwareSerial *serial);
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

#include <Adafruit_BMP280.h>
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

#include <QMC5883LCompass.h>
class CompassSensorQMC5883: public Sensor{
  
  private:
    QMC5883LCompass* sensor;

  public:
    CompassSensorQMC5883(QMC5883LCompass* sensor); 
    SensorType getType(); 
    String read(); 
    boolean calibrate();
};

#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
class CompassSensorHMC5883: public Sensor{
  
  private:
    Adafruit_HMC5883_Unified* sensor;

  public:
    CompassSensorHMC5883(Adafruit_HMC5883_Unified* sensor); 
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