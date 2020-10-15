#include <Arduino.h>
#include <sensors.h>

String Sensor::SENSOR_TYPE_NAMES[] = {"Luminosity", "Pressure", "Altitude", "Temperature", "CO2", "Compass"};

String Sensor::getTypeName()
{
  return SENSOR_TYPE_NAMES[this->getType()];
}

boolean Sensor::calibrate()
{
  return true;
}

/*******************************************************/

Co2Sensor::Co2Sensor(int8_t pinRx, int8_t pinTx)
{

  SoftwareSerial *softwareSerial = new SoftwareSerial(pinRx, pinTx);
  softwareSerial->begin(9600);
  this->serial = softwareSerial;
  this->mhz19 = new MHZ19();
  mhz19->begin(*Co2Sensor::serial);
}

Co2Sensor::Co2Sensor(HardwareSerial *serial)
{

  serial->begin(9600);
  this->serial = serial;
  this->mhz19 = new MHZ19();
  mhz19->begin(*Co2Sensor::serial);
}

SensorType Co2Sensor::getType()
{
  return CO2;
}

String Co2Sensor ::read()
{
  // Código de leitura Serial
  return String(this->mhz19->getCO2(false));
};

boolean Co2Sensor::calibrate()
{
  // Código de calibração do sensor!! DUrará horas???
  this->mhz19->autoCalibration(false);
  return true;
};

/*******************************************************/

LuminositySensor::LuminositySensor(int8_t pin)
{
  pinMode(pin, INPUT);
};

SensorType LuminositySensor::getType()
{
  return LUMINOSITY;
};

String LuminositySensor::read()
{
  return String(analogRead(this->pin));
};

boolean LuminositySensor::calibrate()
{
  return true;
};

/*******************************************************/

TemperatureSensor::TemperatureSensor(Adafruit_BMP280 *sensor)
{

  this->sensor = sensor;
};

SensorType TemperatureSensor::getType()
{
  return TEMPERATURE;
};

String TemperatureSensor::read()
{
  return String(this->sensor->readTemperature());
};

boolean TemperatureSensor::calibrate()
{
  return true;
};

/*******************************************************/

PressureSensor::PressureSensor(Adafruit_BMP280 *sensor)
{

  this->sensor = sensor;
};

SensorType PressureSensor::getType()
{
  return PRESSURE;
};

String PressureSensor::read()
{
  return String(this->sensor->readPressure());
};

boolean PressureSensor::calibrate()
{
  return true;
};

/*******************************************************/

AltitudeSensor::AltitudeSensor(Adafruit_BMP280 *sensor)
{

  this->sensor = sensor;
};

SensorType AltitudeSensor::getType()
{
  return ALTITUDE;
};

String AltitudeSensor::read()
{
  return String(this->sensor->readAltitude(1013.25));
}

boolean AltitudeSensor::calibrate()
{
  return true;
};

/*******************************************************/

CompassSensorQMC5883::CompassSensorQMC5883(QMC5883LCompass *sensor)
{
  this->sensor = sensor;
  this->sensor->init();
  this->sensor->setSmoothing(10, true); 
};

SensorType CompassSensorQMC5883::getType()
{
  return COMPASS;
};

String CompassSensorQMC5883::read()
{
  /* Code to read in degrees*/
  this->sensor->read();
  return String(this->sensor->getAzimuth());
}

boolean CompassSensorQMC5883::calibrate()
{

  int calibrationData[3][2];
  bool changed = false;
  bool done = false;
  int t = 0;
  int c = 0;

  while (!done)
  {
    int x, y, z;

    // Read this->sensor->values
    this->sensor->read();

    // Return XYZ readings
    x = this->sensor->getX();
    y = this->sensor->getY();
    z = this->sensor->getZ();

    changed = false;

    if (x < calibrationData[0][0])
    {
      calibrationData[0][0] = x;
      changed = true;
    }
    if (x > calibrationData[0][1])
    {
      calibrationData[0][1] = x;
      changed = true;
    }

    if (y < calibrationData[1][0])
    {
      calibrationData[1][0] = y;
      changed = true;
    }
    if (y > calibrationData[1][1])
    {
      calibrationData[1][1] = y;
      changed = true;
    }

    if (z < calibrationData[2][0])
    {
      calibrationData[2][0] = z;
      changed = true;
    }
    if (z > calibrationData[2][1])
    {
      calibrationData[2][1] = z;
      changed = true;
    }

    if (changed && !done)
    {
      Serial.println("CALIBRATING... Keep moving your sensor around.");
      c = millis();
    }
    t = millis();

    if ((t - c > 5000) && !done)
    {
      done = true;

      this->sensor->setCalibration(calibrationData[0][0], calibrationData[0][1], calibrationData[1][0], calibrationData[1][1], calibrationData[2][0], calibrationData[2][1]);
      /*TODO Armazenar na EPROM a última calibração */
    }
  }

  return true;
};

/*******************************************************/
CompassSensorHMC5883::CompassSensorHMC5883(Adafruit_HMC5883_Unified* sensor)
{
  this->sensor = sensor;
  if(!sensor->begin())
  {
      Serial.println("HMC5883 not detected ... Check your wiring!");
  }
};

SensorType CompassSensorHMC5883::getType()
{
  return COMPASS;
};

String CompassSensorHMC5883::read()
{
  /* SOURCE: https://platformio.org/lib/show/380/Adafruit%20HMC5883%20Unified*/
  /* Get a new sensor event */ 
  sensors_event_t event; 
  this->sensor->getEvent(&event);

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.33;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  return String(headingDegrees);
}

boolean CompassSensorHMC5883::calibrate()
{
  return true;
};


/*******************************************************/
MQ2::MQ2(int pin) {
  _pin = pin;
}

SensorType MQ2::getType()
{
  return CH4;
};

void MQ2::calibrate(){
    Ro = MQCalibration();
    Serial.print("Ro: ");
    Serial.print(Ro);
    Serial.println(" kohm");
}

float MQ2::readLPG(){
    if (millis()<(lastReadTime + 10000) && lpg != 0){
        return lpg;
    }else{
        return lpg = MQGetGasPercentage(MQRead()/10,GAS_LPG);
    }
}

float MQ2::readCO(){
    if (millis()<(lastReadTime + 10000) && co != 0){
        return co;
    }else{
        return co = MQGetGasPercentage(MQRead()/10,GAS_CO);
    }
}

float MQ2::readSmoke(){
    if (millis()<(lastReadTime + 10000) && smoke != 0){
        return smoke;
    }else{
        return smoke = MQGetGasPercentage(MQRead()/10,GAS_SMOKE);
    }
}

float MQ2::readCH4(){
    if (millis()<(lastReadTime + 10000) && ch4 != 0){
        return ch4;
    }else{
        return ch4 = MQGetGasPercentage(MQRead()/10,GAS_CH4);
    }
}


float MQ2::MQResistanceCalculation(int raw_adc) {
   return (((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}

float MQ2::MQCalibration() {
  float val=0;
 
  for (int i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value
 
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 
  return val; 
}
float MQ2::MQRead() {
  int i;
  float rs=0;
  int val = analogRead(_pin);

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(val);
    delay(READ_SAMPLE_INTERVAL);
  }
 
  rs = rs/READ_SAMPLE_TIMES;
  return rs;  
}
float MQ2::MQGetGasPercentage(float rs_ro_ratio, int gas_id) {
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  } else if ( gas_id == GAS_CH4 ) {
     return MQGetPercentage(rs_ro_ratio,CH4Curve);
  }    
  return 0;
}
int MQ2::MQGetPercentage(float rs_ro_ratio, float *pcurve) {
  return (pow(10,(((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}

String MQ2::read(){
  return String(readCH4());
}

/*******************************************************/

Sensors::Sensors(int8_t maxNumberOfSensors) : size(maxNumberOfSensors)
{
  this->sensors = new Sensor *[maxNumberOfSensors];
}

int8_t Sensors::getSize()
{
  return this->size;
};

void Sensors::addSensor(int index, Sensor *sensor)
{
  this->sensors[index] = sensor;
};

Sensor *Sensors::getSensor(int index)
{
  
  return this->sensors[index];
};

void Sensors::test()
{

  Serial.println("Testing Sensors...");
  for (int index = 0; index < this->getSize(); index++)
  {
    Sensor *sensor = this->getSensor(index);
    Serial.println(" ");
    Serial.print(sensor->getTypeName());
    Serial.print(":");
    Serial.println(sensor->read());
  }
  //delay(2000);
  //Serial.println("******************* ");
}

boolean Sensors::calibrate()
{

  Serial.println("Calibrating Sensors...");
  for (int i = 0; i < this->getSize(); i++)
  {
    Sensor *sensor = this->getSensor(i);
    Serial.print(sensor->getTypeName());
    Serial.print(":");
    Serial.println(sensor->calibrate());
  }

  return true;
}

void Sensors::stabilizationOfSensors()
{

  unsigned long start = millis();

  do
  {
    for (int index = 0; index < getSize(); index++)
    {
      Sensor *sensor = this->getSensor(index);
      sensor->read();
    }
  } while (millis() - start < 2000); // fica por aqui por 2s
}