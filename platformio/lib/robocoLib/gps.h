#ifndef GPS_CPP
#define GPS_CPP
#include <Arduino.h>

struct Location{
    float latitude;
    float longitude;
    float altitude;
    float angle;
    unsigned long time;

    void copyFrom(Location * location){
        latitude = location->latitude;
        longitude = location->longitude;
        altitude = location->altitude;
        angle = location->angle;
        time = location->time; 
    }
};

struct DateTime
{
    uint8_t hour;
    uint8_t minute;
    uint8_t seconds;
    uint16_t year;
    uint8_t month;
    uint8_t day;
};

class GPS{

    protected:
        virtual void setup()=0;
        virtual boolean readGps()=0;     
        Location* targetLocation = new Location();
        Location* previousLocation = new Location();
        Location* currentLocation = new Location();
        DateTime* currentDateTime = new DateTime();

    public:
        virtual Location* getCurrentLocation()=0;
        virtual DateTime* getCurrentDateTime()=0;
        Location* getPreviousLocation();
        Location* getTargetLocation();
        void setTargetLocation(float latitude, float longitude);
        float getDistanceToTarget();
        float getAngleToTarget(Location* currentLocation);
        void test();
};
#endif
