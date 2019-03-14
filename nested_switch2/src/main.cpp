#include <Arduino.h>

// definicion de pines
#define BOTON_PIN 2

// definicion de estados como macros (tambien se puede usar un enum)
#define OFF 0
#define ON 1
#define STANDBY 2

int estado; // variable de estado
int intervalo = 500;

// eventos 

bool botonPresionado()
{
  static int estado_anterior = 1; // activo en bajo

  int estado = digitalRead(BOTON_PIN);
  if(estado != estado_anterior)
  {
    estado_anterior = estado;
    // se ha presionado
    if(estado)
    {
      delay(20);  // debounce
      return true;
    }
  }
  return false;
}

bool tiempoCumplido()
{
  static int tiempo_anterior;

  if(millis() - tiempo_anterior > intervalo)
  {
    tiempo_anterior = millis();
    return true;
  }
  return false;
}
//


void setup() {
  // configuracion de pines
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BOTON_PIN, INPUT_PULLUP);

  // estado inicial
  estado = STANDBY; 
}

void loop() {
  // ejecucion de la maquina de estado
  switch (estado)
  {
    case OFF:
      // apaga el led
      digitalWrite(LED_BUILTIN, 0);
      // verifica eventos
      if(tiempoCumplido())
      {
        estado = ON;
      }
      else if(botonPresionado())
      {
        estado = STANDBY;
      }
      break;

    case ON:
      // enciende el led
      digitalWrite(LED_BUILTIN, 1);
      // verifica eventos
      if(tiempoCumplido())
      {
        estado = OFF;
      }
      else if(botonPresionado())
      {
        estado = STANDBY;
      }
      break;

    case STANDBY:
      // apaga el led
      digitalWrite(LED_BUILTIN, 0);
      // verifica eventos
      if(botonPresionado())
      {
        estado = OFF;
      }
      break;

    default:
      break;
  }
}