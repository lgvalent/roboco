//Programa : Controle 2 motores DC usando Ponte H L298N
//Autora : Emica, Lucio
 
//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
  
void setup()
{
  //Define os pinos como saida
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
}


void frente(){
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 //Gira o Motor B no sentido horario
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
  
}


void tras(){
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 //Gira o Motor B no sentido horario
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
  
}

void direita(){
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 //Gira o Motor B no sentido horario
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
  
}

void esquerda(){
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 //Gira o Motor B no sentido horario
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
}

void parado(){
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 //Gira o Motor B no sentido horario
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
}

void loop(){
  int d = random(1, 6);
  int t = random(1, 4);
  switch(d){
    case 1: frente(); break;
    case 2: direita(); break;
    case 3: tras(); break;
    case 4: esquerda(); break;
    case 5: case 6: parado(); break;
  }
  delay(t*1000);
}

void loop_()
{
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 //Gira o Motor B no sentido horario
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
 
 delay(2000);
 //Para o motor A
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);

 //Para o motor B
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 delay(500);
 
 //Gira o Motor A no sentido anti-horario
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
  //Gira o Motor B no sentido anti-horario
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
 delay(2000);
 //Para o motor A
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 //Para o motor B
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 delay(500);
}
