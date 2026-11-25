#include <Arduino.h>
#include "NodosFisicos.h"

// Red con 3 sensores y 2 actuadores en el micro-invernadero
const int NUM_NODOS = 5;

// Arreglo polimórfico de punteros a la clase base
NodoIoT* red[NUM_NODOS];

// Punteros tipados auxiliares para acceso claro a métodos específicos
NodoSensorFisico* sensorHumedad;
NodoSensorFisico* sensorLuz;
NodoSensorFisico* sensorTempSim;
NodoActuadorFisico* actuadorBomba;
NodoActuadorFisico* actuadorVentilador;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n--- Inicializando Red IoT de Invernadero (POO) ---");

    // Sensores en pines ADC1 del ESP32 (34 y 35 son solo entrada)
    sensorHumedad  = new NodoSensorFisico("SEN_HUMEDAD", 34);
    sensorLuz      = new NodoSensorFisico("SEN_LUZ", 35);
    sensorTempSim  = new NodoSensorFisico("SEN_TEMP_POT", 32);

    // Actuadores en pines digitales de salida
    actuadorBomba      = new NodoActuadorFisico("ACT_BOMBA", 23);
    actuadorVentilador = new NodoActuadorFisico("ACT_VENTILADOR", 25);

    // Registrar todos los nodos en el arreglo polimórfico
    red[0] = sensorHumedad;
    red[1] = sensorLuz;
    red[2] = sensorTempSim;
    red[3] = actuadorBomba;
    red[4] = actuadorVentilador;

    // Configurar umbrales de alerta de los sensores
    sensorHumedad->setUmbralAlerta(2600);
    sensorLuz->setUmbralAlerta(3000);
    sensorTempSim->setUmbralAlerta(2400);

    // Inicialización centralizada polimórfica
    for (int i = 0; i < NUM_NODOS; i++) {
        red[i]->iniciar();
    }
}

void loop() {
    Serial.println("\n[Ejecutando Ciclo de Red de Sensores y Actuadores...]");

    // 1. Primero leemos todos los sensores (primeros 3 nodos)
    for (int i = 0; i < 3; i++) {
        red[i]->ejecutarAccion();
    }

    // 2. Lógica de control del invernadero a partir de las lecturas
    // Ejemplo: si la lectura de humedad supera el umbral, activa la bomba; si no, la apaga
    bool activarRiego = (sensorHumedad->getUltimaLectura() > 2600);
    actuadorBomba->setEstado(activarRiego);

    // El ventilador alterna en cada ciclo (o puedes ligarlo a sensorTempSim)
    actuadorVentilador->alternarEstado();

    // 3. Ejecutamos la acción física de los actuadores (nodos 3 y 4)
    for (int i = 3; i < NUM_NODOS; i++) {
        red[i]->ejecutarAccion();
    }

    delay(2000);
}
