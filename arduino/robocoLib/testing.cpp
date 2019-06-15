#include <Arduino.h>

#include <testing.h>

Testing:: Testing(Sensors* sensors, Output* output, GPS* gps, CollectRegister* collectRegister, Workflow* workflow, Motor* motorLeft, Motor* motorRight){
        this->sensors = sensors;
        this->output = output;
        this->gps = gps;
        this->collectRegister = collectRegister;
        this->workflow = workflow;
        this->motorLeft = motorLeft;
        this->motorRight = motorRight;
}
void Testing::setup(unsigned char teste){
    Serial.println("oieee  ");
    Serial.print(teste);
    switch (teste)
    {
    case 1 : // Testing MOTORS
        this->motorTeste();
    break;
    case 2 : // Testing sensor de temperatura
        this->tempTeste();
    break;
        break;
    case 3 : // Testing SENSORS
        this->ldrTeste();
    break;
    case 4 : // Testing GPS
        this->motorTeste();
    break;
    case 5 : // Testing collectRegister
        this->motorTeste();
    break;
    case 6 : // Testing Workflow
        this->motorTeste();
    break;
    }    
    if(teste == 0){
        for(unsigned char i=1; i<7; i++){
            this->setup(i);
        }
    } 
}
void Testing::motorTeste(){
                unsigned char comando = 0;
                unsigned char pwm = 0;
                Serial.println("TESTING MOTOR");
              while(comando != 1){
                  this->output->lcdPrint("MOTOR TEST",3,0);
                  this->output->lcdPrint("ENTER THE COMAND",0,1);
                  while(Serial.available()){
                  comando = Serial.read();
                  this->output->lcdClear();
                  this->output->lcdPrint("MOTOR TEST",3,0);
                  Serial.print("comando : "); Serial.println(comando-48);
                  switch (comando)
                                  {
                                  case '2':
                                  this->output->lcdPrint("BACK",6,1);
                                  this->motorRight->move(ANTICLOCKWISE, pwm);
                                  this->motorLeft->move(ANTICLOCKWISE, pwm);
                                  delay(2000);
                                  this->motorRight->stop();
                                  this->motorLeft->stop();
                                  break;
                                  
                                  case '4':
                                  this->output->lcdPrint("LEFT",6,1);
                                  this->motorRight->move(CLOCKWISE, pwm);
                                  this->motorLeft->move(ANTICLOCKWISE, pwm);
                                  delay(2000);
                                  this->motorRight->stop();
                                  this->motorLeft->stop();
                                  break;
                                  case '6':
                                  this->output->lcdPrint("RIGHT",5,1);
                                  this->motorRight->move(ANTICLOCKWISE, pwm);
                                  this->motorLeft->move(CLOCKWISE, pwm);
                                  delay(2000);
                                  this->motorRight->stop();
                                  this->motorLeft->stop();
                                  break;
                                  case '8':
                                  this->output->lcdPrint("FORWARD",4,1);
                                  this->motorRight->move(CLOCKWISE, pwm);
                                  this->motorLeft->move(CLOCKWISE, pwm);
                                  delay(2000);
                                  this->motorRight->stop();
                                  this->motorLeft->stop();
                                  break;
                                  case '1' :
                                  comando = 1;
                                  break;
                                  case '7' :
                                  if(pwm>50) pwm = pwm-51;
                                  this->output->lcdPrint(" PWM : ",0,1);
                                  this->output->lcdPrint(String(pwm),6,1);
                                  Serial.print("PWM : "); Serial.println(pwm);
                                  delay(1000);
                                  break;
                                  case '9' :
                                  if(pwm<205) pwm = pwm+51;
                                  this->output->lcdPrint(" PWM : ",0,1);
                                  this->output->lcdPrint(String(pwm),6,1);
                                  Serial.print("PWM : "); Serial.println(pwm);
                                  delay(1000);
                                  break;
                                  }
                                  this->output->lcdClear();
                  }
              }
              Serial.println("saindo");
              this->output->lcdPrint("EXISTING",4,0);
              this->output->lcdPrint("MOTOR TEST",3,1);
              delay(2000);
              this->output->lcdClear();
}
void Testing::tempTeste(){
    unsigned char exit = 0;
    while(!this->sensors->bmpValid()){
    this->output->lcdClear();
    this->output->lcdPrint("SENSOR TEMP",0,0);
    this->output->lcdPrint("DESCONECTED",0,1);
    }
    while(exit == 0){
        if(Serial.available()){
            exit = Serial.read();
        }
    this->output->lcdClear();
    this->output->lcdPrint("TEMPERATURE TEST",0,0);
    this->output->lcdPrint(String(this->sensors->getTemperatureC(),2),5,1);
    this->output->lcdPrint("*C",17,1);
    delay(200);
    }
}

void Testing::co2Teste(){

}
void Testing::ldrTeste(){
    unsigned char exit=0;
    while(exit == 0){
        if(Serial.available()){
            exit = Serial.read();
        }
    this->output->lcdClear();
    this->output->lcdPrint("BRIGHTNESS TEST",0,0);
    this->output->lcdPrint(String(this->sensors->getLuminosity()),5,1);
    delay(200);
    }
}
