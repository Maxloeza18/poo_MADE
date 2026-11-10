#ifndef NODO_IOT_H
#define NODO_IOT_H
#include <Arduino.h>

class NodoIoT {
protected:
    // Atributos protegidos para que las subclases puedan acceder a ellos
    String idDispositivo;
    int pin;
    bool conectado;

public:
    // Constructor
    NodoIoT(String id, int pinHardware) {
        idDispositivo = id;
        pin = pinHardware;
        conectado = false;
    }
    
    // Destructor virtual (buena práctica en C++ al usar polimorfismo)
    virtual ~NodoIoT() {}

    // Métodos virtuales
    virtual void iniciar() {
        // Método base que configurará el pinMode en el ESP32
    }
    
    // Método polimórfico puro o base
    virtual void ejecutarAccion() = 0; 
};

#endif