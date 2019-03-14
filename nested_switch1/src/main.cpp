#include <Arduino.h>

// definicion de estados como macros (tambien se puede usar un enum)
#define OFF 0
#define ON 1

int estado; // variable de estado

void setup() {
  // configuracion de pines
  pinMode(LED_BUILTIN, OUTPUT);

  // estado inicial
  estado = OFF; 
}

void loop() {
  // ejecucion de la maquina de estado
  switch (estado)
  {
    case OFF:
      // apaga el led
      digitalWrite(LED_BUILTIN, 0);
      // espera un poco
      delay(500);
      // cambia de estado
      estado = ON;
      break;

    case ON:
      // enciende el led
      digitalWrite(LED_BUILTIN, 1);
      // espera un poco
      delay(500);
      // cambia de estado
      estado = OFF;
      break;
  
    default:
      break;
  }
}