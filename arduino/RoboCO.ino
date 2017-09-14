#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

SoftwareSerial GpsSerial(8, 7);
SoftwareSerial SensorSerial(12, 13);
Adafruit_GPS GPS(&GpsSerial);
void setup() {
  Serial.begin(115200);
  GPS.begin(9600);
  SensorSerial.begin(9600);
  
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  
  // taxa de atualização
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz taxa de atualização
  // atualizando antena quando nao esta fazendo leitura
  GPS.sendCommand(PGCMD_ANTENNA);
  
  useInterrupt(true);

  delay(1000);
  TesteSensor();
}

void loop() {
  // put your main code here, to run repeatedly:
  GpsDados();
  delay(2000);
  Serial.println("---------------");
  Serial.print("Location (in degrees, works with Google Maps): ");
  Serial.print(GPS.latitudeDegrees, 4);
  Serial.print(", "); 
  Serial.println(GPS.longitudeDegrees, 4);
  Serial.println("--------------------------");
  delay(3000);
  Sensor();
}
