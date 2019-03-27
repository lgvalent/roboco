#include <Arduino.h>
#include <stdio.h>
#include "workflow.h"
#include <SD.h>

Workflow::Worflow (int8_t pinSD){
  this->pinSD = pinSD;
}

Workstep* Workflow::getNextStep(){
  Workstep* workstep = new Workstep;
  this->currentStopIndex = -1;
  int linhaAtual = 0;
  int readLine = 0;
  Serial.begin(9600);
  while (!Serial) {
  }
  
  if ( ! SD. begin ( pinSD ) ) { //Como deixar a pinagem genérica?
  lcd. claro ();
  LCD ( 0 , 0 , "Inicialização falhou." );
  while ( 1 ) ; 
  } 
 LCD ( 0 , 0 , "Inicialização feita." );
  
 File myFile;
 myFile = SD.open("roboco.txt", "r");
 if(myFile == NULL){
     return NULL;
 }
  
  while ( ){//terminar
  }
  
 else{
   if (this->currentStopIndex == linhaAtual) {
      this->latitude = latitude;
      this->longitude = longitude;
      this->collectCount = collectCount;
      this->collectInterval = collectInterval;
      latitude = getValue (buffer, ' , ' , 0 ). toFloat ();
      longitude = getValue (buffer, ' , ' , 1 ). toFloat ();
      collectInterval = getValue (buffer, ' , ' , 5 ). toInt ();
      collectCount = getValue (buffer, ', ', 5). toInt ();
   }
 readLine ++;
 }
//while( (ch=fgetc(arq))!= EOF ) //leitura do arquivo caracter por caracter
//putchar(ch);
   
 fclose(arq);
}
  

