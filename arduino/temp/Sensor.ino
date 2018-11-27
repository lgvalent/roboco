#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10
//mh_z19
byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
char response[9]; 
int prevVal = LOW;
long th, tl, h, l, ppm, tpwm, p1, p2, ppm3 = 0.0;
long offset = 45.0;
//mh_z19
Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
  
 
void TesteSensor(){
  
  Serial.println(F("BMP280 test"));  
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
}
    
void Sensor() {
    //mh_z19
    SensorSerial.write(cmd,9);
    SensorSerial.readBytes(response, 9);
    int responseHigh = (int) response[2];
    int responseLow = (int) response[3];
    //ppm = (256*responseHigh)+responseLow;
    ppm = ((256*responseHigh)+responseLow)+offset;
    Serial.println("-----------");
    Serial.print(F("CO2 = "));
    Serial.print(ppm);
    Serial.println(" ppm");
    Serial.println("-----------");
    //mh_z19
    
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
    Serial.println(" m");
    Serial.println("-----------");
}
