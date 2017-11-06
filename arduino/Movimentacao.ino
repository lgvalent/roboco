void deslocarAteDestino(){
  lcd.clear();
  LCD(0,0,"DESLOCANDO");
  delay(10000);
 /*while(distancia > 0.3){
 localizarGps();
 distanciaAoPonto();
 moverFrente(velocidade);
 delay(2000);
 }*/
 lcd.clear();
}
float distanciaAoPonto(){
  float lat1 = latitudeAtual * 3.1415927 / 180;
  float lon1 = longitudeAtual * 3.1415927 / 180;
  float lat2 = latitude * 3.1415927 / 180;
  float lon2 = longitude * 3.1415927 / 180;
  float Raio_da_terra = 6371000; // km
  float dLat = (lat2-lat1); //diferença das latitudes dos pontos em radianos
  float dLon = (lon2-lon1); //diferença das longitudes dos pontos em radianos
  float a = sin(dLat/2) * sin(dLat/2) + cos(lat1) * cos(lat2) * sin(dLon/2) * sin(dLon/2);
  float c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  distancia = Raio_da_terra * c; //distancia em metros
  Serial.println(distancia,6);
  alinharBico(dLon,dLat);
  velocidadeDeDeslocamento();
}
int velocidadeDeDeslocamento(){
  if(distancia >= 10){
    velocidade = 255;
  }
  if(distancia >= 5 && distancia <10){
    velocidade = 200;
  }
  if(distancia >= 2 && distancia < 5){
    velocidade = 180;
  }
  if(distancia < 2){
    velocidade = 150;
  }
}
void alinharBico(float Long,float Lati){
  double anguloDistancia = atan(Lati/Long);
  Serial.println(anguloDistancia);
}

