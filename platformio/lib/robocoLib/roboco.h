#ifndef ROBOCO_H
#define ROBOCO_H
#include <collectRegister.h>
#include <gps.h>
#include <motor.h>
#include <output.h>
#include <sensors.h>
#include <workflow.h>

class Roboco{

  public: 
    const int TARGET_SOFT_APPROACH_METER = 3;
    const float TARGET_MINIMAL_DISTANCE_APPROACH_FACTOR = 0.1;
    enum RobocoStates{READING_NEXT_STEP, READING_CURRENT_LOCATION, KEEPING_TRACK, READING_SENSORS};

  private:
    Sensors* sensors;
    Output* output;
    GPS* gps;
    CollectRegister* collectRegister;
    Workflow* workflow;
    Motor* motorLeft,* motorRight;
    Workstep* currentStep;
    Location* currentLocation;

  
  public:
    static enum RobocoSensors{LUMINOSITY=0, PRESSURE, ALTITUDE, HUMIDITY, TEMPERATURE, CO2, _COUNT} ROBOCO_SENSORS;
    Roboco(Sensors* sensors, Output* output, GPS* gps, CollectRegister* collectRegister, Workflow* workflow, Motor* left, Motor* right);
    void setup();
    void reset();
    void run();  
    void test();
};
#endif