#include "NodoIoT.h"

NodoIoT::NodoIoT(String id, int pinHardware, unsigned long intervaloMs)
    : _idDispositivo(id),
      _pin(pinHardware),
      _conectado(false),
      _ultimoTiempoEjecucion(0),
      _intervaloMs(intervaloMs) {}

NodoIoT::~NodoIoT() {}

String NodoIoT::getId() const {
    return _idDispositivo;
}

bool NodoIoT::isConectado() const {
    return _conectado;
}

void NodoIoT::setIntervalo(unsigned long nuevoIntervalo) {
    if (nuevoIntervalo >= 50) {
        _intervaloMs = nuevoIntervalo;
    }
}