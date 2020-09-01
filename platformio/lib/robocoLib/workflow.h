#ifndef WORKFLOW_H
#define WORKFLOW_H
#include <Arduino.h>
#include <stdio.h>
#include <SD.h>
#include <EEPROM.h>

struct Workstep{
  double latitude;
  double longitude;
  int collectCount; // contagem da coleta D3 ATE ACABAR O 5M
  int collectInterval; // in seconds intervalo da coleta D2 5M
  byte currentStopIndex; // indice de parada atual 
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
    void test();
};
#endif
