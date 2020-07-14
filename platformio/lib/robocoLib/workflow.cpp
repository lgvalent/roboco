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
  int currentLine = 0;

  if (!SD.begin(pinSD)){ 
    myFile = SD.open("roboco.txt", FILE_READ);
    if(!myFile){
      return NULL;
     }
  }
  
  while (currentLine != this->currentStepIndex){
    if(myFile.readStringUntil('\n').length()>0){
        currentLine++;
    }else{
      return NULL;
    } 
  }

  Workstep* workstep = new Workstep();
 
  workstep->latitude = myFile.readStringUntil(',').toFloat();
  workstep->longitude = myFile.readStringUntil(',').toFloat();
  workstep->collectCount = myFile.readStringUntil(',').toInt();
  workstep->collectInterval = myFile.readStringUntil(',').toInt();

  myFile.close();
  
  this->currentStepIndex++;
  EEPROM.write(EEPROM_STEP_ADDRESS, this->currentStepIndex); //Escrevendo na EPROMM o currentStepIndex https://www.arduino.cc/en/Tutorial/EEPROMWrite

  return workstep;
  
}

void Workflow::test(){

  Serial.print("Testing Workflow... ");

  if(this->getNextStep() == NULL){
    Serial.print("Error: Check sd card or empty file"); // 
  }else{

    // Imprime na serial os dados do currentStep
  //     workstep->latitude
  // workstep->longitude = myFile.readStringUntil(',').toFloat();
  // workstep->collectCount = myFile.readStringUntil(',').toInt();
  // workstep->collectInterval//     this->backOneStep();
  }
  
}