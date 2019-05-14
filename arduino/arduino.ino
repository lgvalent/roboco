
/* Use these includes for Arduido IDE production
#include <roboco.h>
#include <sensors.h>
#include <output.h>
#include <collectRegister.h>
#include <workflow.h>
#include <gps.h>
#include <motor.h>
/**/

/* Use these includes for Linux/Windows development */ 
#include "robocoLib/roboco.h"
#include "robocoLib/sensors.h"
#include "robocoLib/output.h"
#include "robocoLib/collectRegister.h"
#include "robocoLib/workflow.h"
#include "robocoLib/gps.h"
#include "robocoLib/motor.h"
/**/

Roboco* roboco;
void setup()
{
  Sensors* sensors = new Sensors(1,2,3);
  Output* output = new Output(1,2,3);
  GPS* gps = new GPS(1,2);
  CollectRegister* collectRegister = new CollectRegister(1);
  Workflow* workflow = new Workflow(1);
  Motor* motorLeft = new Motor(1,2,3);
  Motor* motorRight = new Motor(1,2,3);

  roboco = new Roboco(sensors, output, gps, collectRegister, workflow, motorLeft, motorRight);

  roboco->setup();
}
void loop() {
  roboco->run();
}



