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

Roboco* roboco;
GPS* gps;



void setup(){

  Serial.begin(9600);
  Serial.println("Starting...\n");

  /*/* Cria os sensores */
  Adafruit_BMP280* bmp280 = new Adafruit_BMP280(); // no Arduino Mega 2560 os pinos de conexão I2C do BMP280 serão o 20 (SDA) e o 21 (SCL).
  bmp280->begin(0x76); // necessario inicializar o bmp280
  LuminositySensor* ldrSensor = new LuminositySensor(A8);
  PressureSensor* pressSensor = new PressureSensor(bmp280);
  AltitudeSensor* altSensor = new AltitudeSensor(bmp280);
  Co2Sensor* myMHZ19 = new Co2Sensor(10, 11);
  TemperatureSensor* tempSensor = new TemperatureSensor(bmp280);

  Sensors* sensors = new Sensors(Roboco::_COUNT);
  sensors->addSensor(Roboco::LUMINOSITY, ldrSensor);
  sensors->addSensor(Roboco::PRESSURE, pressSensor);
  sensors->addSensor(Roboco::ALTITUDE, altSensor);
  sensors->addSensor(Roboco::CO2, myMHZ19); 
  sensors->addSensor(Roboco::TEMPERATURE, tempSensor);

  Output* output = new Output(1,2,3);

  // gps = new GpsMTK33x9(8,7);
  gps = new GpsNEO6M(&Serial1); // pins 18tx e 19rx

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
