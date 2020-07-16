#ifndef GPS_NEO6M_CPP
#define GPS_NEO6M_CPP
#include <Arduino.h>
#include <gps.h>
// #include <TinyGPS.h>
#include <Stream.h>
#include <TinyGPS++.h>

class GpsNEO6M : public GPS{

    protected:
        void setup();
        boolean readGps(); 
        void begin(int32_t baud);
        TinyGPSPlus* gps;

    private:
        Stream *serial;
        
    public:
        GpsNEO6M(int8_t pinRx, int8_t pinTx);
        GpsNEO6M(HardwareSerial *serial);
        Location *getCurrentLocation();
        DataTimer *getCurrentDataTimer();
        //void testeGpsNEO6M();
};
#endif