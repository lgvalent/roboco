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
        
        while (this->workflow(int8_t pinSD)){ // Le o proximo destino do txt
                
                this->gps(int8_t pinRx, int8_t pinTx); // Vai para o destino
                this->Sensors(int8_t pinLum, int8_t pinRxCo2, int8_t pinTxCo2); // Começa a coleta dos dados
                this-> CollectRegister(int8_t pinSD); //Armazena os dados no cartão 
 
        }
        
}
  
