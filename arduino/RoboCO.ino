
//Bibliotecas Gerais
#include <SoftwareSerial.h>
#include <SPI.h>
#include<EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Bibliotecas GPS
#include <Adafruit_GPS.h>
//Biblioteca SD
#include <SD.h>
//Biblioteca MOTOR
#include <Dumotor.h>
//Biblioteca sensores
#include <Adafruit_Sensor.h> //co2
#include <Adafruit_BMP280.h> //temperatura

Adafruit_BMP280 bmp; // I2C
Dumotor motor; //inciando motores

//INICIALIZANDO COMPONENTES
// GPS
SoftwareSerial mySerial(12, 13); // RX, TX, MHZ_19
Adafruit_GPS GPS(&Serial3);
LiquidCrystal_I2C lcd(0x27, 16, 2);// Inicializa o display no endereco 0x27 (16X2);


/// VARIAVEIS DO SKETCH SD
float latitude;
float longitude;
long int tempoEsvaziamentoCamara;
long int intervaloEntreCapturas;
long int intervaloAjustePosicionamento;
long int tempoCaptura;
File printFile;
File arquivoTXT;
String buffer;
boolean SDfound;
int linhaAtual=0;


/// VARIAVEIS DO GPS
float latitudeAtual;
float longitudeAtual;
float angulo;
float Altitude;
boolean fix;
float distancia;
float distanciaAnterior;

/// VARIAVEIS DE DADOS;
int co2;
float temperatura;
float pressao;


///VARIAVEIS DE LEITURA
long tempoEsvaziamentoCamaraMilly;
long intervaloEntreCapturasMilly;
long intervaloAjustePosicionamentoMilly;
long tempoCapturaMilly;
unsigned long tempoEsvaziamentoCamaraAnterior;
unsigned long intervaloEntreCapturasAnterior;
unsigned long intervaloAjustePosicionamentoAnterior;
unsigned long tempoCapturaAnterior;
unsigned long tempoMillis = millis();
unsigned long tempoAnterior;
int linhaFinal=0;

/// PINOS DOS LEDS
int ledBranco = 38;
int ledBranco1 = 34;
int ledBranco2 = 36;
int ledVerde = 32;
int ledVerde1 = 40;
int ledVerde2 = 44;
int ledVermelho = 46;
int ledVermelho1 = 48;
int ledVermelho2 = 50;

//VARIAVEIS DE DESLOCAMENTO
int velocidade=0;


void setup() {
  // SETANDO OS PINOS DOS LED COMO SAIDA
  pinMode(ledBranco, OUTPUT);
  pinMode(ledBranco1, OUTPUT);
  pinMode(ledBranco2, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVerde1, OUTPUT);
  pinMode(ledVerde2, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVermelho1, OUTPUT);
  pinMode(ledVermelho2, OUTPUT);
  pinMode(A5,OUTPUT); //Pino do buzzer

  Serial.begin(115200); // INICIANDO MONITOR SERIAL
  GPS.begin(9600); //INICIANDO COMUNICAÇÃO SERIAL DO GPS
  mySerial.begin(9600);// INICIANDO COMUNICAÇÃO SERIAL DO SENSOR DE CO2
  lcd.begin (16, 2); // INFORMANDO QUE O LCD E 16X2
  lcd.init(); // INICIANDO LCD
  lcd.init(); // INICIANDO LCD
  lcd.setBacklight(LOW); // APAGANDO LUZ LCD
  delay(2000);
  lcd.setBacklight(HIGH); // ACENDENDO LUZ LCD  
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // COLOCANDO PARAMETRO EM ALGUMAS VARIAVEZ DO GPS
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz taxa de atualização
  GPS.sendCommand(PGCMD_ANTENNA);// atualizando antena quando nao esta fazendo leitura
  useInterrupt(true);
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
  }
  teste();
  distanciaAoPonto();
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
  apresentacao();
}


