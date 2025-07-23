#include <Arduino.h>
#include "boton.h"

// Ahora usamos el enum para inicializar el botón. ¡Mucho más claro!
boton boton1(14, ResistenciaModo::MODO_PULLUP);

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  Serial.println("Sistema iniciado. Esperando pulsaciones...");
}

void loop() {
  // Llama a checar() UNA SOLA VEZ por ciclo y guarda el estado
  BotonEstado estado = boton1.checar();

  // Compara el estado usando el enum. El código se explica por sí solo.
  switch (estado) {
    case BotonEstado::PRESIONADO:
      // Serial.println("Botón presionado");
      analogWrite(13, 25);
      break;

    case BotonEstado::PULSO_CORTO:
      Serial.println("Pulso corto detectado");
      analogWrite(13, 50);
      break;

    case BotonEstado::PULSO_NORMAL:
      Serial.println("Pulso normal detectado");
      analogWrite(13, 85);
      break;

    case BotonEstado::PULSO_LARGO:
      Serial.println("Pulso largo detectado");
      analogWrite(13, 125);
      break;

    case BotonEstado::DOBLE_PULSO:
      Serial.println("¡Doble pulso detectado!");
      // Aquí puedes poner la acción que quieras para el doble pulso
      // Por ejemplo, hacer parpadear el LED dos veces
      analogWrite(13, 255);
      break;

    case BotonEstado::SIN_ACCION:
      // No es necesario hacer nada si no hay un evento nuevo
      digitalWrite(13, LOW);
      break;
  }
  if (estado == BotonEstado::SIN_ACCION) {
     digitalWrite(13, LOW);
  }
}
