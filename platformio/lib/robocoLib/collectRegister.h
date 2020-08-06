#ifndef COLLECT_REGISTER_H
#define COLLECT_REGISTER_H
#include <SD.h>
#include <gps.h>
#include <sensors.h>
#include <gpsNEO6M.h>

class CollectRegister{
  
  private:
    int8_t pinSD;
	  File file;
    
  public:
    CollectRegister(int8_t pinSD);
	  void open();
    void write(Location* location,DateTime* dateTime, Sensors* sensors);
  	void close();
    void test();
};
#endif


