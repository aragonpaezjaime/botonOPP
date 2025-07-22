#ifndef boton_h
#define boton_h

#include <Arduino.h>    

#define POSITIVO 1
#define NEGATIVO 0
class boton {
    public:
        boton(int pin, unsigned int modo);
        void setup();
        int checar();
        bool read();
    private:
        int pin;
        unsigned int modo;
        bool estadoAnterior;
        bool presionado;
        bool corto;
        bool doble;
        bool largo;
};

#endif
