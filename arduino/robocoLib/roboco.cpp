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

void Roboco::setup(){
        this->output->lcdPrint("ROBOCO",0,0);
}

/*
void Roboco::reset(){
        this->workflow->reset();

        int lumens = this->sensors->getSensor(Roboco::LUMINOSITY)->read().toInt();

        int lumens = this->sensors->readLuminosity();
};

void Roboco::run(){
        
        currentStep = this->whorkFlow->getNextStep // 1º Ler o próximo destino no arquivo
        currentLocation = this->gps->getLocation // 2º Deslocar-se até o destino
   
        // this->gps->getPreviousLocation() //para conparar a velocidade e onde ele está/estava, ter um time para ver o tempo de uso do arduino.
       
        // fazer o delta e uma funão para estipular a velocidade
        distanceLatitude = currentStep->latitude - currentLocation->latitude;// Verificar a distância e definir a velocidade (?) de deslocamento
        distanceLongitude = currentStep->longitude - currentLocation->longitude; //após verificar a distancia deve definir a velocidade, porem n temos um controle de velocidade na classe dos motores
       
        if (currentLocation->angle < 10  &&  > 350 ) { // Alinhar o bico
                motorLeft = motor->move; // move o motor da esqueda
                motorRight = motor->move; // move o motor da direita
        }
        
        // Outra forma de fazer para alinhar o bico
        if (currentLocation->angle !=0 &&  distanceLongitude !=0 && distanceLatitude !=0) {
                if (currentLocation->angle < 180)
                          motorLeft = motor->move;
                else
                          motorRight = motor->move;
        }

        // OBS: para alinhar o bico pega o currentstep (latitude e longitude) -alvo- fazer uma funcao que dependendo do anglo de distancia entre o alvo ate a localizacao atual, gira um pouco mais o motor da direita ou da esquerda
        //funcao map do arduino para conseguir ter diferenca de giro (220 - 255) com a funcao map o giro passa a ser de 0 a 255
        
}*/
