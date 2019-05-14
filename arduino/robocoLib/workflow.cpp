#include <Arduino.h>
#include <stdio.h>
#include <SD.h>
#include <EEPROM.h>

#include <workflow.h>

#define EEPROM_STEP_ADDRESS 0

Workflow::Workflow(int8_t pinSD){
  this->pinSD = pinSD;
  this->currentStepIndex = EEPROM.read(EEPROM_STEP_ADDRESS);
}

void Workflow::reset(){
  this->currentStepIndex = 0;
  EEPROM.write(EEPROM_STEP_ADDRESS, 0);
}

void Workflow::backOneStep(){
  this->currentStepIndex--;
  EEPROM.write(EEPROM_STEP_ADDRESS, this->currentStepIndex);
}

Workstep* Workflow::getNextStep(){
  File myFile;
  if ( ! SD. begin ( pinSD ) ) { 
    myFile = SD.open("roboco.txt", FILE_READ);
    if(myFile){
      return NULL;
     }
  }
  
  int linhaAtual = 0;
  while (linhaAtual != this->currentStepIndex){
    if(myFile.readStringUntil('\n').length()>0){
        linhaAtual++;
    }else{
      return NULL;
    } 
  }

  if(this->currentStepIndex != linhaAtual)
    return NULL;

  Workstep* workstep = new Workstep();
  // Ler a linha atual inteira. Se usar getvalue (precisa implementar) guardar no buffer antes.
  workstep->latitude = myFile.readStringUntil(',').toFloat();
  workstep->longitude = myFile.readStringUntil(',').toFloat();
  workstep->collectCount = myFile.readStringUntil(',').toInt();
  workstep->collectInterval = myFile.readStringUntil(',').toInt();

  myFile.close();
  
  //fazer a leitura de cada caracter e guardar a junção dos caracteres em cada variavel, exemplo '100028749' = latitude.  
  this->currentStepIndex++;
  EEPROM.write(EEPROM_STEP_ADDRESS, this->currentStepIndex); //Escrevendo na EPROMM o currentStepIndex https://www.arduino.cc/en/Tutorial/EEPROMWrite

  return workstep;

}
  

