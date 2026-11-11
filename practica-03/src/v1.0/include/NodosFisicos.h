#ifndef NODOS_FISICOS_H
#define NODOS_FISICOS_H
#include "NodoIoT.h"

// 1. Subclase para sensores (Ej. Sensor de humedad capacitivo o temperatura)
class NodoSensorFisico : public NodoIoT {
private:
    // Atributo privado: Solo esta clase puede modificarlo directamente
    int _umbralAlerta;

public:
    // El constructor invoca al constructor de la superclase
    NodoSensorFisico(String id, int pinHardware) : NodoIoT(id, pinHardware) {
        _umbralAlerta = 2048; // Valor medio por defecto para el ADC de 12 bits
    }

    // Polimorfismo: Sobrescribe la configuración inicial del pin
    void iniciar() override {
        pinMode(pin, INPUT);
        conectado = true;
    }

    // Encapsulamiento: Setter que protege el hardware
    // Valida que el umbral no exceda la resolución del ADC del ESP32 (0 a 4095)
    void setUmbralAlerta(int umbral) {
        if(umbral >= 0 && umbral <= 4095) {
            _umbralAlerta = umbral;
        } else {
            Serial.println("Error: Umbral fuera del rango del ADC (0-4095).");
        }
    }

    // Polimorfismo: Implementación de la lectura del sensor
    void ejecutarAccion() override {
        int lectura = analogRead(pin);
        Serial.print("["); Serial.print(idDispositivo); Serial.print("] ADC: ");
        Serial.print(lectura);
        
        if(lectura > _umbralAlerta) {
            Serial.print(" -> ¡ALERTA! Supera el umbral de "); 
            Serial.print(_umbralAlerta);
        }
        Serial.println();
    }
};


// 2. Subclase para actuadores (Ejemplo. Relé para bomba de agua o ventilador)
class NodoActuadorFisico : public NodoIoT {
private:
    bool _estadoActivo;

public:
    NodoActuadorFisico(String id, int pinHardware) : NodoIoT(id, pinHardware) {
        _estadoActivo = false;
    }

    // Polimorfismo: Sobrescribe la configuración inicial del pin
    void iniciar() override {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW); // Asegura que inicie apagado por seguridad
        conectado = true;
    }
    
    // Método exclusivo de esta subclase para cambiar el estado lógico
    void alternarEstado() {
        _estadoActivo = !_estadoActivo;
    }

    // Polimorfismo: Implementación de la acción física en el hardware
    void ejecutarAccion() override {
        digitalWrite(pin, _estadoActivo ? HIGH : LOW);
        Serial.print("["); Serial.print(idDispositivo); Serial.print("] Hardware: ");
        Serial.println(_estadoActivo ? "ENCENDIDO" : "APAGADO");
    }
};

#endif
