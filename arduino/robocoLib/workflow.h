#ifndef WORKFLOW_H
#define WORKFLOW_H
#include <Arduino.h>

struct Workstep{
  float latitude;
  float longitude;
  int collectCount;
  int collectInterval; // in seconds
  byte currentStopIndex;
};

class Workflow{
  private:
      int8_t pinSD;
      byte currentStepIndex;

  public:
    Workflow(int8_t pinSD);
	  Workstep* getNextStep();
	  void backOneStep();
    void reset();
};
#endif
