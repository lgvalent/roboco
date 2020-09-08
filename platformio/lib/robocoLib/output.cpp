#include <Arduino.h>
#include <output.h>

Output::Output(int8_t pinLed0, int8_t pinLed1, int8_t pinLed2){

    this->pinLed0 = pinLed0;
    this->pinLed1 = pinLed1;
    this->pinLed2 = pinLed2;
   // this->lcd = new LiquidCrystal_I2C(0x27,16,2);
    pinMode(pinLed0, OUTPUT);
    pinMode(pinLed1, OUTPUT);
    pinMode(pinLed2, OUTPUT);
    //lcd->init();
    lcd->backlight();
}

void Output::setLed0(boolean on){
        digitalWrite(pinLed0, on?HIGH:LOW);
}

void Output::setLed1 (boolean on){
        digitalWrite(pinLed1, on?HIGH:LOW);
}

void Output::setLed2(boolean on){
        digitalWrite(pinLed2, on?HIGH:LOW);
}

void Output::lcdPrint(String p,uint8_t column, uint8_t line){

        if(column>16){
                lcd->print(p);
        }else{
                lcd->setCursor(column,line);
                lcd->print(p);
        }
}

void Output::lcdClear(){
        lcd->clear();
}

/*void Output::lcdAutoScroll(boolean on){
        if(on){
                lcd->autoscroll();
        }else{
                lcd->noAutoscroll();
        }
}*/

void Output::test(){

        Serial.print("Testing Output... ");

        int const DELAY = 500;
        this->setLed0(true);
        delay(DELAY);
        this->setLed0(false);
        this->setLed1(true);
        delay(DELAY);
        this->setLed1(false);
        this->setLed2(true);
        delay(DELAY);
        this->setLed2(false);

        this->lcdPrint("Testing lcd... 1 ", 1, 0);
        this->lcdClear();
        this->lcdPrint("Testing lcd... 2 ", 1, 0);
        this->lcdClear();
}       