#include <workflow.h>

#define EEPROM_STEP_ADDRESS 0

Workflow::Workflow(SDClass& sd){
  this->sd = &sd;
  this->currentStepIndex = EEPROM.read(EEPROM_STEP_ADDRESS);
}

void Workflow::reset(){
  this->currentStepIndex = 0;
  //this->currentLine = 0;
  EEPROM.write(EEPROM_STEP_ADDRESS, 0);
}

void Workflow::backOneStep(){
  this->currentStepIndex--;
  EEPROM.write(EEPROM_STEP_ADDRESS, this->currentStepIndex);
}

Workstep* Workflow::getNextStep(){
  File myFile = sd->open("ROBOCO.txt", FILE_READ);
  int currentLine = 0;
  Workstep* workstep = new Workstep();

  if(!myFile){
    return NULL;
  }
  
  while (currentLine != this->currentStepIndex){
        myFile.readStringUntil('\n'); // Pula uma linha no arquivo
        currentLine++;
  }

  String val = myFile.readStringUntil(',');
  workstep->latitude = val.toFloat();
  workstep->longitude = myFile.readStringUntil(',').toFloat();
  workstep->collectCount = myFile.readStringUntil(',').toInt();
  workstep->collectInterval = myFile.readStringUntil('\n').toInt();

  if(myFile.readStringUntil('.').length() == 0){
    return NULL; // Acabou o arquivo
  } 
  
  // myFile.close();
   
  this->currentStepIndex++;

  EEPROM.write(EEPROM_STEP_ADDRESS, this->currentStepIndex); //Escrevendo na EPROMM o currentStepIndex https://www.arduino.cc/en/Tutorial/EEPROMWrite
  return workstep;
}

void Workflow::test(){

  Serial.print("Testing Workflow... ");
  Workstep* saida = this->getNextStep();

  if(saida == NULL){
    Serial.print("Error: Check sd card or empty file"); 
  }else{
    Serial.print("Lat ");
    Serial.println(saida->latitude,6);
    Serial.print("Lon ");
    Serial.println(saida->longitude,6);
    Serial.print("collectCount ");
    Serial.println(saida->collectCount);
    Serial.print("collectInterval ");
    Serial.println(saida->collectInterval);

    //this->backOneStep();
    //this->reset();
  }
  
}