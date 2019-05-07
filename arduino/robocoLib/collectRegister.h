#include <Arduino.h>
#include <stdio.h>
#include <SD.h>
#include "collectRegister.h"
#include "Sensor.h"
#include <SPI.h>

CollectRegister::CollectRegister(int8_t pinSD){
	this->pinSD = pinSD;
}

CollectRegister::open(){ 
	this->myFile = SD.open("result.txt", FILE_WRITE);
	myfile.println("Luminosity, Temperature, Altitude, AtmosphericPressure");
}

CollectRegister::write(Location* location, Sensors* sensors){
	this->location = location;
	this->sensors = sensors;
	if(myFile){
		myFile.print(Sensors.getLuminosity());
		myFile.print(',');
		myFile.print(Sensors.getTemperature());
		myFile.print(',');
		myFile.print(Sensors.getAltitude());
		myFile.print(',');
		myFile.print(Sensors.getAtmosphericPressure());
		myFile.print(',');
		myFile.print(Sensors.getCO2ppm());
		myFile.println(';');
	}	
}

CollectRegister::close(){
    myFile.close();
}
