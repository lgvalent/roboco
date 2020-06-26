#ifndef GPS_NEO6M_CPP
#define GPS_NEO6M_CPP
#include <Arduino.h>
#include <gps.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>


class GpsNEO6M : public GPS
{
private:
    void setup();
    boolean readGps(); 
    TinyGPS* gps;

public:
    GpsNEO6M(int8_t pinRx, int8_t pinTx);
    GpsNEO6M(HardwareSerial *serial);
    Location *getCurrentLocation();
    DataTimer *getCurrentDataTimer();
    void testeGpsNEO6M();
};
#endif
