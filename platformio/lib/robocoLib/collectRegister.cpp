#include <collectRegister.h>
#include <stdio.h>


CollectRegister::CollectRegister(SDClass& sd) {
	this->sd = &sd;
}

void CollectRegister::open(String collectName) {
	this->file = this->sd->open(collectName.c_str(), FILE_WRITE);
	if (this->file) { 									// Inicializa o SD Card (if temporário)
		Serial.println("O Arquivo pronto para uso."); 
	} else {
		Serial.println("Falha ao abrir o arquivo.");
		return;
	}
}

void CollectRegister::write(Location* location, DateTime* dateTime, Sensors* sensors) {

	file.print("------------------------------------------------------ ");
	file.println(this->cont++);

	if (file) { 
		file.print("Longitude: ");
		file.println(location->longitude, 6);
		file.print("Latitude: ");
		file.println(location->latitude, 6);

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
		file.println();

		for (int i = 0; i < (sensors->getSize()-1); i++) { 
			file.print(sensors->getSensor(i)->getTypeName());
			file.print(": ");
			file.print(sensors->getSensor(i)->read());
			file.println();
			Serial.print(sensors->getSensor(i)->getTypeName());
			Serial.print(": ");
			Serial.print(sensors->getSensor(i)->read());
			Serial.println( );
		}
		Serial.println( );
	 	file.println();

	}else{										 
		Serial.println("Erro ao Abrir Arquivo .txt"); 
	}

}

void CollectRegister::close() {
	this->file.close();
}

void CollectRegister::test() {
// pegamos os valores que estão sendo criados na maim, para não criar os virtuais

	Serial.println("Testing collectRegister...");

	//Criados valores virtuais para teste
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

	unsigned long start = millis();

	Location *loc = g->getCurrentLocation();
	DateTime *dat = g->getCurrentDateTime();
	open("result.txt"); 	
	write(loc, dat, s);
	close(); 										

	// Apartir daqui mostra no monitor o conteudo do arquivo
	file = SD.open("result.txt"); 					

	if (file){
		Serial.println("Conteúdo do Arquivo:");
		while (file.available()){ 						// Exibe o conteúdo do Arquivo
			Serial.write(file.read());
		}
		file.close(); 									// Fecha o Arquivo após ler
	} else{
		Serial.println("Erro ao Abrir Arquivo .txt"); 
	}

}