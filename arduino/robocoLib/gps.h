<<<<<<< HEAD
#ifndef SENSOR_CPP
#define SENSOR_CPP
#include <Arduino.h>
enum SensorDirection{
  CLOCKWISE_,
  ANTICLOCKWISE_ 
};

class Sensor{
  private:
    int8_t pin1;
    int8_t pin2;
    int8_t pinPwm;  
  public:
    Sensor(int8_t pin1, int8_t pin2, int8_t pinPwm);
    void stop();
    void move(SensorDirection direction,unsigned char speed);  
=======
#ifndef GPS_H
#define GPS_H
#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>


struct Location{
  float latitude;
  float longitude;
  float altitude;
  float angle;
};

class GPS{
  private:
    Adafruit_GPS* gps;
  public:
    GPS(HardwareSerial* serialPort);
    
    Location* getCurrentLocation();  
>>>>>>> 1b8ea424bf609793e34d3ea57c66622b5af47996
};
#endif
