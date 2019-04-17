#include <Arduino.h>
#include <stdio.h>
#include "workflow.h"
#include <SD.h>
#include <EEPROM.h>
#define adress 0

//passar todas as variaveis pro ingles.

Workflow::Worflow (int8_t pinSD){
  this->pinSD = pinSD;
  byte value;
  byte currentStopIndex;
  this->currentStopIndex = EEPROM.read(adress);
}

Workstep* Workflow::getNextStep(){
  Workstep* workstep = new Workstep;
  int linhaAtual = 0;
  int readLine = 0;
  
  if ( ! SD. begin ( pinSD ) ) { 
    File myFile;
    myFile = SD.open("roboco.txt", "r");
    if(myFile == NULL){
      return NULL;
     }
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
      this->longitude = getValue (buffer, ',', 1 ). toFloat ();
      this->collectInterval = getValue (buffer, ',', 5 ). toInt ();
      this->collectCount = getValue (buffer, ',', 5). toInt ();
      //fazer a leitura de cada caracter e guardar a junção dos caracteres em cada variavel, exemplo '100028749' = latitude.
      this->longitude = longitude;
      this->collectCount = collectCount;
      this->collectInterval = collectInterval;
        
   }
   this->currentStopIndex ++;
   EEPROM.write(address, currentStopIndex); //Escrevendo na EPROMM o currentStopIndex23 https://www.arduino.cc/en/Tutorial/EEPROMWrite
   address = address + 1;
   if(address == EEPROM.length()){
      address = 0;
   }
   ++ address & = EEPROM.length() -1; //impedimento da memória EEPROM estourar.
}

fclose(arq);
 

 fclose(arq);
}
  

