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
class MQ2: public Sensor {
public: 
	MQ2(int pin);
  SensorType getType(); 
  String read(); 
	void calibrate();
	float readLPG();
	float readCO();
	float readSmoke();
	float readCH4();
private:
	int _pin;
	int RL_VALUE = 5;     //define the load resistance on the board, in kilo ohms
	int RO_CLEAN_AIR_FACTOR = 9.83;  
	int CALIBARAION_SAMPLE_TIMES = 5; 
	int CALIBRATION_SAMPLE_INTERVAL = 50;
	int READ_SAMPLE_INTERVAL = 50;
	int READ_SAMPLE_TIMES = 5;

	float COCurve[3]  =  {2.3,0.72,-0.34};   
	float CH4Curve[3]  =  {2.3,0.48,-0.44}; //curva CH4 aproximada baseada na sensibilidade descrita no datasheet {x,y,deslocamento} baseada em dois pontos 
                                          //p1: (log200, log3), p2: (log10000, log0.7)
                                          //inclinacao = (Y2-Y1)/(X2-X1)
                                          //vetor={x, y, inclinacao}
   
	float SmokeCurve[3] = {2.3,0.53,-0.42};                                                       
	float LPGCurve[3]  =  {2.3,0.21,-0.47}; 
	float Ro = 10;             
 
  int GAS_LPG = 0;
	int GAS_CO = 1;
	int GAS_SMOKE = 2;
	int GAS_CH4 = 3;

	float lpg = 0;
	float co = 0;
	float smoke = 0;
	float ch4 = 0;
	
	float MQRead();
	float MQGetGasPercentage(float rs_ro_ratio, int gas_id);
	int MQGetPercentage(float rs_ro_ratio, float *pcurve);
	float MQCalibration();
	float MQResistanceCalculation(int raw_adc);

	int lastReadTime = 0;
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