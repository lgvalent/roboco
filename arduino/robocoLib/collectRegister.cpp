
#include <collectRegister.h>
#include <gps.h>

CollectRegister::CollectRegister(int8_t pinSD){
	this->pinSD = pinSD;
}

void CollectRegister::open(){ 
	this->file = SD.open("result.txt", FILE_WRITE);
	file.println("Luminosity, Temperature, Altitude, AtmosphericPressure");
}

void CollectRegister::write(Location* location, Sensors* sensors){
	if(file){
		file.print(sensors->getLuminosity());
		file.print(',');
		file.print(sensors->getTemperatureC());
		file.print(',');
		file.print(sensors->getAltitude());
		file.print(',');
		file.print(sensors->getAtmosphericPressure());
		file.print(',');
		file.print(sensors->getCO2ppm());
		file.println(';');
	}	
}

void CollectRegister::close(){
    file.close();
}
