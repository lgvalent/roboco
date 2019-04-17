#include <Arduino.h>
#include <stdio.h>
#include <SD.h>
#include "collectRegister.h"
#include "Sensor.h"
#include <SPI.h>

CollectRegister::CollectRegister(int8_t pinSD){
	this->pinSD = pinSD;
}

CollectRegister::open(char* fileName){ 
	
	fileName = SD.open("result.txt", FILE_WRITE);
}

CollectRegister::write(Location* location, Sensors* sensors){
	this->location = location;
	this->sensors = sensors;
	myFile.println(Sensors.getLuminosity());
	myFile.println(',');
	myFile.println(Sensors.getTemperature());
	myFile.println(',');
	myFile.println(Sensors.getAltitude());
	myFile.println(',');
	myFile.println(Sensors.getAtmosphericPressure());
	myFile.println(',');
	myFile.println(Sensors.getCO2ppm());
	myFile.println(';');
}
CollectRegister::close(){
    myFile.close();
}
	

