#ifndef ROBOCO_H
#define ROBOCO_H

#include <collectRegister.h>
#include <gps.h>
#include <motor.h>
#include <output.h>
#include <sensors.h>
#include <workflow.h>
#include <testing.h>

class Roboco{
  private:
    Sensors* sensors;
    Output* output;
    GPS* gps;
    CollectRegister* collectRegister;
    Workflow* workflow;
    Motor* motorLeft,* motorRight;
    Testing* testing;
  
  public:
    static enum RobocoSensors{LUMINOSITY=0, PRESSURE, ALTITUDE, HUMIDITY, TEMPERATURE, CO2, _COUNT} ROBOCO_SENSORS;

    Roboco(Sensors* sensors, Output* output, GPS* gps, CollectRegister* collectRegister, Workflow* workflow, Motor* left, Motor* right);

    void setup();

    void reset();

    void run();  
};
#endif
