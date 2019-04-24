#ifndef ROBOCO_H
#define ROBOCO_H
#include "sensors.h"
#include "output.h"
#include "collectRegister.h"
#include "workflow.h"
#include "gps.h"
#include "motor.h"

class Roboco{
  private:
    Sensors *sensors;
    Output *output;
    GPS *gps;
    CollectRegister *collectRegister;
    Worflow *workflow;
    Motor *motorLeft, *motorRight;
  
  public:
    Roboco(Sensors *sensors, Output *output, GPS *gps, CollectRegister *collectRegister, Worflow *workflow, Motor *left, Motor *right);

    void setup();

    void reset();

    void run();  
};
#endif
