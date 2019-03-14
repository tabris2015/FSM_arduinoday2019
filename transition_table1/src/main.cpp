#include "Arduino.h"
#include "FSME.h"

#define BOTON_PIN 2

int intervalo = 500;
// enum de estados
enum estados_enum {
	STANDBY,
	OFF,
  ON
};

// declaracion del objeto de la maquina de estados
FSME fsm;
State estados[3]; // array de estados
Transition *STANDBY_trans[1]; // array de punteros para las transiciones
Transition *OFF_trans[2]; 
Transition *ON_trans[2]; 
// 

// Prototipos
// eventos
uint8_t tiempoCumplido();
uint8_t botonPresionado();
// acciones
void encender(void);
void apagar(void);
//------------------

void setup()
{
  // inicializar pines
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(BOTON_PIN, INPUT_PULLUP);
  
  // Definicion de transiciones
  // se debe inicializar el array de transiciones definido en la tabla
  STANDBY_trans[0] = new EvnTransition(botonPresionado, OFF);
  OFF_trans[0] = new EvnTransition(tiempoCumplido, ON);
  OFF_trans[1] = new EvnTransition(botonPresionado, STANDBY);
  ON_trans[0] = new EvnTransition(tiempoCumplido, OFF);  
  ON_trans[1] = new EvnTransition(botonPresionado, STANDBY);

  // Definicion de estados
  estados[STANDBY].setState(apagar, STANDBY_trans, 1);
  
  estados[OFF].setState(apagar, OFF_trans, 2);

  estados[ON].setState(encender, ON_trans, 2);
     

  fsm.setStates(estados, 3); // pasar los estados a la maquina
  fsm.setInitialState(STANDBY); // configurar el estado inicial
}

// The loop function is called in an endless loop
void loop()
{
  // la maquina de estados solamente se ejecuta con una linea en el loop
	fsm.run(); // run the FSM
}

// implementacion de funciones
// eventos 
uint8_t botonPresionado()
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
      return 1;
    }
  }
  return 0;
}

uint8_t tiempoCumplido()
{
  static int tiempo_anterior = millis();

  if(millis() - tiempo_anterior > intervalo)
  {
    tiempo_anterior = millis();
    return 1;
  }
  return 0;
}
//

// acciones
void encender(void){
  if (fsm.isStateChanged()) // se pueden ejecutar acciones solo cuando se entra al estado
  {
    digitalWrite(LED_BUILTIN, 1);
  }
}

void apagar(void){
  if (fsm.isStateChanged()) 
  {
    digitalWrite(LED_BUILTIN, 0);
  }
}