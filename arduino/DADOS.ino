#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
char response[9];
int prevVal = LOW;
long th, tl, h, l, ppm, tpwm, p1, p2, ppm3 = 0.0;
long offset = 45.0;

void leituraSensores() { // FUNCAO QUE FAZ LEITURA DOS SENSORES DE TEMPERATURA E CO2
  led(2, 1); //acionando led verdes
  //mh_z19
  mySerial.write(cmd, 9);
  mySerial.readBytes(response, 9);
  int responseHigh = (int) response[2];
  int responseLow = (int) response[3];
  //ppm = (256*responseHigh)+responseLow;
  ppm = ((28 * responseHigh) + responseLow) + offset;
  //mh_z19
  temperatura = bmp.readTemperature();
  co2 = ppm;
  pressao = (bmp.readPressure()) / 101325;

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
  Serial.println(" m");
  Serial.println("-----------");
  led(2, 0);
}
void lcdSensores(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temp = "));
  lcd.print(bmp.readTemperature());
  lcd.println(" *C ");
  lcd.setCursor(0, 1);
  lcd.print(F("co2 = "));
  lcd.print(ppm);
  lcd.println(" , ppm ");
}
void testeSensores() { // TESTE DOS SENSORES DE TEMPERATURA E CO2
  leituraSensores();
  lcd.setCursor(0, 0);
  lcd.print(F("Temp = "));
  lcd.print(bmp.readTemperature());
  lcd.println(" *C ");
  lcd.setCursor(0, 1);
  lcd.print(F("co2 = "));
  lcd.print(ppm);
  lcd.println(" , ppm ");
}
void capturaDeDados() {
  esvaziamentoCamera(); /// ESVAZIAMENTO DA CAMERA E ESTABILIZAÇÃO DO SENSOR DE CO2
  int numeroCapturas = tempoCaptura/intervaloEntreCapturas;
  int numeroCapturasRealizadas=0;
  intervaloAjustePosicionamentoAnterior = millis();
  while(numeroCapturasRealizadas <= numeroCapturas){
        tempoMillis = millis();
        if(tempoMillis-intervaloAjustePosicionamentoAnterior > intervaloAjustePosicionamentoMilly){
          led(3,1);
          deslocarAteDestino();
          led(3,0);
          esvaziamentoCamera();
          intervaloAjustePosicionamentoAnterior = millis();
        }
        led(2,1);
        coletarDados();
        led(2,0);
        numeroCapturasRealizadas++;
        lcd.setCursor(5,1);
        lcd.print("N/CPT : ");
        lcd.print(numeroCapturasRealizadas);
        delay(1000);
  }
}

void ajusteDePosicionamento() {
  //INCIANDO ESVAZIAMENTO DA CAMERAAAA
  //AJUSTANDO POSICIONAMENTO DO ROBOCO
}
void esvaziamentoCamera() {
  lcd.clear();
  LCD(0,0,"ESVAZIANDO CAMERA");
  tempoMillis = millis();
  if (tempoEsvaziamentoCamaraMilly > 90000) {
    tempoEsvaziamentoCamaraAnterior = tempoMillis;
    while (tempoMillis - tempoEsvaziamentoCamaraAnterior < tempoEsvaziamentoCamaraMilly) { /// enquanto o tempo for menor que tempo de esvaziamento da camera
      //Acionar esvaziamento da câmara
      leituraSensores();
      tempoMillis = millis();
      lcd.setCursor(0,1);
      lcd.print(int((tempoMillis-tempoEsvaziamentoCamaraAnterior)/1000));
      lcd.print("s");
    }
  } else {
    tempoAnterior = tempoMillis;
    while (tempoMillis - tempoAnterior < 90000) { /// enquanto o tempo for menor que 90segundos
      //Acionar esvaziamento da câmara
      leituraSensores();
      tempoMillis = millis();
    }
  }
  lcd.clear();
}
void coletarDados(){
  LCD(0,0,"COLETANDO DADOS");
  tempoMillis = millis();
  intervaloEntreCapturasAnterior = tempoMillis;
  int captura = 0;
  while(captura == 0){ // enquanto eu nao capturar dadoss eu nao saio
  if (tempoMillis - intervaloEntreCapturasAnterior > intervaloEntreCapturasMilly ) { // se o tempo for maior que o intervalo entre capturas faça a captura dos dados
    leituraSensores();
    armazenarDadosNoCartao();
    intervaloEntreCapturasAnterior = tempoMillis;
    tempoMillis = millis();
    tone(A5,262,500); //DO
    captura = 1; // capturei dados
  }else{
    tempoMillis = millis();
    lcd.setCursor(0,1);
    lcd.print(int((tempoMillis - intervaloEntreCapturasAnterior)/1000));
    lcd.print("s");
    }
  }
}

