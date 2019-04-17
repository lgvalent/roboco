#ifndef WORKFLOW_H
#define WORKFLOW_H
#include <Arduino.h>

byte currentStopIndex;

struct Workstep{
  float latitude;
  float longitude;
  int collectCount;
  int collectInterval; // in seconds
};

class Workflow{
  private:
  public:
    Workflow(/* Coloque os dados que precisam para configurar os pinos onde estão o SDCARD, seriais, etcs*/);
	Workstep* getNextStep();
};
#endif
