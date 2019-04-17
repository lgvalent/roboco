#ifndef COLLECT_REGISTER_H
#define COLLECT_REGISTER_H
#include <gps.h>
#include "sensor.h"

class CollectRegister{
  private:
  public:
    CollectRegister(int8_t pinSD);
	void open(char* fileName);
    void write(Location* location, Sensors* sensors);
	void close();
};
#endif
