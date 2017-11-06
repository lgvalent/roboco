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
void teste() {
  testeSensores();
  localizarGps();
  testeGps();
  testeSD();
}
void led(int cor, int intensidade) {
  switch (cor) {
    case '1' :
      if (intensidade == 1) {
        digitalWrite(ledBranco, HIGH);
        digitalWrite(ledBranco1, HIGH);
        digitalWrite(ledBranco2, HIGH);
      }
      else {
        digitalWrite(ledBranco, LOW);
        digitalWrite(ledBranco1, LOW);
        digitalWrite(ledBranco2, LOW);
      }
      break;
    case '2' :
      if (intensidade == 1) {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledVerde1, HIGH);
        digitalWrite(ledVerde2, HIGH);
      } else {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledVerde1, LOW);
        digitalWrite(ledVerde2, LOW);
      }
      break;
    case '3' :
      if (intensidade == 1) {
        digitalWrite(ledVermelho, HIGH);
        digitalWrite(ledVermelho1, HIGH);
        digitalWrite(ledVermelho2, HIGH);
      } else {
        digitalWrite(ledVermelho, LOW);
        digitalWrite(ledVermelho1, LOW);
        digitalWrite(ledVermelho2, LOW);
      }
      break;
  }
}
void transformandoTempo(){
tempoEsvaziamentoCamaraMilly = tempoEsvaziamentoCamara*1000;
intervaloEntreCapturasMilly = intervaloEntreCapturas*1000;
intervaloAjustePosicionamentoMilly = intervaloAjustePosicionamento*1000;
tempoCapturaMilly = tempoCaptura*1000;
}


