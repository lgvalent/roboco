#include <Arduino.h>

#include <roboco.h>

Roboco::Roboco(Sensors *sensors, Output *output, GPS *gps, CollectRegister *collectRegister, Workflow *workflow, Motor *motorLeft, Motor *motorRight)
{
        this->sensors = sensors;
        this->output = output;
        this->gps = gps;
        this->collectRegister = collectRegister;
        this->workflow = workflow;
        this->motorLeft = motorLeft;
        this->motorRight = motorRight;
}

void Roboco::setup()
{
        this->output->lcdPrint("ROBOCO²", 0, 0);
}

void Roboco::reset()
{
        this->workflow->reset();
}

void Roboco::run()
{
        //      1º Ler o próximo destino no arquivo
        this->currentStep = this->workflow->getNextStep();
        //      1.1 Verificar qual foi a última linhas do arquivo processada
        //          1.1.1 Ler em um arquivo ROBOCO.TXT o valor gravado na primeira linha do arquivo
        //      1.2 Ler a linha do arquivo ROBOCO.TXT
        //      1.3 Guardar os valores em variáveis globais

        //      2º Deslocar-se até o destino
        this->gps->setTargetLocation(this->currentStep->latitude, this->currentStep->longitude);

        bool goToTarget = false;
        do
        {
                //      2.1 Localizar-se pelo GPS
                this->currentLocation = this->gps->getCurrentLocation();
                //      2.2 Verificar a distância e definir a velocidade de deslocamento
                //          2.2.1 Quanto mais longe do ponto, maior será a velocidade.
                //      2.3 Alinhar o bico

                float angleFactor = map(this->currentLocation->angle, -180, 180, -100, 100) / 100.0; // sera o valor do angulo mapeado entre -100 e 100
                float distanceFactor = this->gps->getDistanceToTarget();
                distanceFactor = distanceFactor > TARGET_SOFT_APPROACH_METER ? 1 : distanceFactor / TARGET_SOFT_APPROACH_METER; //  a distancia (em metros) do alvo influenciara a velocidade do motor
                int motorLeftFactor = distanceFactor - (distanceFactor * angleFactor);
                int motorRightFactor = distanceFactor + (distanceFactor * angleFactor);

                //      2.4 Avançar
                this->motorLeft->move(CLOCKWISE, map(motorLeftFactor * 100, 0, 100, 225, 255));   // move motor da esqueda
                this->motorRight->move(CLOCKWISE, map(motorRightFactor * 100, 0, 100, 225, 255)); // move o motor da direita

                //      2.5 Volte para 2.3 N vezes, onde N pode ser uma razão entre a posição atual e o destino
                //      2.6 Volte para 2.1 até chegar
                goToTarget = distanceFactor > TARGET_MINIMAL_DISTANCE_APPROACH_FACTOR;
        } while (goToTarget);

        //      3º Iniciar captura dos dados
        //      3.1 Acionar simultâneamente até o final de ambas tarefas
        //              3.1.1 Acionar esvaziamento da câmara por TEMPO_ESVAZIAMENTO_CÂMARA segundos
        //              3.1.2 Estabilizar sensor CO2 por 90 segundos
        //       3.2 Coletar dados
        //              3.1 CO2, temperaturas, pressão, altitude, etc
        //              3.2 Armazenar os dados no cartão
        //                      3.2.1 Gravar uma linha para cada capitura
        //                        TIME_STAMP, CO2, TEMP_INTERNA, PRESSÃO, ALTITUDE
        //      3.3 Repetir 3.2 a cada NTERVALO_ENTRE_CAPTURAS segundos
        //      3.4 Verificar o INTERVALO_AJUSTE_POSICIONAMENTO
        //              3.4.1 Repetir as atividades do 2º passo para reposicionamento
        //      3.5 Repetir 3.2 até esgotar o TEMPO_CAPTURA
        /*
        // fazer o delta e uma funão para estipular a velocidade
        distanceLatitude = currentStep->latitude - currentLocation->latitude;// Verificar a distância e definir a velocidade de deslocamento
         distanceLongitude = currentStep->longitude - currentLocation->longitude; //após verificar a distancia deve definir a velocidad
       
        if (currentLocation->angle < 10  &&  > 350 ) { // Alinhar o bico

        }
        
        // Outra forma de fazer para alinhar o bico
        if (currentLocation->angle !=0 &&  distanceLongitude !=0 && distanceLatitude !=0) {
                if (currentLocation->angle < 180)
                          motorLeft = motor->move;
                else
                          motorRight = motor->move;
        }*/
}

void Roboco::test()
{
        Serial.println("Testing Roboco...");
        this->gps->test();

        // this->sensors->test();

        this->motorLeft->test();
        this->motorRight->test();

}