#ifndef ROBOCO_H
#define ROBOCO_H
#include <collectRegister.h>
#include <gps.h>
#include <motor.h>
#include <output.h>
#include <sensors.h>
#include <workflow.h>

class Roboco{

  public: 
    const int TARGET_SOFT_APPROACH_METER = 3;
    const float TARGET_MINIMAL_DISTANCE_APPROACH_METER = 2; // metros
    enum RobocoStates{READING_NEXT_STEP, READING_CURRENT_LOCATION, KEEPING_TRACK, READING_SENSORS};

  private:
    Sensors* sensors;
    Output* output;
    GPS* gps;
    CollectRegister* collectRegister;
    Workflow* workflow;
    Motor* motorLeft,* motorRight;
    Workstep* currentStep;
    Location* currentLocation;
    Location* originLocation;
    DateTime* currentDataTime;
    
  public:
    static enum RobocoState{GET_TARGET = 0, GO_TARGET, INIT_SENSORS, COLLECT_DATA, RETURN_ORIGIN, FINISH} state;
    static enum RobocoSensors{LUMINOSITY=0, PRESSURE=1, ALTITUDE=2,TEMPERATURE=3, CO2=4, CH4=5, COMPASS=6, _COUNT} ROBOCO_SENSORS;
    Roboco(Sensors* sensors, Output* output, GPS* gps, CollectRegister* collectRegister, Workflow* workflow, Motor* left, Motor* right);
    void setup(); 
    void origin();
    void reset(); 
    void run(); // estado central da maquina de estados
    Location* getTarget(); 
    void goTarget(); // ir ao local indicado
    void collectData(); // get dados dos sensores
    void returnOrigin();  // voltar para o lugar de origem
    void initSensors(); // inicializa os sensores
    void calibrateSensors(); // Controla a calibração periodica dos sensores, pois não tem necessidade de ser executada toda a vez que liga o robo
    void test(); 
};
#endif

// 1º Ler o próximo destino no arquivo
//    1.1 Verificar qual foi a última linhas do arquivo processada
//        1.1.1 Ler em um arquivo ROBOCO.TXT o valor gravado na primeira linha do arquivo
//    1.2 Ler a linha do arquivo ROBOCO.TXT
//    1.3 Guardar os valores em variáveis globais

// 2º Deslocar-se até o destino
//    2.1 Localizar-se pelo GPS
//    2.2 Verificar a distância e definir a velocidade de deslocamento
//        2.2.1 Quanto mais longe do ponto, maior será a velocidade.
//    2.3 Alinhar o bico
//    2.4 Avançar
//    2.5 Volte para 2.3 N vezes, onde N pode ser uma razão entre a posição atual e o destino
//    2.6 Volte para 2.1 até chegar

// 3º Iniciar captura dos dados
//    3.1 Acionar simultâneamente até o final de ambas tarefas
//        3.1.1 Acionar esvaziamento da câmara por TEMPO_ESVAZIAMENTO_CÂMARA segundos
//        3.1.2 Estabilizar sensor CO2 por 90 segundos
//    3.2 Coletar dados
//        3.1 CO2, temperaturas, pressão, altitude, etc
//        3.2 Armazenar os dados no cartão
//            3.2.1 Gravar uma linha para cada capitura
//                  TIME_STAMP, CO2, TEMP_INTERNA, PRESSÃO, ALTITUDE
//    3.3 Repetir 3.2 a cada NTERVALO_ENTRE_CAPTURAS segundos
//    3.4 Verificar o INTERVALO_AJUSTE_POSICIONAMENTO
//        3.4.1 Repetir as atividades do 2º passo para reposicionamento
//    3.5 Repetir 3.2 até esgotar o TEMPO_CAPTURA