#ifndef COLLECT_REGISTER_H
#define COLLECT_REGISTER_H
#include <SD.h>
#include <SPI.h>
#include <gps.h>
#include <sensors.h>
#include <gpsNEO6M.h>

class CollectRegister{
  
  private:
    SDClass* sd;
	  File file;

  public:
    CollectRegister(SDClass& sd);
	  void open();
    void write(Location* location,DateTime* dateTime, Sensors* sensors);
  	void close();
    void test(Location* location, DateTime* dateTime, Sensors* sensors); // pegamos os valores que estão sendo criados na mais, para não criar os hipotéticos
};
#endif


