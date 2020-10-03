#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
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
CollectRegister* collectRegister;
Sensors* sensors;

void setup(){

  Serial.begin(9600);
  Serial.println("Starting...\n");

  // Cria os sensores
  Adafruit_BMP280* bmp280 = new Adafruit_BMP280();  // no Arduino Mega 2560 os pinos de conexão I2C do BMP280 serão o 20 (SDA) e o 21 (SCL).
  bmp280->begin(0x76);                              // necessario inicializar o bmp280
  QMC5883LCompass* c = new QMC5883LCompass();
  CompassSensorQMC5883* compass = new CompassSensorQMC5883(c);
  // Adafruit_HMC5883_Unified* c = new Adafruit_HMC5883_Unified(12345);
  // CompassSensorHMC5883* compass = new CompassSensorHMC5883(c);

  LuminositySensor* ldrSensor = new LuminositySensor(A8);
  PressureSensor* pressSensor = new PressureSensor(bmp280);
  AltitudeSensor* altSensor = new AltitudeSensor(bmp280);
  //Co2Sensor* myMHZ19 = new Co2Sensor(0,1);     // OBS 1: esta dando conflito nos poinos com o módulo shield v1r3 (SD card). Se for testar o SD comente o sensor co2
  TemperatureSensor* tempSensor = new TemperatureSensor(bmp280);

  sensors = new Sensors(Roboco::_COUNT);
  sensors->addSensor(Roboco::LUMINOSITY, ldrSensor);
  sensors->addSensor(Roboco::PRESSURE, pressSensor);
  sensors->addSensor(Roboco::ALTITUDE, altSensor);
  //sensors->addSensor(Roboco::CO2, myMHZ19); 
  sensors->addSensor(Roboco::TEMPERATURE, tempSensor);
  sensors->addSensor(Roboco::COMPASS, compass);

  Output* output = new Output(1,2,3);

  // gps = new GpsMTK33x9(8,7);
  gps = new GpsNEO6M(&Serial1);  
  // gps->setCompassSensor(compass);
   
  // Prepare SD Card, pinSD is a select SPI pin, MEGA: 50,51,52 and 53, 
  pinMode(53, OUTPUT);
  SD.begin(53);

  CollectRegister* collectRegister = new CollectRegister(SD); // para arduino uno use o pin10

  Workflow* workflow = new Workflow(SD);                      // para arduino uno use o pin10

  Motor* motorLeft = new Motor(5,6,3);
  Motor* motorRight = new Motor(8,9,3);

  roboco = new Roboco(sensors, output, gps, collectRegister, workflow, motorLeft, motorRight);
  //roboco->setup(); // OBS 2: Setup comentado pq quando testamos o sd com ele, da problema.
  workflow->reset();
}

void loop(){
  //roboco->run(); 
}