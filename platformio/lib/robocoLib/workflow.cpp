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
  Serial.println("Começo do getNextStep - workflow");
  File myFile = sd->open("ROBOCO.txt", FILE_READ);
  int currentLine = 0;
  Workstep* workstep = new Workstep();

  if(!myFile){
    return NULL;
  }
  
  while (currentLine != this->currentStepIndex){
        Serial.println("while - workflow");
        myFile.readStringUntil('\n'); // Pula uma linha no arquivo
        currentLine++;
  }

  Serial.print("currentLine do workflow: ");
  Serial.println(currentLine);
  String val = myFile.readStringUntil(',');
  if(val.length() == 0) return NULL; // Acabou o arquivo
  workstep->latitude = val.toDouble();
  
  workstep->longitude = myFile.readStringUntil(',').toDouble();
  workstep->collectCount = myFile.readStringUntil(',').toInt();
  workstep->collectInterval = myFile.readStringUntil('\n').toInt();

  myFile.close();
  
  Serial.print("currentStepIndex sem ++: ");
  Serial.println(this->currentStepIndex);
  this->currentStepIndex++;
  Serial.print("currentStepIndex com ++: ");
  Serial.println(this->currentStepIndex);

  EEPROM.write(EEPROM_STEP_ADDRESS, this->currentStepIndex); //Escrevendo na EPROMM o currentStepIndex https://www.arduino.cc/en/Tutorial/EEPROMWrite
  Serial.println("Final do getNextStep - workflow");
  return workstep;
}

void Workflow::test(){

  Serial.print("Testing Workflow... ");
  Workstep* saida = this->getNextStep();

  if(saida == NULL){
    Serial.print("Error: Check sd card or empty file"); 
  }else{
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