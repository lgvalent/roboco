#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>

class Unit{
  public:
    String description;
};

class SensorValue{
  public:
    float value;
    Unit unit;
};

enum SensorType{LUMINOSITY, PRESSURE, ALTITUDE, TEMPERATURE, CO2, CH4, COMPASS};

class Sensor{
  protected:
    static String SENSOR_TYPE_NAMES[];
  public:
    virtual SensorType getType() = 0;
    virtual String read() = 0;
    String getTypeName(); 
    boolean calibrate();
};

#include <MHZ19.h>
class Co2Sensor: public Sensor {

  private:
    Stream* serial;
    MHZ19* mhz19;

  public:
    Co2Sensor(int8_t pinRx, int8_t pinTx);
    Co2Sensor(HardwareSerial *serial);
    SensorType getType();
    String read();
    boolean calibrate();
};

class LuminositySensor: public Sensor{

  private:
    int8_t pin;

  public:
    LuminositySensor(int8_t pin);
    SensorType getType();
    String read();
    boolean calibrate();
};

#include <Adafruit_BMP280.h>
class TemperatureSensor: public Sensor{

  private:
    Adafruit_BMP280* sensor;

  public:
    TemperatureSensor(Adafruit_BMP280* sensor); 
    SensorType getType(); 
    String read();
    boolean calibrate();
};

class PressureSensor: public Sensor{

  private:
    Adafruit_BMP280* sensor;

  public:
    PressureSensor(Adafruit_BMP280* sensor); 
    SensorType getType();
    String read();
     boolean calibrate();
};

class AltitudeSensor: public Sensor{
  
  private:
    Adafruit_BMP280* sensor;

  public:
    AltitudeSensor(Adafruit_BMP280* sensor); 
    SensorType getType(); 
    String read(); 
    boolean calibrate();
};

#include <QMC5883LCompass.h>
class CompassSensorQMC5883: public Sensor{
  
  private:
    QMC5883LCompass* sensor;

  public:
    CompassSensorQMC5883(QMC5883LCompass* sensor); 
    SensorType getType(); 
    String read(); 
    boolean calibrate();
};

#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
class CompassSensorHMC5883: public Sensor{
  
  private:
    Adafruit_HMC5883_Unified* sensor;

  public:
    CompassSensorHMC5883(Adafruit_HMC5883_Unified* sensor); 
    SensorType getType(); 
    String read(); 
    boolean calibrate();
};

/* MQ2 ===========================================================================
   SOURCE: https://create.arduino.cc/projecthub/Junezriyaz/how-to-connect-mq2-gas-sensor-to-arduino-f6a456
           https://jualabs.wordpress.com/2016/11/30/sensoriamento-de-gases-em-tempo-real-atraves-de-sensores-mq-0-9/ */
class MQ2Sensor: public Sensor {
private:
	int pin;
	int RL_VALUE = 5;     //define the load resistance on the board, in kilo ohms
	int RO_CLEAN_AIR_FACTOR = 9.83;  //Resistência do sensor em ar limpo 9.83 de acordo com o datasheet
	int CALIBRATION_SAMPLE_INTERVAL = 50; //numero de leituras para calibracao
	int READ_SAMPLE_TIMES = 5; //numero de leituras para analise

	float CH4Curve[3]  =  {2.3,0.48,-0.44}; //curva CH4 aproximada baseada na sensibilidade descrita no datasheet {x,y,deslocamento} baseada em dois pontos 
                                          //p1: (log200, log3), p2: (log10000, log0.7)
                                          //inclinacao = (Y2-Y1)/(X2-X1)
                                          //vetor={x, y, inclinacao}
	float COCurve[3]  =  {2.3,0.72,-0.34};   
	float SmokeCurve[3] = {2.3,0.53,-0.42};                                                       
	float Ro = 10;             
 
	int GAS_CH4 = 1;
	int GAS_CO = 2;
	int GAS_SMOKE = 3;
	
	float MQRead();
	float MQGetGasPercentage(float rs_ro, int gas_id);
	int MQGetPercentage(float rs_ro, float *pcurve); //Rs/R0 é fornecido para calcular a concentracao em PPM do gas em questao. O calculo eh em potencia de 10 para sair da logaritmica
	float MQResistanceCalculation(int raw_adc); //funcao que recebe o tensao (dado cru) e calcula a resistencia efetuada pelo sensor. O sensor e a resistência de carga forma um divisor de tensão. 

public: 
	MQ2Sensor(int pin);
  SensorType getType(); 
  String read(); 
	boolean calibrate();
	float MQCalibration(); //funcao que calibra o sensor em um ambiente limpo utilizando a resistencia do sensor em ar limpo 9.83
	float readCH4();
	float readCO();
	float readSmoke();
};

class Sensors{

  private:
    Sensor** sensors;
    int8_t size;
    
  public:
    Sensors(int8_t maxNumberOfSensors);
    int8_t getSize();
    void addSensor(int index, Sensor* sensor);
    Sensor* getSensor(int index);
    void test();
    boolean calibrate();
    void stabilizationOfSensors();  // estado de estabilização dos sensores PRECISA SER IMPLEMENTADO
};
#endif