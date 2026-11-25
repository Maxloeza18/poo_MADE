#ifndef NODOS_FISICOS_H
#define NODOS_FISICOS_H
#include "NodoIoT.h"

// 1. Subclase para sensores analógicos (humedad de suelo, luz, temperatura/simulador)
class NodoSensorFisico : public NodoIoT {
private:
    int _umbralAlerta;
    int _ultimaLectura;

public:
    NodoSensorFisico(String id, int pinHardware) : NodoIoT(id, pinHardware) {
        _umbralAlerta = 2048; // Valor medio por defecto para el ADC de 12 bits (0-4095)
        _ultimaLectura = 0;
    }

    // Polimorfismo: Sobrescribe la configuración inicial del pin
    void iniciar() override {
        pinMode(pin, INPUT);
        conectado = true;
    }

    // Encapsulamiento: Setter que protege el rango del ADC del ESP32 (0 a 4095)
    void setUmbralAlerta(int umbral) {
        if (umbral >= 0 && umbral <= 4095) {
            _umbralAlerta = umbral;
        } else {
            Serial.println("Error: Umbral fuera del rango del ADC (0-4095).");
        }
    }

    int getUltimaLectura() const {
        return _ultimaLectura;
    }

    // Polimorfismo: Implementación de la lectura del sensor
    void ejecutarAccion() override {
        _ultimaLectura = analogRead(pin);
        Serial.print("[");
        Serial.print(idDispositivo);
        Serial.print(" | GPIO ");
        Serial.print(pin);
        Serial.print("] ADC: ");
        Serial.print(_ultimaLectura);

        if (_ultimaLectura > _umbralAlerta) {
            Serial.print(" -> ¡ALERTA! Supera el umbral de ");
            Serial.print(_umbralAlerta);
        }
        Serial.println();
    }
};

// 2. Subclase para actuadores (relé para bomba de agua, ventilador, luces, etc.)
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

    // Cambia el estado lógico manualmente
    void alternarEstado() {
        _estadoActivo = !_estadoActivo;
    }

    // Establece el estado lógico directamente (útil para control automático)
    void setEstado(bool nuevoEstado) {
        _estadoActivo = nuevoEstado;
    }

    bool getEstado() const {
        return _estadoActivo;
    }

    // Polimorfismo: Implementación de la acción física en el hardware
    void ejecutarAccion() override {
        digitalWrite(pin, _estadoActivo ? HIGH : LOW);
        Serial.print("[");
        Serial.print(idDispositivo);
        Serial.print(" | GPIO ");
        Serial.print(pin);
        Serial.print("] Hardware: ");
        Serial.println(_estadoActivo ? "ENCENDIDO" : "APAGADO");
    }
};

#endif
