#ifdef GPS_CPP
#define GPS_CPP
#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

class GPS
{
    private:
        SoftwareSerial mySerial(8, 7);
        Adafruit_GPS* gps(&mySerial);
        boolean usingInterrupt = false;  
        
    public:
        void useInterrupt(boolean v); // Func prototype keeps Arduino 0023 happy
        void testeGps();
};

#endif