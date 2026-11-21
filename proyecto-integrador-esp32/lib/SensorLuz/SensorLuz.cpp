#include "SensorLuz.h"

SensorLuz::SensorLuz(String id, int pinADC, unsigned long intervaloMs)
    : NodoIoT(id, pinADC, intervaloMs), _lecturaCruda(0),
      _porcentajeLuz(0), _umbralLuzMinima(40) {}

void SensorLuz::iniciar() {
    pinMode(_pin, INPUT);
    _conectado = true;
}

void SensorLuz::actualizar() {
    unsigned long ahora = millis();
    if (ahora - _ultimoTiempoEjecucion >= _intervaloMs) {
        _ultimoTiempoEjecucion = ahora;

        _lecturaCruda = analogRead(_pin);
        _porcentajeLuz = constrain(map(_lecturaCruda, 0, 4095, 0, 100), 0, 100);
    }
}

int SensorLuz::getPorcentajeLuz() const { return _porcentajeLuz; }
int SensorLuz::getLecturaCruda() const { return _lecturaCruda; }

void SensorLuz::setUmbralLuzMinima(int porcentaje) {
    _umbralLuzMinima = constrain(porcentaje, 0, 100);
}

int SensorLuz::getUmbralLuzMinima() const { return _umbralLuzMinima; }
bool SensorLuz::requiereIluminacion() const { return _porcentajeLuz < _umbralLuzMinima; }