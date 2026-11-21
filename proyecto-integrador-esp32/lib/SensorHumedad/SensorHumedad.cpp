#include "SensorHumedad.h"

SensorHumedad::SensorHumedad(String id, int pinADC, unsigned long intervaloMs)
    : NodoIoT(id, pinADC, intervaloMs),
      _lecturaCruda(0),
      _porcentajeHumedad(0.0),
      _umbralAlerta(30),
      _valorSeco(3200),
      _valorMojado(1400) {}

void SensorHumedad::iniciar() {
    pinMode(_pin, INPUT);
    _conectado = true;
}

void SensorHumedad::actualizar() {
    unsigned long ahora = millis();
    if (ahora - _ultimoTiempoEjecucion >= _intervaloMs) {
        _ultimoTiempoEjecucion = ahora;

        _lecturaCruda = analogRead(_pin);
        long mapeo = map(_lecturaCruda, _valorSeco, _valorMojado, 0, 100);
        _porcentajeHumedad = constrain(mapeo, 0, 100);
    }
}

void SensorHumedad::setUmbralAlerta(int porcentaje) {
    _umbralAlerta = constrain(porcentaje, 0, 100);
}

int SensorHumedad::getUmbralAlerta() const {
    return _umbralAlerta;
}

float SensorHumedad::getHumedad() const {
    return _porcentajeHumedad;
}

int SensorHumedad::getLecturaCruda() const {
    return _lecturaCruda;
}

bool SensorHumedad::hayAlerta() const {
    return _porcentajeHumedad < _umbralAlerta;
}