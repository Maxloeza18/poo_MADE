#include "ActuadorRele.h"

ActuadorRele::ActuadorRele(String id, int pinDigital)
    : NodoIoT(id, pinDigital, 100),
      _estadoActivo(false),
      _modoAutomatico(true) {}

void ActuadorRele::iniciar() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    _conectado = true;
}

void ActuadorRele::actualizar() {
    unsigned long ahora = millis();
    if (ahora - _ultimoTiempoEjecucion >= _intervaloMs) {
        _ultimoTiempoEjecucion = ahora;
        digitalWrite(_pin, _estadoActivo ? HIGH : LOW);
    }
}

void ActuadorRele::setEstado(bool encender) {
    _estadoActivo = encender;
}

bool ActuadorRele::getEstado() const {
    return _estadoActivo;
}

void ActuadorRele::setModoAutomatico(bool autoMode) {
    _modoAutomatico = autoMode;
}

bool ActuadorRele::isModoAutomatico() const {
    return _modoAutomatico;
}