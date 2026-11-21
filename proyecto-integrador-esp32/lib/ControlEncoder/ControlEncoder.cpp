#include "ControlEncoder.h"

ControlEncoder::ControlEncoder(int clk, int dt, int sw)
    : _pinCLK(clk), _pinDT(dt), _pinSW(sw), _ultimoEstadoCLK(HIGH),
      _deltaAcumulado(0), _estadoBotonEstable(HIGH), _ultimaLecturaBoton(HIGH),
      _clicPendiente(false), _ultimoTiempoRebote(0) {}

void ControlEncoder::iniciar() {
    pinMode(_pinCLK, INPUT);
    pinMode(_pinDT, INPUT);
    pinMode(_pinSW, INPUT_PULLUP);
    _ultimoEstadoCLK = digitalRead(_pinCLK);
}

void ControlEncoder::actualizar() {
    // 1. Decodificación en cuadratura del KY-040
    int estadoActualCLK = digitalRead(_pinCLK);
    if (estadoActualCLK != _ultimoEstadoCLK && estadoActualCLK == LOW) {
        if (digitalRead(_pinDT) != estadoActualCLK) {
            _deltaAcumulado++;
        } else {
            _deltaAcumulado--;
        }
    }
    _ultimoEstadoCLK = estadoActualCLK;

    // 2. Antirrebote no bloqueante para el pulsador SW
    bool lecturaActual = digitalRead(_pinSW);
    if (lecturaActual != _ultimaLecturaBoton) {
        _ultimoTiempoRebote = millis();
    }

    if ((millis() - _ultimoTiempoRebote) > _retardoRebote) {
        if (lecturaActual != _estadoBotonEstable) {
            _estadoBotonEstable = lecturaActual;
            if (_estadoBotonEstable == LOW) {
                _clicPendiente = true;
            }
        }
    }
    _ultimaLecturaBoton = lecturaActual;
}

int ControlEncoder::leerDelta() {
    int pasos = _deltaAcumulado;
    _deltaAcumulado = 0;
    return pasos;
}

bool ControlEncoder::leerPulsacion() {
    if (_clicPendiente) {
        _clicPendiente = false;
        return true;
    }
    return false;
}