#ifndef GPS_H
#define GPS_H
#include <Arduino.h>
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
};
#endif
