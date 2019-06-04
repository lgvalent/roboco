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
};

void Roboco::setup(){
     
        // Testing SENSORS
        
        // Testing LEDs

        // Testing GPS

        // Testing collectRegister

        // Testing Workflow

        // Testing MOTORS
  
};

void Roboco::reset(){
        this->workflow->reset();
}

void Roboco::run(){
        
        currentStep = this->whorkFlow->getNextStep // 1º Ler o próximo destino no arquivo
        currentLocaition = this->gps->getLocation // 2º Deslocar-se até o destino
   
        // previousLocation= currentLocation //para conparar a velocidade e onde ele está/estava, ter um time para ver o tempo de uso do arduino.

    
        // fazer o delta e uma funão para estipular a velocidade
        // para alinhar o bico pega o currentstep (latitude e longitude) -alvo- fazer uma funcao que dependendo do anglo de distancia entre o alvo ate a localizacao atual, gira um pouco mais o motor da direita ou da esquerda
        
        //funcao mape do arduino para conseguir ter diferenca de giro (220 - 255) com a funcao mape o giro passa a ser de 0 a 255
        
       
        }
        
}
  
