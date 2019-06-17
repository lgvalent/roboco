
/* Use these includes for Arduido IDE production */
#include <roboco.h>
#include <sensors.h>
#include <output.h>
#include <collectRegister.h>
#include <workflow.h>
#include <gps.h>
#include <motor.h>
#include <testing.h>
/**/

/* Use these includes for Linux/Windows development 
#include "robocoLib/roboco.h"
#include "robocoLib/testing.h"
#include "robocoLib/sensors.h"
#include "robocoLib/output.h"
#include "robocoLib/collectRegister.h"
#include "robocoLib/workflow.h"
#include "robocoLib/gps.h"
#include "robocoLib/motor.h"
/**/

Roboco* roboco;
Testing* testing;
void setup()
{
  Serial.begin(9600);

  /* Cria os sensores */
  Adafruit_BMP280* bmp280 = new Adafruit_BMP280();
  TemperatureSensor* tempSensor = new TemperatureSensor(bmp280);
  AltitudeSensor* altSensor = new AltitudeSensor(bmp280);
  PressureSensor* pressSensor = new PressureSensor(bmp280);

  Mhz19* mhzSensor = new Mhz19(10);

  Ldr* ldrSensor1 = new Ldr(A8);
   
  Sensors* sensors = new Sensors(Roboco::_COUNT);
  sensors->addSensor(Roboco::TEMPERATURE, tempSensor);
  sensors->addSensor(Roboco::ALTITUDE, altSensor);
  sensors->addSensor(Roboco::PRESSURE, pressSensor);
  sensors->addSensor(Roboco::CO2, mhzSensor);
  sensors->addSensor(Roboco::LUMINOSITY, ldrSensor1);

  Output* output = new Output(1,2,3);

  GPS* gps = new GPS(8,7);

  CollectRegister* collectRegister = new CollectRegister(1);

  Workflow* workflow = new Workflow(1);

  Motor* motorLeft = new Motor(2,4,3);
  Motor* motorRight = new Motor(5,6,9);
  
  if(digitalRead(12) == LOW){  // Define se o robô estará em modo normal ou de teste
    roboco = new Roboco(sensors, output, gps, collectRegister, workflow, motorLeft, motorRight);
    roboco->setup();
  }else{
    testing = new Testing(sensors, output, gps, collectRegister, workflow, motorLeft, motorRight);
    testing->setup(0);
  }
}
void loop(){

}
