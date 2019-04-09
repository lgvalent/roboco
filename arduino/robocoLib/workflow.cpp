#include <Arduino.h>
#include <stdio.h>
#include "workflow.h"
#include <SD.h>


//passar todas as variaveis pro ingles.

Workflow::Worflow (int8_t pinSD){
  this->pinSD = pinSD;
  this->currentStopIndex = 0; //verificar o registrador do arduino em que passo parou (flash memory).
}

Workstep* Workflow::getNextStep(){
  Workstep* workstep = new Workstep;
  int linhaAtual = 0;
  int readLine = 0;
  Serial.begin(9600);
  while (!Serial) {
  } // Limitar o laço para detectar erros no sensor.
  
  if ( ! SD. begin ( pinSD ) ) { //Como deixar a pinagem genérica?

 
 File myFile;
 myFile = SD.open("roboco.txt", "r");
 if(myFile == NULL){
     return NULL;
 }
  
  while ( linhaAtual != currentStopIndex){
    while ( (ch=myFile.read(arq))!= EOF) 
          if(ch=='/n'){ 
            linhaAtual++;
            break;
          }
  }
  //ler a linha atual inteira.   se usar getvalue (precisa implementar) guardar no buffer antes.
    
      (this->currentStopIndex == linhaAtual) {
      
      this->latitude = getValue (buffer, ',', 0 ). toFloat (); //arrumar os outros igual a esse.
      longitude = getValue (buffer, ',', 1 ). toFloat ();
      collectInterval = getValue (buffer, ',', 5 ). toInt ();
      collectCount = getValue (buffer, ',', 5). toInt ();
      //fazer a leitura de cada caracter e guardar a junção dos caracteres em cada variavel, exemplo '100028749' = latitude.
      this->longitude = longitude;
      this->collectCount = collectCount;
      this->collectInterval = collectInterval;
        
   }
 readLine ++;
 }

 fclose(arq);
}
  

