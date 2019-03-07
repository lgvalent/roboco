#include <Arduino.h>
#include <stdio.h>
#include "workflow.h"
#include <SD.h>

Workstep* Workflow::getNextStep(){
  file meuArquivo;
 meuArquivo = SD.open("roboco.txt", "r");
 if(meuArquivo == NULL)
     return NULL;
 else
     while( (ch=fgetc(arq))!= EOF )
     putchar(ch);
   
  
  
  
 fclose(arq);
}
  

