#include <Arduino.h>

#include <roboco.h>

Roboco:: Roboco(Sensors* sensors, Output* output, GPS* gps, CollectRegister* collectRegister, Workflow* workflow, Motor* motorLeft, Motor* motorRight){
        this->sensors = sensors;
        this->output = output;
        this->gps = gps;
        this->collectRegister = collectRegister;
        this->workflow = workflow;
        this->motorLeft = motorLeft;
        this->motorRight = motorRight;
}

void Roboco::setup(unsigned char testing){


        if(testing == 1){ //TESTING MOTORES
                unsigned char comando = 0;
                unsigned char pwm = 0;
                 Serial.println("TESTING MOTOR");
              while(comando != 1){
                  if(Serial.available()){
                  comando = Serial.read();
                  Serial.print("comando : "); Serial.println(comando-48);
                  switch (comando)
                                  {
                                  case '2':
                                  this->motorRight->move(ANTICLOCKWISE, pwm);
                                  this->motorLeft->move(ANTICLOCKWISE, pwm);
                                  delay(1000);
                                  this->motorRight->stop();
                                  this->motorLeft->stop();
                                  break;
                                  
                                  case '4':
                                  this->motorRight->move(CLOCKWISE, pwm);
                                  this->motorLeft->move(ANTICLOCKWISE, pwm);
                                  delay(1000);
                                  this->motorRight->stop();
                                  this->motorLeft->stop();
                                  break;
                                  case '6':
                                  this->motorRight->move(ANTICLOCKWISE, pwm);
                                  this->motorLeft->move(CLOCKWISE, pwm);
                                  delay(1000);
                                  this->motorRight->stop();
                                  this->motorLeft->stop();
                                  break;
                                  case '8':
                                  this->motorRight->move(CLOCKWISE, pwm);
                                  this->motorLeft->move(CLOCKWISE, pwm);
                                  delay(1000);
                                  this->motorRight->stop();
                                  this->motorLeft->stop();
                                  break;
                                  case '1' :
                                  comando = 1;
                                  break;
                                  case '7' :
                                  if(pwm>50) pwm = pwm-51;
                                  Serial.print("PWM : "); Serial.println(pwm);
                                  break;
                                  case '9' :
                                  if(pwm<205) pwm = pwm+51;
                                  Serial.print("PWM : "); Serial.println(pwm);
                                  break;
                                  }
                  }
              }
                
        }
        if(testing == 2){ //TESTING GPS
                while(1){
                        this->gps->testeGps();
                }
        }
     
        // Testing SENSORS
        
        // Testing LEDs

        // Testing GPS

        // Testing collectRegister

        // Testing Workflow

        // Testing MOTORS
  
}
/*
void Roboco::reset(){
        this->workflow->reset();
}

void Roboco::run(){
        
        currentStep = this->whorkFlow->getNextStep // 1º Ler o próximo destino no arquivo
        currentLocaition = this->gps->getLocation // 2º Deslocar-se até o destino
   
        // previousLocation= currentLocation //para conparar a velocidade e onde ele está/estava, ter um time para ver o tempo de uso do arduino.
       
        // fazer o delta e uma funão para estipular a velocidade
        distanceLatitude = currentStep->latitude - currentLocation->latitude;// Verificar a distância e definir a velocidade (?) de deslocamento
        didstanceLongitude = currentStep->longitude - currentLocation->longitude; //após verificar a distancia deve definir a velocidade, porem n temos um controle de velocidade na classe dos motores
       
        if (currentLocation->angle < 10  &&  > 350 ) { // Alinhar o bico
                motorLeft = motor->move; // move o motor da esqueda
                motorRight = motor->move; // move o motor da direita
                
        }
        
     
        // para alinhar o bico pega o currentstep (latitude e longitude) -alvo- fazer uma funcao que dependendo do anglo de distancia entre o alvo ate a localizacao atual, gira um pouco mais o motor da direita ou da esquerda
        
        //funcao mape do arduino para conseguir ter diferenca de giro (220 - 255) com a funcao mape o giro passa a ser de 0 a 255
        
       
        }
        
}*/
  
