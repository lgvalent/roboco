#include <Arduino.h>
#include <roboco.h>


Roboco::RobocoState Roboco::state = GET_TARGET;

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

void Roboco::setup(){

  // this->sensors->stabilizationOfSensors(); //start sensores, fica por aqui por 2s (quando utilizamos esse metodo ele fica resetando o metodo setup, ARRUMAR ISSO)

  this->originLocation = this->gps->getCurrentLocation(); // salvando a origem do gps ao ligar o robo
  Serial.print("latitude origem:");
  Serial.println(this->originLocation->latitude); // contagem da coleta ATE ACABAR O tempo
  Serial.print("longitude origem:");
  Serial.println(this->originLocation->longitude);

 //this->output->lcdPrint("ROBOCO²", 0, 0);
 }

void Roboco::reset(){
  this->workflow->reset();
}

void Roboco::run(){
  
  switch (this->state){     // Máquina de estado
    case GET_TARGET:        // Recebe o alvo 
      if(this->getTarget()!= NULL){
        this->state = GO_TARGET;
      } else{
        this->state = RETURN_ORIGIN;
      }
    break;
  
    case GO_TARGET:         // Vai para o alvo e controla a velocidade dos motores (perto=diminiu vel. /// longe=aumenta vel.)
          this->goTarget();
          this->state = COLLECT_DATA;
    break;
  
    case COLLECT_DATA:      // Coleta os dados dos sensores e salva no cartão de memória
      this->motorLeft->stop();
      this->motorRight->stop();							     
      this->collectData();
      this->state = GET_TARGET;
    break;
  
    case RETURN_ORIGIN:     // Volta para o ponto inicial
      Serial.println("passei no case RETURN_ORIGIN");
      this->returnOrigin();
      this->state = FINISH;
    break;
  
    case INIT_SENSORS:      
      // Inicializa os sensores, liga eles quando estiver chegando perto do ponto (implementar?)
    break;

    case FINISH:
      //Desligar o robo (implementar)
      Serial.println("FINALIZADO");
      this->motorLeft->stop();
      this->motorRight->stop();
      while (1){
      Serial.println("missão cumprida");
      break;
      }
  }
}

Location* Roboco::getTarget(){
  //      1º Ler o próximo destino no arquivo
  //      1.1 Verificar qual foi a última linhas do arquivo processada
  //          1.1.1 Ler em um arquivo ROBOCO.TXT o valor gravado na primeira linha do arquivo
  //      1.2 Ler a linha do arquivo ROBOCO.TXT
  //      1.3 Guardar os valores em variáveis globais/EEPROM_STEP_ADDRESS

  //      2º Deslocar-se até o destino
  //      2.1 Localizar-se pelo GPS
  //      2.2 Verificar a distância e definir a velocidade de deslocamento
  //          2.2.1 Quanto mais longe do ponto, maior será a velocidade.
  //      2.3 Alinhar o bico // Sendo feito no angulo
  //      2.4 Avançar
  //      2.5 Volte para 2.3 x(distamcia) vezes, onde x pode ser uma razão entre a posição atual e o destino
  //      2.6 Volte para 2.1 até chegar
    Serial.println("ESTOU no getTarget");
    this->currentStep = this->workflow->getNextStep();
    if(this->currentStep != NULL){
      Serial.println("passei no if do getTarget");
      this->gps->setTargetLocation(this->currentStep->latitude, this->currentStep->longitude);
      //this->gps->setTargetLocation(-24.034241, -52.362065); // teste com alvo fixo. Endereço da esquina da rua da Bruna de Campo Mourão.

    } else {
      Serial.println("passei no else do getTarget");
      return NULL;
    }
  
  return this->gps->getTargetLocation();
}

void Roboco::goTarget(){
  float angleFactor;
  float distanceFactor, distanceToTarget;

  do{
    this->currentLocation = this->gps->getCurrentLocation();
    this->currentDataTime = this->gps->getCurrentDateTime();

    angleFactor = map(this->currentLocation->angle, -180, 180, -100, 100) / 100.0; // sera o valor do angulo mapeado entre -100 e 100
    Serial.println(angleFactor);
    // map(valor, deMenor, deMaior, paraMenor, paraMaior);
    distanceToTarget = this->gps->getDistanceToTarget();
    // Serial.print ("distanceFactor 1: ");
    // Serial.println (distanceFactor);
    distanceFactor = distanceToTarget > TARGET_SOFT_APPROACH_METER ? 1 : distanceToTarget / TARGET_SOFT_APPROACH_METER; //  a distancia (em metros) do alvo influenciara a velocidade do motor
    // Serial.print ("distanceFactor 2: ");
    // Serial.println (distanceFactor);
    
    float motorLeftFactor = distanceFactor + (distanceFactor * angleFactor);
    float motorRightFactor = distanceFactor + (distanceFactor * angleFactor);

    this->motorLeft->move(CLOCKWISE, map(motorLeftFactor * 100, 0, 100, 225, 255));
    this->motorRight->move(CLOCKWISE, map(motorRightFactor * 100, 0, 100, 225, 255));
 
  }while(distanceToTarget > TARGET_MINIMAL_DISTANCE_APPROACH_METER);
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

	Serial.print("COLLECT COUNT:");
  Serial.println(this->currentStep->collectCount); // contagem da coleta ATE ACABAR O tempo
  Serial.print("COLLECT INTERVAL:");
  Serial.println(this->currentStep->collectInterval);
  int conta = (this->currentStep->collectInterval)/(this->currentStep->collectCount);
  Serial.println(conta);

     unsigned long start = millis();
     do
     {
       this->gps->getCurrentLocation();
       this->gps->getCurrentDateTime();

     } while (millis() - start < conta);

       for (int i = 0; i < this->currentStep->collectCount; i++)
       {
         this->collectRegister->open();
         this->collectRegister->write(this->gps->getCurrentLocation(), this->gps->getCurrentDateTime(), this->sensors);
         this->collectRegister->close();
       }
}

void Roboco::origin(){

  this->originLocation = this->gps->getCurrentLocation(); // salvando a origem do gps ao ligar o robo
  Serial.print("latitude origem:");
  Serial.println(this->originLocation->latitude); // contagem da coleta ATE ACABAR O tempo
  Serial.print("longitude origem:");
  Serial.println(this->originLocation->longitude);

}

void Roboco::returnOrigin(){
  //      4 voltar para lugar de origem
  //      4.1 define as coordenadas de origem como proximo alvo do gps
  //this->gps->setTargetLocation(this->originLocation->latitude, this->originLocation->longitude); //OBS:sobrescrevendo valores (assim ele coloca o alvo como a origem e não grava a primeira coordenada)
  this->gps->setTargetLocation(-24.034236, -52.361972); // testamos com parametros fixos e ele retorna para a origem certinho.
  this->goTarget();
  }

void Roboco::initSensors(){
 // implementar se for usar o estado INIT_SENSORS
}

void Roboco::calibrateSensors(){
  // Controla a calibração (20 min.) periodica dos sensores, não tem necessidade de ser executada toda a vez que liga o robo
  this->sensors->calibrate();
}

void Roboco::test(){
  Serial.println("Testing Roboco...");
  //this->gps->test();
  this->sensors->test();
  // this->output->test();
  // this->collectRegister->test(); 
  //this->workflow->test();
  //this->motorLeft->test();
  //this->motorRight->test();
}
