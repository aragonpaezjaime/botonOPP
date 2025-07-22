#include <Arduino.h>
#include "boton.h"
boton boton1(14,POSITIVO);
void setup() {
  Serial.begin(115200);
  pinMode(13,OUTPUT);
}

void loop() {
  if (boton1.checar()) {
    //Serial.println("presionado");
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}
