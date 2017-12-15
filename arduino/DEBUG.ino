
int lerEEPROM(int posicao)
{
  int x = EEPROM.read(posicao);
  return x;
}
void escEEPROM(int posicao, int valor)
{
  EEPROM.write(posicao, valor);
}
void LCD(int coluna, int linha, String msg) {
  lcd.setCursor(coluna, linha);
  lcd.print(msg);
}

void testeLeds(){
        digitalWrite(ledBranco, HIGH);
        delay(500);
        digitalWrite(ledBranco, LOW);
        digitalWrite(ledBranco1, HIGH);
        delay(500);
        digitalWrite(ledBranco1, LOW);
        digitalWrite(ledBranco2, HIGH);
        delay(500);
        digitalWrite(ledBranco2, LOW);
        digitalWrite(ledVerde, HIGH);
        delay(500);
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledVerde1, HIGH);
        delay(500);
        digitalWrite(ledVerde1, LOW);
        digitalWrite(ledVerde2, HIGH);
        delay(500);
        digitalWrite(ledVerde2, LOW);
        digitalWrite(ledVermelho, HIGH);
        delay(500);
        digitalWrite(ledVermelho, LOW);
        digitalWrite(ledVermelho1, HIGH);
        delay(500);
        digitalWrite(ledVermelho1, LOW);
        digitalWrite(ledVermelho2, HIGH);
        delay(500);
        digitalWrite(ledVermelho2, LOW);

        led(ledBranco, true);
        delay(500);
        led(ledBranco, false);
        led(ledVerde, true);
        delay(500);
        led(ledVerde, false);
        led(ledVermelho, true);
        delay(500);
        led(ledVermelho, false);
}

void testeSensores() { // TESTE DOS SENSORES DE TEMPERATURA E CO2
  leituraSensores();
  lcd.setCursor(0, 1);
  lcd.print(temperatura);
  lcd.print(" C, ");
  lcd.print(ppm);
  lcd.println(" ppm ");
}

void testeGps() {
  while (!fix) {
    Serial.println("Ativando SINAL DO GPS");
    LCD(0, 1, "Ativando GPS...");
    //localizarGps();
    delay (3000);
    fix=true; // lucio
  }
  if(fix){
    LCD(3,1,"GPS FIXADO");
    delay(3000);
  }
}

const int velocidadeTeste = 0;
void testeMotores(){
  moverFrente(velocidadeTeste);
  delay(2000);
  parar();
  moverTras(velocidadeTeste);
  delay(2000);
  parar();
  moverDireita(velocidadeTeste);
  delay(2000);
  parar();
  moverEsquerda(velocidadeTeste);
  delay(2000);
  parar();  
  moverFrente(velocidadeTeste);
  parar();  
}

void boot() {
  LCD(0,0, "Inicializando...");
  delay(1000);
  LCD(0,1, "Testando LEDs...");
  testeLeds();
  LCD(0,1, "Testando SENSORES...");
  testeSensores();
  delay(3000);
  LCD(0,1, "Testando GPS...");
  testeGps();
  LCD(0,1, "Testando SD-CARD...");
  // testeSD();
  LCD(0,1, "Testando Motores...");
  testeMotores();
  
  tone(A5, 392, 500);delay(200); //DO
  tone(A5, 330, 500);delay(200); //DO
  tone(A5, 262, 500);delay(200); //DO
}
void led(int cor, boolean ligado) {
  switch (cor) {
    case ledBranco :
        digitalWrite(ledBranco, ligado?HIGH:LOW);
        digitalWrite(ledBranco1, ligado?HIGH:LOW);
        digitalWrite(ledBranco2, ligado?HIGH:LOW);
      break;
    case ledVerde :
        digitalWrite(ledVerde, ligado?HIGH:LOW);
        //digitalWrite(ledVerde1, ligado?HIGH:LOW);
        //digitalWrite(ledVerde2, ligado?HIGH:LOW);
      break;
    case ledVermelho :
        digitalWrite(ledVermelho, ligado?HIGH:LOW);
        digitalWrite(ledVermelho1, ligado?HIGH:LOW);
        digitalWrite(ledVermelho2, ligado?HIGH:LOW);
      break;
  }
}

void transformandoTempo(){ 
  tempoEsvaziamentoCamaraMilly = tempoEsvaziamentoCamara*1000;
  intervaloEntreCapturasMilly = intervaloEntreCapturas*1000;
  intervaloAjustePosicionamentoMilly = intervaloAjustePosicionamento*1000;
  tempoCapturaMilly = tempoCaptura*1000;
}


