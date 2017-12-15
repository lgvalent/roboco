void estacionario () {
  lcd.clear();
  LCD(0, 0, "INICIANDO MODO");
  LCD(0, 1, "ESTACIONARIO");
  delay(3000);
  localizarGps();
  lerProximoDestino(lerEEPROM(2));
  latitude = latitudeAtual;
  longitude = longitudeAtual;
  capturaDeDados();
  tone(A5, 262, 2000); //DO
  delay(3000);
  /*while(1){
    lcd.clear();
    LCD(0,0,"PROCESSO ");
    LCD(0,1,"TERMINADO");
    delay(10000000);
    }*/
}
void movimentacao () {
  LCD(0, 0, "INICIANDO MODO");
  LCD(0, 0, "MOVIMENTACAO");
  delay(3000);
  int x = 0;
  lerProximoDestino(lerEEPROM(2));
  deslocarAteDestino();
  capturaDeDados();
  tone(A5, 262, 2000); //DO
  delay(3000);
  /*while(1){
    lcd.clear();
    LCD(0,0,"PROCESSO ");
    LCD(0,1,"TERMINADO");
    delay(10000000);
    }*/
}

const int SLOW = 3000;
const int NORMAL = 2000;
const int FAST = 1000;
const int FASTEST = 500;
const int vel = 500;

void randomCapture(){
  // Acende os LEDs
  digitalWrite(ledVerde, HIGH);
  lcd.clear();
  LCD(2,0,"Capturando...");
  // Escreve na TELA CAPTURANDO....
  leituraSensores();
  lcd.setCursor(0,1);lcd.print("Temp: ");lcd.print(temperatura); lcd.print(" C" );
  tone(A5, 440, 200); delay(2000);
  lcd.setCursor(0,1);lcd.print("Pressao: ");lcd.print(pressao);
  tone(A5, 440, 200); delay(2000);
  lcd.setCursor(0,1);lcd.print("CO2: ");lcd.print(co2);lcd.print(" ppm ");
  tone(A5, 440, 200); delay(2000);
  lcd.setCursor(0,1);lcd.print("Salvando SD...");
  delay(10000); 
  
  
}

void randomMove() {

  while (true) {
    int randMove = random(0, 6);
    int randSpeed = random(1, 6);
    int ledControl;
    Serial.print(randMove);
    Serial.print(":");
    Serial.println(randSpeed);
    // ESCREVE NA TELA MOVENDO-SE
    lcd.clear(); lcd.print("<<<Movendo-se>>>");
    switch (randMove) {
      case 0: moverFrente(vel); ledControl = ledBranco; randSpeed *=2; break;
      case 1: moverTras(vel); ledControl = ledBranco; break;
      case 2: moverEsquerda(vel); ledControl = ledVermelho; break;
      case 3: moverDireita(vel); ledControl = ledVermelho; break;
      case 4: parar(); ledControl = 0; break;
      case 5: parar(); randomCapture(); ledControl = ledVerde; break;
    }
    led(ledControl, true);
    delay(randSpeed * vel);
    led(ledControl, false);
  }
}

void apresentacao() {
  randomMove();

  return;

  int randNumero = random(0, 8);
  switch (randNumero) {
    case 0 :
      lcd.clear();
      LCD(0, 0, "EXECUCAO : 0");
      delay(2000);
      led(3, 1); // acionando led vermelho
      moverFrente(255);
      delay(1000);
      moverTras(255);
      delay(200);
      led(3, 0); // acionando led vermelho
      parar();
      break;
    case 1 :
      lcd.clear();
      LCD(0, 0, "EXECUCAO : 1");
      delay(2000);
      led(3, 1); // acionando led vermelho
      moverFrente(255);
      delay(500);
      led(3, 0); // acionando led vermelho
      parar();
      break;
    case 2 :
      lcd.clear();
      LCD(0, 0, "EXECUCAO : 2");
      delay(2000);
      led(2, 1); // acionando led verde
      leituraSensores();
      delay(5000);
      led(2, 0); // apaga led verde
      break;
    case 3 :
      lcd.clear();
      LCD(0, 0, "EXECUCAO : 3");
      delay(2000);
      led(2, 1); // acionando led verde
      for (int i = 0; i < 5; i++) {
        leituraSensores();
        delay(5000);
        led(2, 0); // apaga led verde
      }
      break;
    case 4 :
      lcd.clear();
      LCD(0, 0, "EXECUCAO : 4");
      delay(2000);
      led(3, 1); //acende led vermelho
      moverEsquerda(255);
      delay(500);
      leituraSensores();
      delay(5000);
      led(3, 1); // apaa led vermelho
      break;
    case 5 :
      lcd.clear();
      LCD(0, 0, "EXECUCAO : 5");
      delay(2000);
      led(3, 1); // acende led vermelho
      moverDireita(255);
      delay(500);
      moverFrente(255);
      delay(500);
      led(3, 0); // apaga led vermelho
      led(2, 1); // acende led verde
      leituraSensores();
      led(2, 0); // apaga led verde
      delay(5000);
      break;
    case 6 :
      lcd.clear();
      LCD(0, 0, "EXECUCAO : 6");
      delay(2000);
      estacionario();
      break;
    case 7 :
      lcd.clear();
      LCD(0, 0, "EXECUCAO : 7");
      delay(2000);
      movimentacao();
  }
}

