
#include <collectRegister.h>
#include <gps.h>

CollectRegister::CollectRegister(int8_t pinSD){
	this->pinSD = pinSD;
}

void CollectRegister::open(Sensors* sensors){ 
	this->file = SD.open("result.txt", FILE_WRITE);
	
	file.print("Longitude, Latitude, ");

	for(int i = 0; i < sensors->getSize(); i++){
		file.print(sensors->getSensor(i)->getTypeName());
		file.print(", ");
	}
	file.println();
}

void CollectRegister::write(Location* location, Sensors* sensors){
	if(file){
		file.print(location->longitude); file.print(", ");
		file.print(location->latitude); file.print(", ");

		for(int i = 0; i < sensors->getSize(); i++){
			file.print(sensors->getSensor(i)->read());
			file.print(", ");
		}
		file.println();
	}	
}

void CollectRegister::close(){
    file.close();
}

void CollectRegister::test(){
    // TODO Testar se o coletor registra os dados no SD card
}
