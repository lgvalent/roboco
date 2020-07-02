#include <Arduino.h>

#include <testing.h>

Testing::Testing(Sensors *sensors, Output *output, GPS *gps, CollectRegister *collectRegister, Workflow *workflow, Motor *motorLeft, Motor *motorRight)
{
    this->sensors = sensors;
    this->output = output;
    this->gps = gps;
    this->collectRegister = collectRegister;
    this->workflow = workflow;
    this->motorLeft = motorLeft;
    this->motorRight = motorRight;
}
void Testing::setup(unsigned char teste)
{
    Serial.println("Starting tests...");
    Serial.print(teste);
    switch (teste)
    {
    case 1: // Testing MOTORS
        this->testMotor();
        break;
    case 2: // Testing all sensors
        this->testSensors();
        break;
    case 3: // Testing SENSORS
        this->testGpsNEO6M();
        break;
    case 10:
        while(1){
        this->apresentacao();
        }
        break;
    }
    if (teste == 0)
    {
        for (unsigned char i = 1; i < 7; i++)
        {
            this->setup(i);
        }
    }
}
void Testing::testMotor()
{
    unsigned char comando = 0;
    unsigned char pwm = 0;
    Serial.println("TESTING MOTOR");
    while (comando != 1)
    {
        this->output->lcdPrint("MOTOR TEST", 3, 0);
        this->output->lcdPrint("ENTER THE COMAND", 0, 1);
        while (Serial.available())
        {
            comando = Serial.read();
            this->output->lcdClear();
            this->output->lcdPrint("MOTOR TEST", 3, 0);
            Serial.print("comando : ");
            Serial.println(comando - 48);
            switch (comando)
            {
            case '2':
                this->output->lcdPrint("BACK", 6, 1);
                this->motorRight->move(ANTICLOCKWISE, pwm);
                this->motorLeft->move(ANTICLOCKWISE, pwm);
                delay(2000);
                this->motorRight->stop();
                this->motorLeft->stop();
                break;

            case '4':
                this->output->lcdPrint("LEFT", 6, 1);
                this->motorRight->move(CLOCKWISE, pwm);
                this->motorLeft->move(ANTICLOCKWISE, pwm);
                delay(2000);
                this->motorRight->stop();
                this->motorLeft->stop();
                break;
            case '6':
                this->output->lcdPrint("RIGHT", 5, 1);
                this->motorRight->move(ANTICLOCKWISE, pwm);
                this->motorLeft->move(CLOCKWISE, pwm);
                delay(2000);
                this->motorRight->stop();
                this->motorLeft->stop();
                break;
            case '8':
                this->output->lcdPrint("FORWARD", 4, 1);
                this->motorRight->move(CLOCKWISE, pwm);
                this->motorLeft->move(CLOCKWISE, pwm);
                delay(2000);
                this->motorRight->stop();
                this->motorLeft->stop();
                break;
            case '1':
                comando = 1;
                break;
            case '7':
                if (pwm > 50)
                    pwm = pwm - 51;
                this->output->lcdPrint(" PWM : ", 0, 1);
                this->output->lcdPrint(String(pwm), 6, 1);
                Serial.print("PWM : ");
                Serial.println(pwm);
                delay(1000);
                break;
            case '9':
                if (pwm < 205)
                    pwm = pwm + 51;
                this->output->lcdPrint(" PWM : ", 0, 1);
                this->output->lcdPrint(String(pwm), 6, 1);
                Serial.print("PWM : ");
                Serial.println(pwm);
                delay(1000);
                break;
            }
            this->output->lcdClear();
        }
    }
    Serial.println("saindo");
    this->output->lcdPrint("EXISTING", 4, 0);
    this->output->lcdPrint("MOTOR TEST", 3, 1);
    delay(2000);
    this->output->lcdClear();
}
void Testing::testSensors()
{
    unsigned char exit = 0;
    for (int i = 0; i < this->sensors->getSize(); i++)
    {
        // while(!this->sensors->getSensor(Sensor::bmpValid()){
        //     this->output->lcdClear();
        //     this->output->lcdPrint("SENSOR TEMP", 0, 0);
        //     this->output->lcdPrint("DESCONECTED", 0, 1);
        // }
        Sensor* sensor = this->sensors->getSensor(i);

        this->output->lcdClear();
        this->output->lcdPrint(sensor->getTypeName(), 0, 0);
        this->output->lcdPrint(sensor->read(), 5, 1);
        delay(200);
    }
}

void Testing::testGps()
{
    unsigned char exit = 0;
    unsigned long timer = millis();
    while (exit == 0)
    {
        if (Serial.available())
        {
            exit = Serial.read();
        }
        if (millis() - timer > 100)
        {
            Location *loc = gps->getCurrentLocation();
            DataTimer *dat = gps->getCurrentDataTimer();
            timer = millis(); // reset the timer
            Serial.print("\nTime: ");
            Serial.print((dat->hour - 3), DEC);
            Serial.print(':');
            Serial.print(dat->minute, DEC);
            Serial.print(':');
            Serial.print(dat->seconds, DEC);
            Serial.print('.');
            Serial.print("Date: ");
            Serial.print(dat->day, DEC);
            Serial.print('/');
            Serial.print(dat->month, DEC);
            Serial.print("/20");
            Serial.println(dat->year, DEC);
            //Serial.print("Fix: "); Serial.print((int)gps->fix);
            //Serial.print(" quality: "); Serial.println((int)gps->fixquality);
            Serial.print("Location (in degrees, works with Google Maps): ");
            Serial.println(loc->latitude, 4);
            Serial.print("Location (in degrees, works with Google Maps): ");
            Serial.println(loc->longitude, 4);
            // Serial.print("Speed (knots): "); Serial.println(gps->speed);
            //Serial.print("Angle: "); Serial.println(loc->angle);
            //Serial.print("Altitude: "); Serial.println(loc->altitude);
            //Serial.print("Satellites: "); Serial.println((int)gps->satellites);
            output->lcdClear();
            output->lcdPrint("Time: ", 0, 0);
            output->lcdPrint(String((dat->hour - 3), DEC), 17, 0);
            output->lcdPrint(":", 17, 0);
            output->lcdPrint(String(dat->minute, DEC), 17, 0);
            output->lcdPrint(":", 17, 0);
            output->lcdPrint(String(dat->seconds, DEC), 17, 0);
            output->lcdPrint("Date: ", 0, 1);
            output->lcdPrint(String(dat->day, DEC), 17, 1);
            output->lcdPrint("/", 17, 1);
            output->lcdPrint(String(dat->month, DEC), 17, 1);
            output->lcdPrint("/", 17, 1);
            output->lcdPrint(String(dat->year, DEC), 17, 1);
            //Serial.print("Fix: "); Serial.print((int)gps->gps->fix);
            //Serial.print(" quality: "); Serial.println((int)gps->gps->fixquality);
            //Serial.print("Location (in degrees, works with Google Maps): ");
            //Serial.println(loc->latitude, 4);
            //Serial.print("Location (in degrees, works with Google Maps): ");
            //Serial.println(loc->longitude,4);
            //Serial.print("Speed (knots): "); Serial.println(gps->speed);
            //Serial.print("Angle: "); Serial.println(loc->angle);
            //Serial.print("Altitude: "); Serial.println(loc->altitude);
            //Serial.print("Satellites: "); Serial.println((int)gps->satellites);
            free(dat);
            free(loc);
            delay(1000);
        }
    }
}
void Testing::testGpsMTK33x9(){
  
    Location* loc = gps->getCurrentLocation();
    DataTimer* dat = gps->getCurrentDataTimer();
    unsigned long timer = millis();

    if(millis() - timer > 100) {
        timer = millis(); // reset the timer  
        Serial.print("\nTime: ");
        Serial.print((dat->hour-3), DEC); Serial.print(':');
        Serial.print(dat->minute, DEC); Serial.print(':');
        Serial.print(dat->seconds, DEC); Serial.print('.');
        Serial.print("Date: ");
        Serial.print(dat->day, DEC); Serial.print('/');
        Serial.print(dat->month, DEC); Serial.print("/20");
        Serial.println(dat->year, DEC);
        Serial.print("Fix: "); 
        // Serial.print((int)gps->fix);
        Serial.print(" quality: "); 
        // Serial.println((int)gps->fixquality);
        Serial.print("Location (in degrees, works with Google Maps): ");
        Serial.println(loc->latitude, 4);
        Serial.print("Location (in degrees, works with Google Maps): ");
        Serial.println(loc->longitude,4);      
        Serial.print("Speed (knots): "); 
        // Serial.println(gps->speed);
        Serial.print("Angle: "); 
        Serial.println(loc->angle);
        Serial.print("Altitude: "); 
        Serial.println(loc->altitude);
        Serial.print("Satellites: "); 
        // Serial.println((int)gps->satellites);
        free(dat);
        free(loc);
  }
}

// void Testing::callTestGpsNEO6M(){

//    if (this->use_sw_serial){
//       while(this->gpsSwSerial->available()){
//          if (this->gps->encode(this->gpsSwSerial->read())){
//             this->testGpsNEO6M();
//          }
//       }
//    }else{
//        while(this->gpsHwSerial->available()){
//           if (this->gps->encode(this->gpsHwSerial->read())){
//             this->testGpsNEO6M();
//          }
//       }
//    } 
// }

// void Testing::testGpsNEO6M(){
   
//    unsigned long date, hour;
//    float lat, lon, vel;
//    unsigned short sat;  

//    //Hora e data                 
//    this->gps->get_datetime(&date, &hour);
      
//    Serial.print("--");
//    Serial.print(hour / 1000000);
//    Serial.print(":");
//    Serial.print((hour % 1000000) / 10000);
//    Serial.print(":");
//    Serial.print((hour % 10000) / 100);
//    Serial.print("--");
//    Serial.print(date / 10000);
//    Serial.print("/");
//    Serial.print((date % 10000) / 100);
//    Serial.print("/");
//    Serial.print(date % 100);
//    Serial.println("--");
         
//    //latitude e longitude
//    this->gps->f_get_position(&lat, &lon);
      
//    Serial.print("Latitude: ");
//    Serial.println(lat, 6);
//    Serial.print("Longitude: ");
//    Serial.println(lon, 6);
      
//    //velocidade
//    vel = this->gps->f_speed_kmph();
      
//    Serial.print("Velocidade: ");
//    Serial.println(vel);
      
//    //Satelites
//    sat = this->gps->satellites();
//    if (sat != TinyGPS::GPS_INVALID_SATELLITES) {
//       Serial.print("Satelites: ");
//       Serial.println(sat);
//    }
//    Serial.println("");
// }

void Testing::testGpsNEO6M(){
 
    Location* loc = gps->getCurrentLocation();
    DataTimer* dat = gps->getCurrentDataTimer();
    unsigned long timer = millis();
    float vel;
    unsigned short sat; 

      Serial.print("--");
      Serial.print(dat->hour); 
      Serial.print(":");
      Serial.print(dat->minute); 
      Serial.print(":");
      Serial.print(dat->seconds); 
      Serial.print("--");
      Serial.print(dat->day);
      Serial.print("/");
      Serial.print(dat->month);
      Serial.print("/");
      Serial.print(dat->year);
      Serial.println("--");
      
      //latitude e longitude
      Serial.print("Latitude: ");
      Serial.println(loc->latitude, 6);
      Serial.print("Longitude: ");
      Serial.println(loc->longitude, 6);

      //angulo
      Serial.print("Angulo: ");
      Serial.println(loc->angle);

    //altitude
    Serial.print("Altitude: ");
    Serial.println(loc->altitude);

    Serial.println("");
}

void Testing::apresentacao(){
                this->output->lcdPrint("FORWARD", 4, 1);
                this->motorRight->move(CLOCKWISE, 255);
                this->motorLeft->move(CLOCKWISE, 255);
                delay(2000);
                this->motorRight->stop();
                this->motorLeft->stop();
                this->output->lcdPrint("BACK", 6, 1);
                this->motorRight->move(ANTICLOCKWISE, 255);
                this->motorLeft->move(ANTICLOCKWISE, 255);
                delay(2000);
                this->motorRight->stop();
                this->motorLeft->stop();
                this->output->lcdPrint("RIGHT", 5, 1);
                this->motorRight->move(ANTICLOCKWISE, 255);
                this->motorLeft->move(CLOCKWISE, 255);
                delay(2000);
                this->motorRight->stop();
                this->motorLeft->stop();
                this->output->lcdPrint("LEFT", 6, 1);
                this->motorRight->move(CLOCKWISE, 255);
                this->motorLeft->move(ANTICLOCKWISE, 255);
                delay(2000);
                this->motorRight->stop();
                this->motorLeft->stop();
    }