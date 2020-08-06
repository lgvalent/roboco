#ifndef GPS_CPP
#define GPS_CPP
#include <Arduino.h>

struct Location{
    double latitude;
    double longitude;
    float altitude;
    float angle;
    unsigned long time;
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
        Location* targetLocation = new Location();
        Location* previousLocation = new Location();
        Location* currentLocation = new Location();
        DateTime* currentDateTime = new DateTime();

    public:
        virtual boolean readGps()=0;     
        virtual Location* getCurrentLocation()=0;
        virtual DateTime* getCurrentDateTime()=0;
        Location* getPreviousLocation();
        Location* getTargetLocation();
        void setTargetLocation(float latitude, float longitude);
        float getDistanceToTarget();
        float getAngleToTarget();
        boolean test();
};
#endif
