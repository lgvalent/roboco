#ifndef GPS_CPP
#define GPS_CPP
#include <Arduino.h>
#include <Adafruit_GPS.h>

struct Location{
    float latitude;
    float longitude;
    float altitude;
    float angle;
};

struct DataTimer
{
    uint8_t hour;
    uint8_t minute;
    uint8_t seconds;
    uint8_t year;
    uint8_t month;
    uint8_t day;
};

class GPS{
    private:
        void setup();
        boolean readGps();
        Adafruit_GPS* gps;
    public:
        GPS(int8_t pinRx, int8_t pinTx);
        GPS(HardwareSerial* serial);    
        Location* getCurrentLocation();
        DataTimer* getCurrentDataTime();
};
#endif
