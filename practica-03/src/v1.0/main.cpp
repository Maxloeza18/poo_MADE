#include <Arduino.h>
#include "NodosFisicos.h"

// Definimos la cantidad total de nodos (sensores y actuadores) en el micro-invernadero
const int NUM_NODOS = 2;

// 1. Arreglo polimórfico de punteros a la clase base
// Esto permite almacenar diferentes objetos hijos en una sola lista estructurada.
NodoIoT* red[NUM_NODOS];

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n--- Inicializando Sistema IoT Invernadero (POO) ---");

    // 2. Instanciación dinámica
    // Asignamos memoria para los dispositivos físicos conectándolos a pines específicos del ESP32
    red[0] = new NodoSensorFisico("SENS_HUMEDAD", 34);  // Sensor capacitivo en pin ADC 34
    red[1] = new NodoActuadorFisico("ACT_BOMBA", 23);   // Relé/bomba en pin digital 23

    // 3. Cast seguro (Downcasting)
    // Accedemos al método setter encapsulado de la clase hija para establecer el umbral de alerta
    ((NodoSensorFisico*)red[0])->setUmbralAlerta(2500); 

    // 4. Inicialización centralizada
    // Recorremos el arreglo invocando el método iniciar() sin preguntar el tipo de dispositivo
    for (int i = 0; i < NUM_NODOS; i++) {
        red[i]->iniciar();
    }
}

void loop() {
    Serial.println("\n[Ejecutando Bucle de Telemetría Polimórfico...]");
    
    // Simulación temporal: Alternamos el estado del actuador (bomba/ventilador) en cada ciclo
    ((NodoActuadorFisico*)red[1])->alternarEstado();

    // 5. El núcleo del Polimorfismo
    // Este bucle ejecuta la acción física correspondiente (analogRead o digitalWrite) 
    // de cada nodo automáticamente gracias al método virtual puro de la superclase.
    for (int i = 0; i < NUM_NODOS; i++) {
        red[i]->ejecutarAccion();
    }
    
    // Pausa de 2 segundos para estabilizar las lecturas antes del siguiente ciclo
    delay(2000); 
}