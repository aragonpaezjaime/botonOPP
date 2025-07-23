#include "boton.h"

// Inicializa las constantes estáticas
const unsigned long boton::TIEMPO_REBOTE_MS;
const unsigned long boton::TIEMPO_PULSO_CORTO_MS;
const unsigned long boton::TIEMPO_PULSO_NORMAL_MS;
const unsigned long boton::INTERVALO_DOBLE_PULSO_MS;

boton::boton(int pin, ResistenciaModo modo) : _pin(pin), _modo(modo) {
    if (_modo == ResistenciaModo::MODO_PULLUP) {
        pinMode(_pin, INPUT_PULLUP);
        _estadoActivo = LOW; // En PULLUP, el botón está activo en LOW
    } else {
        pinMode(_pin, INPUT_PULLDOWN);
        _estadoActivo = HIGH; // En PULLDOWN, el botón está activo en HIGH
    }
}

BotonEstado boton::checar() {
    // --- Lógica de Antirrebote (Debounce) ---
    bool lecturaActual = (digitalRead(_pin) == _estadoActivo);

    if (lecturaActual != _ultimoEstadoBoton) {
        _ultimoTiempoRebote = millis();
    }
    _ultimoEstadoBoton = lecturaActual;

    if ((millis() - _ultimoTiempoRebote) > TIEMPO_REBOTE_MS) {
        if (lecturaActual != _estadoBotonActual) {
            _estadoBotonActual = lecturaActual;

            if (_estadoBotonActual) {
                // --- EL BOTÓN ACABA DE SER PRESIONADO ---
                _tiempoInicioPresion = millis();
                _estaPresionado = true;

                // Si estábamos esperando el segundo pulso y se presiona a tiempo...
                if (_esperandoSegundoPulso && (millis() - _tiempoPrimerPulso) < INTERVALO_DOBLE_PULSO_MS) {
                    _esperandoSegundoPulso = false; // Reseteamos el flag
                    _ignoreNextRelease = true;    // Ignoramos la siguiente liberación
                    return BotonEstado::DOBLE_PULSO;
                }
                // Ya no retornamos PRESIONADO aquí para evitar el mensaje no deseado

            } else {
                // --- EL BOTÓN ACABA DE SER SOLTADO ---
                _estaPresionado = false;
                // Si estamos en el estado de ignorar (porque acabamos de hacer un doble pulso), no hacemos nada
                if (_ignoreNextRelease) {
                    _ignoreNextRelease = false;
                    return BotonEstado::SIN_ACCION;
                }
                unsigned long duracion = millis() - _tiempoInicioPresion;
                // Si la duración es muy corta, podría ser el primer pulso de un doble pulso
                if (duracion < TIEMPO_PULSO_CORTO_MS) {
                    _esperandoSegundoPulso = true;
                    _tiempoPrimerPulso = millis(); // Guardamos el tiempo de este pulso
                    // No retornamos nada aún, esperamos a ver si llega el segundo pulso o si expira el tiempo
                } else if (duracion >= TIEMPO_PULSO_NORMAL_MS) {
                    return BotonEstado::PULSO_LARGO;
                } else {
                    return BotonEstado::PULSO_NORMAL;
                }
            }
        }
    }

    // --- Lógica de Timeout para la Doble Pulsación ---
    // Si estábamos esperando un segundo pulso pero ha pasado demasiado tiempo...
    if (_esperandoSegundoPulso && (millis() - _tiempoPrimerPulso) >= INTERVALO_DOBLE_PULSO_MS) {
        _esperandoSegundoPulso = false; // Reseteamos el flag
        // Como el tiempo ha expirado, ahora sí consideramos que fue un pulso corto simple
        return BotonEstado::PULSO_CORTO;
    }
    if (_estaPresionado) {
        return BotonEstado::PRESIONADO;
    }
    return BotonEstado::SIN_ACCION; // No ha pasado nada relevante
}
