#include <workflow.h>

#define EEPROM_STEP_ADDRESS 0

Workflow::Workflow(SDClass& sd){
  this->sd = &sd;
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
  int currentLine = 0;
  Workstep* workstep = new Workstep();
  myFile = sd->open("ROBOCO.txt", FILE_READ);

  if(!myFile){
    return NULL;
  }
  
  while (currentLine != this->currentStepIndex){
    if(myFile.readStringUntil('\n').length()>=0){
        workstep->latitude = myFile.readStringUntil(',').toDouble();
        workstep->longitude = myFile.readStringUntil(',').toDouble();
        workstep->collectCount = myFile.readStringUntil(',').toInt();
        workstep->collectInterval = myFile.readStringUntil(',').toInt();
        currentLine++;
        return workstep;
        } else{
          return NULL;
        } 
  }

  myFile.close();
  
  this->currentStepIndex++;
  EEPROM.write(EEPROM_STEP_ADDRESS, this->currentStepIndex); //Escrevendo na EPROMM o currentStepIndex https://www.arduino.cc/en/Tutorial/EEPROMWrite

  return workstep;
  
}

void Workflow::test(){

  Serial.print("Testing Workflow... ");
  Workstep* saida;

  if(this->getNextStep() == NULL){
    Serial.print("Error: Check sd card or empty file"); 
  }else{
    saida = this->getNextStep();
    Serial.print("Lat ");
    Serial.println(saida->latitude);
    Serial.print("Lon ");
    Serial.println(saida->longitude);
    Serial.print("collectCount ");
    Serial.println(saida->collectCount);
    Serial.print("collectInterval ");
    Serial.println(saida->collectInterval);

    // this->backOneStep();
    // this->reset();
  }
  
}