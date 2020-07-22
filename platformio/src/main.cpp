#include <Arduino.h>
#include <SD.h>
/* Use these includes for Arduido IDE production */
#include <roboco.h>
#include <sensors.h>
#include <output.h>
#include <collectRegister.h>
#include <workflow.h>
#include <gps.h>
#include <motor.h>
#include <gpsMTK33x9.h>
#include <gpsNEO6M.h>

/**/

Roboco* roboco;
GPS* gps;

void setup(){

  Serial.begin(115200);
  Serial.println("Starting...\n");

  /* Cria os sensores */
  Adafruit_BMP280* bmp280 = new Adafruit_BMP280();
  TemperatureSensor* tempSensor = new TemperatureSensor(bmp280);
  AltitudeSensor* altSensor = new AltitudeSensor(bmp280);
  PressureSensor* pressSensor = new PressureSensor(bmp280);
  Co2Sensor* mhzSensor = new Co2Sensor(12, 13); 
  LuminositySensor* ldrSensor = new LuminositySensor(A8);

  Sensors* sensors = new Sensors(Roboco::_COUNT);
  sensors->addSensor(Roboco::TEMPERATURE, tempSensor);
  sensors->addSensor(Roboco::ALTITUDE, altSensor);
  sensors->addSensor(Roboco::PRESSURE, pressSensor);
  sensors->addSensor(Roboco::CO2, mhzSensor); 
  sensors->addSensor(Roboco::LUMINOSITY, ldrSensor);

  Output* output = new Output(1,2,3);

  // gps = new GpsMTK33x9(8,7);
  gps = new GpsNEO6M(10,11);

  CollectRegister* collectRegister = new CollectRegister(1);

  Workflow* workflow = new Workflow(1);

  Motor* motorLeft = new Motor(2,4,3);
  Motor* motorRight = new Motor(5,6,9);

  roboco = new Roboco(sensors, output, gps, collectRegister, workflow, motorLeft, motorRight);
  roboco->setup();
}

void loop(){
  // if(digitalRead(12) == LOW && false){  // Define se o robô estará em modo normal ou de teste
 // roboco->run();
  roboco->test();
}
