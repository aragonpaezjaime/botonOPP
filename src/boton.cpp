#include "boton.h"
#include <Arduino.h>

boton::boton(int _pin, unsigned int _modo) {
    pin = _pin;
    modo = _modo;
    if (modo) {
        pinMode(pin, INPUT_PULLUP);
    }else{
        pinMode(pin, INPUT_PULLDOWN );
    }
}

int boton::checar(){
    if (modo && !digitalRead(pin)) {
        presionado = true;
        return 1;
    }else if (!modo && digitalRead(pin)) {
        presionado = true;
        return 1;
    }else{
        presionado = false;
        return 0;
    }
}