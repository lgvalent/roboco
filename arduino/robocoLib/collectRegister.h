#ifndef COLLECT_REGISTER_H
#define COLLECT_REGISTER_H
#include <gps.h>
#include <sensors.h>

class CollectRegister{
  private:
  public:
    CollectRegister(/* Coloque os dados que precisam para configurar os armazenador de dados SDCARD pinos, seriais, etcs*/ );
	void open(char* fileName);
    void write(Location* location, Sensors* sensors);
	void close();
};
#endif
