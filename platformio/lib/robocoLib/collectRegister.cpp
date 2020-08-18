
#include <collectRegister.h>

CollectRegister::CollectRegister(int8_t pinSD) {
	this->pinSD = pinSD;
}

void CollectRegister::open() {

	this->file = SD.open("result.txt", FILE_WRITE);

}

void CollectRegister::write(Location* location, DateTime* dateTime, Sensors* sensors) {

	if (file) {
		file.print("Longitude: ");
		file.println(location->longitude);
		file.print("Latitude: ");
		file.println(location->latitude);

		file.print("Date: ");
    	file.print(dateTime->day);
    	file.print("/");
    	file.print(dateTime->month);
    	file.print("/");
    	file.print(dateTime->year);
    	file.println(" ");
    	file.print("Time: ");
    	file.print(dateTime->hour);
    	file.print(":");
    	file.print(dateTime->minute);
    	file.print(":");
    	file.print(dateTime->seconds);
    	file.println();

		for (int i = 0; i < sensors->getSize(); i++) {
			file.print(sensors->getSensor(i)->getTypeName());
			file.print(", ");
		}
		file.println();

		for (int i = 0; i < sensors->getSize(); i++) {
			file.print(sensors->getSensor(i)->read());
			file.print(", ");
		}
		file.println();
	}
}

void CollectRegister::close() {
	file.close();
}


void CollectRegister::test() {

	Adafruit_BMP280* bmp = new Adafruit_BMP280(); 
  	bmp->begin(0x76); 
    LuminositySensor* Sensor = new LuminositySensor(A8);
    PressureSensor* Sensor2 = new PressureSensor(bmp);
	AltitudeSensor* Sensor3 = new AltitudeSensor(bmp);

  	Sensors* s = new Sensors(3);
  	s->addSensor(0, Sensor);
  	s->addSensor(1, Sensor2);
  	s->addSensor(2, Sensor3);

  	GPS* g = new GpsNEO6M(&Serial1);

	open();  // Abrir os regitrso 
	write(g->getCurrentLocation(), g->getCurrentDateTime() , s); // Gravar os valores virtuais
	close(); // Fechar o registro
}