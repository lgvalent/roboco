void lerProximoDestino(int linhaAtual) {

  lcd.clear();
  LCD(0,0,"LENDO DADOS");
  printFile = SD.open("texto.txt");

  if (!printFile) {
    Serial.print("The text file cannot be opened");
    while (1);
  }
  int readLine = 0;
  while (printFile.available()) {
    buffer = printFile.readStringUntil('\n');
    Serial.println(buffer); //Printing for debugging purpose
    //
    if (readLine == linhaAtual) {
      latitude = getValue(buffer, ',', 0).toFloat();
      longitude = getValue(buffer, ',', 1).toFloat();
      tempoEsvaziamentoCamara = getValue(buffer, ',', 2).toInt();
      intervaloEntreCapturas = getValue(buffer, ',' , 3).toInt();
      intervaloAjustePosicionamento = getValue(buffer, ',' , 4).toInt();
      tempoCaptura = getValue(buffer, ',' , 5).toInt();
      Serial.println();
      Serial.println();
      Serial.print("Hora: "); Serial.print(GPS.hour, DEC); Serial.print(':'); Serial.print(GPS.minute, DEC); Serial.print(':'); Serial.print(GPS.seconds, DEC);
      Serial.print(", Date: "); Serial.print(GPS.day, DEC); Serial.print('/');  Serial.print(GPS.month, DEC); Serial.print("/20");  Serial.print(GPS.year, DEC);
      Serial.print(", Latitude : "); Serial.print(latitudeAtual);
      Serial.print(", Longitude : "); Serial.print(longitudeAtual);
      Serial.print(", Altitude : "); Serial.print(Altitude);
      Serial.print(", CO2 : ");  Serial.print(co2); Serial.print(" ppm");
      Serial.print(", Temperatura : "); Serial.print(temperatura);
      Serial.print(", pressao : " ); Serial.print(pressao); Serial.print(" atm");
      Serial.print(", Tempo de Esvaziamento da camera : "); Serial.print(tempoEsvaziamentoCamara);
      Serial.print(", intervalo Entre Capturas : "); Serial.print(intervaloEntreCapturas);
      Serial.print(",intervalo Ajuste Posicionamento : "); Serial.print(intervaloAjustePosicionamento);
      Serial.print(",tempo Captura : "); Serial.println(tempoCaptura);
      transformandoTempo();
    }
    readLine++;
  }
  if(latitude == 0){
    linhaFinal = 1;
  }
  printFile.close();
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void testeSD() {
  lcd.clear();
  while (!SD.begin(53)) {
    Serial.print("The SD card cannot be found");
    LCD(0, 0, "CARTAO SD NAO");
    LCD(0, 1, "ENCONTRADO");
  }
  lcd.clear();
  LCD(4, 0, "TESTE SD");
  LCD(4, 1, "CONCLUIDO");
  delay(5000);
}
void armazenarDadosNoCartao() {  
  arquivoTXT = SD.open ("roboco.txt", FILE_WRITE);
  lcd.clear();
  LCD(0,0,"ARMAZENANDO");
  arquivoTXT.print("Hora: "); arquivoTXT.print(GPS.hour, DEC); arquivoTXT.print(':'); arquivoTXT.print(GPS.minute, DEC); arquivoTXT.print(':'); arquivoTXT.print(GPS.seconds, DEC); 
  arquivoTXT.print(", Date: "); arquivoTXT.print(GPS.day, DEC); arquivoTXT.print('/');  arquivoTXT.print(GPS.month, DEC); arquivoTXT.print("/20");  arquivoTXT.print(GPS.year, DEC);
  arquivoTXT.print(", Latitude : "); arquivoTXT.print(latitudeAtual);
  arquivoTXT.print(", Longitude : "); arquivoTXT.print(longitudeAtual);
  arquivoTXT.print(", Altitude : "); arquivoTXT.print(Altitude);
  arquivoTXT.print(", CO2 : ");  arquivoTXT.print(co2); arquivoTXT.print(" ppm");
  arquivoTXT.print(", Temperatura : "); arquivoTXT.print(temperatura);
  arquivoTXT.print(", pressao : " ); arquivoTXT.print(pressao); arquivoTXT.print(" atm");
  arquivoTXT.print(", Tempo de Esvaziamento da camera : ");arquivoTXT.print(tempoEsvaziamentoCamara);
  arquivoTXT.print(", intervalo Entre Capturas : "); arquivoTXT.print(intervaloEntreCapturas);
  arquivoTXT.print(",intervalo Ajuste Posicionamento : "); arquivoTXT.print(intervaloAjustePosicionamento);
  arquivoTXT.print(",tempo Captura : "); arquivoTXT.println(tempoCaptura);
  arquivoTXT.close();
}

