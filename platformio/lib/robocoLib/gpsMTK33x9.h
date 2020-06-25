#ifndef GPS_MTK33x9_CPP
#define GPS_MTK33x9_CPP
#include <Arduino.h>
#include <gps.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

class GpsMTK33x9 : public GPS
{
private:
    void setup();
    boolean readGps();
    Adafruit_GPS* gps;

public:
    GpsMTK33x9(int8_t pinRx, int8_t pinTx);
    GpsMTK33x9(HardwareSerial *serial);
    Location *getCurrentLocation();
    DataTimer *getCurrentDataTimer();
};
#endif
