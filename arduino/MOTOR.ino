#include <Arduino.h>


void moverFrente(int vel) {
  led(3,1); // acionando led vermelho
  motor.M1move(vel, ANTI_HORARIO);
  motor.M2move(vel, HORARIO);
  Serial.println("Frente");
}
void moverTras(int vel) {
  motor.M1move(vel, HORARIO);
  motor.M2move(vel, ANTI_HORARIO);
  Serial.println("tras");
}
void moverDireita(int vel) {
  motor.M1move(vel, HORARIO);
  motor.M2move(vel, HORARIO);
  Serial.println("Direita");
}
void moverEsquerda(int vel) {
  motor.M1move(vel, ANTI_HORARIO);
  motor.M2move(vel, ANTI_HORARIO);
  Serial.println("Esquerda");
}
void parar() {
  motor.M1parar(); //Para o motor1
  motor.M2parar(); //Para o motor2
  Serial.println("parar");

  // GAMBI
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
