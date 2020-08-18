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
  //calibração dos sensores e GPS
  //salvando a origim
  this->output->lcdPrint("ROBOCO²", 0, 0);
}

void Roboco::reset()
{
  this->workflow->reset();
}

void Roboco::run()
{
  switch (this->state)
  {
  case SET_TARGET:
    this->SetTarget();
  break;
  
  case GO_TARGET:
    this->runTarget();
    this->state = COLLECT_DATA;
  break;
  
  case COLLECT_DATA:
    this->collectData();
    this->state = GO_TARGET;
  break;
  
  case RETURN_ORIGIN:
    this->runBackToOrigin()
    this->runTaget();
    this->state = FINISH;
    break;
  
  case INIT_SENSORS:
    this->initSensors();
  break;
  case FINISH:
    //terminou e esta na origem
  break;
  default:
    break;
  }
}

boolean Roboco::stabilizationOfSensors()
{
  //Estabilizar sensores por 120 segundos // iniciar timer 120segundos
  //get valor do sensores a cada 1 Segundo //iniciar timer de 1segundo
  boolean stabilization = false;
  boolean getDate = false;
  boolean calcMedia = false;
  timer(120s){
    stabilization = true;
  }
  timer(1s){
    getDate = true;
  }

  /// puxar enum dos sensores
  String arrayAtual[sensors->getSize()];
  String arrayMedio[sensors->getSize()];
  while(!stabilzation){ //enquanto tempo for menor 120segundos fica ai...
    if(getDate){
      for(int i =0; i<sensors->getSize();i++ ){}
        arrayAtual[i] = sensors->getSensor(i)->read(); // 4 é o CO2
      }
      getDate = false;
      calcMedia = true;
    }// interrupção de 1 segundo
    //paroooo
    //volto
    if(calcMedia){
      for(int i = 0; i<sensors->getSize(); i++){
        arrayMedio[i] = (arrayMedio[i]+arrayAtual[i])/2//montar função media movel....
      }
      calcMedia = false;
    }
    delay(1);
  }
  //passou 120segundos
  // apresentar valores dos sensores e confirmar seu funcionamento/ mais a temperatura no local estava 30 graus
  // lcd sensor de co2 ta com 400 confirma? 
  // lcd sensor de temp ta com 35 graus? confirma?
  // lcd sensor de luminosidade valor 1024? ta escuro? não, quer continuar ou interromper?
}

void Roboco::collectData()
{

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

  do
  {

    collectRegister->write(this->gps->getCurrentLocation(), this->gps->getCurrentDateTime(), this->sensors);
  } while (millis() - start < this->currentStep->collectCount);

  collectRegister->close();
}

void Roboco::runTarget()
{
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

  do
  {
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

  } while (goToTarget);
}

void Roboco::runBackToOrigin()
{
  //      4 voltar para lugar de origem
  //      4.1 define as coordenadas de origem como proximo alvo do gps
  //      4.1  GO_TARGET
}

void Roboco::test()
{

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

void Roboco::calibrateSensors()
{
  this->sensors->calibrate();
}