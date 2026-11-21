#ifndef NODO_IOT_H
#define NODO_IOT_H

#include <Arduino.h>

class NodoIoT {
protected:
    String _idDispositivo;
    int _pin;
    bool _conectado;
    unsigned long _ultimoTiempoEjecucion;
    unsigned long _intervaloMs;

public:
    NodoIoT(String id, int pinHardware, unsigned long intervaloMs = 1000);
    virtual ~NodoIoT();

    virtual void iniciar() = 0;
    virtual void actualizar() = 0;

    String getId() const;
    bool isConectado() const;
    void setIntervalo(unsigned long nuevoIntervalo);
};

#endif