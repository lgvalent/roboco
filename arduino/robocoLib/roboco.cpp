#include <Arduino.h>

#include <roboco.h>

Roboco:: Roboco(Sensors *sensors, Output *output, GPS *gps, CollectRegister *collectRegister, Workflow *workflow, Motor *motorLeft, Motor *motorRight){
        this->sensors = sensors;
        this->output = output;
        this->gps = gps;
        this->collectRegister = collectRegister;
        this->workflow = workflow;        

        this->motorLeft = motorLeft;
        this->motorRight = motorRight;
};

void Roboco::setup(){
        int const DELAY = 500;
        // Testing SENSORS
        
        // Testing LEDs
        this->output->setLed0(true);
        delay(DELAY);
        this->output->setLed0(false);
        this->output->setLed1(true);
        delay(DELAY);
        this->output->setLed1(false);
        this->output->setLed2(true);
        delay(DELAY);
        this->output->setLed2(false);

        // Testing GPS

        // Testing collectRegister

        // Testing Workflow
        if(this->workflow->getNextStep() == NULL){
                this->output->setLed0(true);
                this->output->setLed1(true);
                this->output->setLed2(true);
                while(1);
        }else{
                this->workflow->backOneStep();
        }


        // Testing MOTORS
        this->motorRight->move(CLOCKWISE, 255);
        delay(2000);
        this->motorRight->stop();
        this->motorLeft->move(CLOCKWISE, 255);
        delay(2000);
        this->motorRight->stop();  
};

void Roboco::reset(){
        this->workflow->reset();
}

void Roboco::run(){
        
}
  
