#include<Arduino.h>
#include "gps.h"

#define GPSECHO  true

void Gps::testeGps(){
 Serial.begin(115200);
  while (!Serial);
  delay(1000);
  Serial.println("Adafruit GPS logging start test!");

  // 9600 NMEA is the default baud rate for MTK - some use 4800
  GPS.begin(9600);
  
  // You can adjust which sentences to have the module emit, below
  // Default is RMC + GGA
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // Default is 1 Hz update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);
  delay(500);
  Serial.print("\nSTARTING LOGGING....");
  if (GPS.LOCUS_StartLogger())
    Serial.println(" STARTED!");
  else
    Serial.println(" no response :(");
  delay(1000);
}
void Gps::useInterrupt(boolean v){
    if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
    } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
    }
}
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO && c) {
#ifdef UDR0
    UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#else
    Serial.write(c);
#endif
  }
}