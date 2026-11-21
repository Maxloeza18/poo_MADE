#include "SensorDHT11.h"

SensorDHT11::SensorDHT11(String id, int pinData, unsigned long intervaloMs)
    : NodoIoT(id, pinData, intervaloMs), _dht(pinData, DHT11),
      _temperatura(0.0), _humedadAire(0.0), _umbralTempMax(32.0) {}

void SensorDHT11::iniciar() {
    _dht.begin();
    _conectado = true;
}

void SensorDHT11::actualizar() {
    unsigned long ahora = millis();
    if (ahora - _ultimoTiempoEjecucion >= _intervaloMs) {
        _ultimoTiempoEjecucion = ahora;

        float t = _dht.readTemperature();
        float h = _dht.readHumidity();

        if (!isnan(t) && !isnan(h)) {
            _temperatura = t;
            _humedadAire = h;
        }
    }
}

float SensorDHT11::getTemperatura() const { return _temperatura; }
float SensorDHT11::getHumedadAire() const { return _humedadAire; }

void SensorDHT11::setUmbralTempMax(float tempMax) {
    _umbralTempMax = constrain(tempMax, 0.0, 50.0);
}

float SensorDHT11::getUmbralTempMax() const { return _umbralTempMax; }
bool SensorDHT11::hayAlertaTemperatura() const { return _temperatura > _umbralTempMax; }