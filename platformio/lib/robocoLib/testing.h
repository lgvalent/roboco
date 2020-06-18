#ifndef TESTING_H
#define TESTING_H

#include <collectRegister.h>
#include <gps.h>
#include <motor.h>
#include <output.h>
#include <sensors.h>
#include <workflow.h>

class Testing
{
private:
    Sensors* sensors;
    Output* output;
    GPS* gps;
    CollectRegister* collectRegister;
    Workflow* workflow;
    Motor* motorLeft,* motorRight;
    Testing* testing;
public:
    Testing(Sensors* sensors, Output* output, GPS* gps, CollectRegister* collectRegister, Workflow* workflow, Motor* left, Motor* right);
    void setup(unsigned char teste);
    void testMotor();
    void testSensors();
    void testGps();
    void apresentacao(); // metodo para o robo ficar bobo.
};








#endif
