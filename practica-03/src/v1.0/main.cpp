#include <Arduino.h>
#include "NodosFisicos.h"

// Definimos la cantidad total de nodos en el micro-invernadero
const int NUM_NODOS = 2;

// Arreglo polimórfico de punteros a la clase base
NodoIoT* red[NUM_NODOS];

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n--- Inicializando Sistema IoT Invernadero (POO) ---");

    // Instanciación dinámica con los pines del ESP32
// En tu main.cpp, al crear el nodo en el pin 12 que tenías asignado al sensor:
red[0] = new NodoSensorFisico("POT_SIMULADOR", 12);
    red[1] = new NodoActuadorFisico("ACT_BOMBA", 23);   // Relé/bomba en pin digital 23

    // Downcasting para configurar el umbral del sensor
    ((NodoSensorFisico*)red[0])->setUmbralAlerta(2500); 

    // Inicialización centralizada polimórfica
    for (int i = 0; i < NUM_NODOS; i++) {
        red[i]->iniciar();
    }
}

void loop() {
    Serial.println("\n[Ejecutando Bucle de Telemetría Polimórfico...]");
    
    // Alternamos el estado del actuador en cada ciclo
    ((NodoActuadorFisico*)red[1])->alternarEstado();

    // Bucle polimórfico que ejecuta la acción de cada nodo automáticamente
    for (int i = 0; i < NUM_NODOS; i++) {
        red[i]->ejecutarAccion();
    }
    
    delay(2000); // Pausa de 2 segundos
}