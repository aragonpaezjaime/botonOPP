#ifndef BOTON_H
#define BOTON_H

#include <Arduino.h>

// Enum para el tipo de resistencia, más seguro y descriptivo que usar #define
enum class ResistenciaModo {
    MODO_PULLUP,
    MODO_PULLDOWN
};

// Enum para los estados que puede devolver el botón
enum class BotonEstado {
    SIN_ACCION,
    PRESIONADO,
    PULSO_CORTO,
    PULSO_NORMAL,
    PULSO_LARGO,
    DOBLE_PULSO // Nuevo estado para la doble pulsación
};

class boton {
public:
    // El constructor ahora usa el enum ResistenciaModo
    boton(int pin, ResistenciaModo modo);

    // La función checar ahora devuelve un BotonEstado
    BotonEstado checar();

private:
    int _pin;
    ResistenciaModo _modo;
    bool _estadoActivo; // Almacena si el estado activo es HIGH o LOW

    bool _ultimoEstadoBoton = false; // Para el antirrebote
    bool _estadoBotonActual = false;
    bool _estaPresionado = false;

    unsigned long _tiempoInicioPresion = 0;
    unsigned long _ultimoTiempoRebote = 0;

    // --- Variables para la detección de doble pulsación ---
    bool _esperandoSegundoPulso = false; // Flag para saber si estamos esperando el segundo pulso
    bool _ignoreNextRelease = false;   // Flag para ignorar la liberación del segundo pulso
    unsigned long _tiempoPrimerPulso = 0; // Almacena el tiempo en que terminó el primer pulso

    // --- Constantes de tiempo (ajustables) ---
    static const unsigned long TIEMPO_REBOTE_MS = 50;
    static const unsigned long TIEMPO_PULSO_CORTO_MS = 400;
    static const unsigned long TIEMPO_PULSO_NORMAL_MS = 800;
    // Intervalo máximo en ms entre dos pulsos para considerarse una doble pulsación
    static const unsigned long INTERVALO_DOBLE_PULSO_MS = 300; 
};

#endif // BOTON_H
