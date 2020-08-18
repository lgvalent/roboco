#include <Arduino.h>
#include <roboco.h>

int Roboco::status = 0;

Roboco::Roboco(Sensors *sensors, Output *output, GPS *gps, CollectRegister *collectRegister, Workflow *workflow, Motor *motorLeft, Motor *motorRight){

        this->sensors = sensors;
        this->output = output;
        this->gps = gps;
        this->collectRegister = collectRegister;
        this->workflow = workflow;
        this->motorLeft = motorLeft;
        this->motorRight = motorRight;
}

void Roboco::setup(){
        this->output->lcdPrint("ROBOCO²", 0, 0);        
}

void Roboco::reset(){
        this->workflow->reset();
}

void Roboco::stabilizationOfSensors(){
        //      3º Iniciar captura dos dados
        //      3.1 Acionar simultâneamente até o final de ambas tarefas
        //              3.1.1 Acionar esvaziamento da câmara por TEMPO_ESVAZIAMENTO_CÂMARA segundos *Not
        //              3.1.2 Estabilizar sensor CO2 por 90 segundos (feito ao ligar o roboco) 27, 32
        unsigned long start = millis();
        int i = 0;
        do {            
                
                sensors->getSensor(i)->read(); // 4 é o CO2
                i++;
        } while (millis() - start < 9000);
}

void Roboco::collectData(){

        //     3.2 Coletar dados (metodo)
        //              3.2. CO2, temperaturas, pressão, altitude, etc
        //              3.2.1 Armazenar os dados no cartão
        //                      3.2.2 Gravar uma linha para cada capitura
        //                        TIME_STAMP, CO2, TEMP_INTERNA, PRESSÃO, ALTITUDE

        //      3.3 Repetir 3.2 a cada NTERVALO_ENTRE_CAPTURAS segundos
        //      3.4 Verificar o INTERVALO_AJUSTE_POSICIONAMENTO
        //              3.4.1 Repetir as atividades do 2º passo para reposicionamento
        //      3.5 Repetir 3.2 até esgotar o TEMPO_CAPTURA

        unsigned long start = millis();

        collectRegister->open();

        do {  

                collectRegister->write( this->gps->getCurrentLocation(), this->gps->getCurrentDateTime(), this->sensors);
        } while (millis() - start < this->currentStep->collectCount);

        collectRegister->close();
}

void Roboco::runTarget(){
        //      1º Ler o próximo destino no arquivo
        //      1.1 Verificar qual foi a última linhas do arquivo processada
        //          1.1.1 Ler em um arquivo ROBOCO.TXT o valor gravado na primeira linha do arquivo
        //      1.2 Ler a linha do arquivo ROBOCO.TXT
        //      1.3 Guardar os valores em variáveis globais/EEPROM_STEP_ADDRESS
        this->currentStep = this->workflow->getNextStep();

        //      2º Deslocar-se até o destino
        //      2.1 Localizar-se pelo GPS
        //      2.2 Verificar a distância e definir a velocidade de deslocamento
        //          2.2.1 Quanto mais longe do ponto, maior será a velocidade.
        //      2.3 Alinhar o bico // Sendo feito no angulo
        //      2.4 Avançar
        //      2.5 Volte para 2.3 x(distamcia) vezes, onde x pode ser uma razão entre a posição atual e o destino
        //      2.6 Volte para 2.1 até chegar

        this->gps->setTargetLocation(this->currentStep->latitude, this->currentStep->longitude);
        bool goToTarget = false; // vai para o alvo

        do{
                float distanceFactor;
                float angleFactor;

                this->currentLocation = this->gps->getCurrentLocation();

                angleFactor = map(this->currentLocation->angle, -180, 180, -100, 100) / 100.0; // sera o valor do angulo mapeado entre -100 e 100
                // map(valor, deMenor, deMaior, paraMenor, paraMaior);
                distanceFactor = this->gps->getDistanceToTarget();
                distanceFactor = distanceFactor > TARGET_SOFT_APPROACH_METER ? 1 : distanceFactor / TARGET_SOFT_APPROACH_METER; //  a distancia (em metros) do alvo influenciara a velocidade do motor
                int motorLeftFactor = distanceFactor - (distanceFactor * angleFactor);
                int motorRightFactor = distanceFactor + (distanceFactor * angleFactor);

                if (currentLocation->angle != 0 && distanceFactor != 0)
                {
                        if (currentLocation->angle < 180)
                                this->motorLeft->move(CLOCKWISE, map(motorLeftFactor * 100, 0, 100, 225, 255)); // move motor da esqueda
                        // motorLeft = motor->move;
                        else
                                this->motorRight->move(CLOCKWISE, map(motorRightFactor * 100, 0, 100, 225, 255)); // move o motor da direita
                                                                                                                  // motorRight = motor->move;
                }

                goToTarget = distanceFactor > TARGET_MINIMAL_DISTANCE_APPROACH_FACTOR;

        }while(goToTarget); 
}

void Roboco::runBackToOrigin(){
 //      4 voltar para lugar de origem
}

void Roboco::run(){

        unsigned long start = millis();
        this->stabilizationOfSensors();

        switch (status){
                case 0:
                        // overflow codicao para ir a leitura depois 90s 
                        if (this->workflow->getNextStep() != NULL){
                                runTarget();
                                status = 2;
                        }else{
                                status = 1;
                        }
                       
                case 1:
                        runBackToOrigin();

                        break;
                case 2:
                        do {  
                                collectData();
                        } while ((millis() - start) < this->currentStep->collectInterval);

                        status = 0;
                        break;
               
        }
}
void Roboco::test(){

        Serial.println(" ");
        Serial.println("Testing Roboco...");
        this->gps->test(); 
        Serial.println(" ");
        this->sensors->test();
        //this->output->test();
        //this->collectRegister->test(); // em andamento
        //this->workflow->test();
        //this->motorLeft->test();
        //this->motorRight->test();
}

void Roboco::calibrateSensors(){
        this->sensors->calibrate();
}