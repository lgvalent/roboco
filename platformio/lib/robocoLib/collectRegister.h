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
    int cont = 1;

  public:
    CollectRegister(SDClass& sd);
	  void open(String collectName);
    void write(Location* location,DateTime* dateTime, Sensors* sensors);
  	void close();
    void test(); // pegamos os valores que estão sendo criados na mais, para não criar os hipotéticos
};
#endif


