#include <collectRegister.h>

CollectRegister::CollectRegister(int8_t pinSD) {
	this->pinSD = pinSD;
	pinMode(pinSD, OUTPUT);
		if (SD.begin()) { 							// Inicializa o SD Card (if temporário)
		Serial.println("SD Card pronto para uso."); 
		} else {
		Serial.println("Falha na inicialização do SD Card.");
		return;
		}
}

void CollectRegister::open() {
	this->file = SD.open("result.txt", FILE_WRITE); 
}

void CollectRegister::write(Location* location, DateTime* dateTime, Sensors* sensors) {
	
	if (file) {
		Serial.println("Passei por aqui 2.1"); 
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
	} else {										  // Se o Arquivo não abrir
		Serial.println("Erro ao Abrir Arquivo .txt"); 
	}
}

void CollectRegister::close() {
	file.close();
}

void CollectRegister::test(Location* location, DateTime* dateTime, Sensors* sensors) {
// pegamos os valores que estão sendo criados na mais, para não criar os virtuais

Serial.println("Testing collectRegister...");

	/* Criados valores virtuais para teste, usados anteriormente mas sem sucesso

	Adafruit_BMP280* bmp = new Adafruit_BMP280(); 
  	bmp->begin(0x76); 
    LuminositySensor* Sensor = new LuminositySensor(A8);
    PressureSensor* Sensor2 = new PressureSensor(bmp);
	AltitudeSensor* Sensor3 = new AltitudeSensor(bmp);

  	Sensors* s = new Sensors(3);
  	s->addSensor(0, Sensor);
  	s->addSensor(1, Sensor2);
  	s->addSensor(2, Sensor3);

  	GPS* g = new GpsNEO6M(&Serial1);*/

	open();  								// Abrir os regitrso 
	write(location, dateTime, sensors); 
	close(); 								// Fechar o registro

	file = SD.open("result.txt"); 			// Abre o Arquivo

	if (file){
		Serial.println("Conteúdo do Arquivo:"); 
		while (file.available()){ 			// Exibe o conteúdo do Arquivo
			Serial.write(file.read());
		}
		file.close(); 						// Fecha o Arquivo após ler

	} else {
		Serial.println("Erro ao Abrir Arquivo .txt"); // Imprime na tela
	}
}