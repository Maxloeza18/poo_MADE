#ifndef SENSOR_DHT11_H
#define SENSOR_DHT11_H

#include "NodoIoT.h"
#include <DHT.h>

class SensorDHT11 : public NodoIoT {
private:
    DHT _dht;
    float _temperatura;
    float _humedadAire;
    float _umbralTempMax;

public:
    SensorDHT11(String id, int pinData, unsigned long intervaloMs = 2000);

    void iniciar() override;
    void actualizar() override;

    float getTemperatura() const;
    float getHumedadAire() const;
    void setUmbralTempMax(float tempMax);
    float getUmbralTempMax() const;
    bool hayAlertaTemperatura() const;
};

#endif