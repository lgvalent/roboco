#ifndef GPS_CPP
#define GPS_CPP
#include <Arduino.h>

struct Location{
    float latitude;
    float longitude;
    float altitude;
    float angle;
    unsigned long time;
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
    protected:
        virtual void setup()=0;
        virtual boolean readGps()=0;
     

        Location* targetLocation;
        Location* previousLocation;
        Location* currentLocation;
    public:
        virtual Location* getCurrentLocation()=0;
        virtual DataTimer* getCurrentDataTimer()=0;

        Location* getPreviousLocation();
        Location* getTargetLocation();

        void setTargetLocation(float latitude, float longitude);
        
        float getDistanceToTarget();
        float getAngleToTarget(Location* currentLocation);
};
#endif
