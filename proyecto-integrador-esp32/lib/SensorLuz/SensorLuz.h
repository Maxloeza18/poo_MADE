#ifndef SENSOR_LUZ_H
#define SENSOR_LUZ_H

#include "NodoIoT.h"

class SensorLuz : public NodoIoT {
private:
    int _lecturaCruda;
    int _porcentajeLuz;
    int _umbralLuzMinima;

public:
    SensorLuz(String id, int pinADC, unsigned long intervaloMs = 500);

    void iniciar() override;
    void actualizar() override;

    int getPorcentajeLuz() const;
    int getLecturaCruda() const;
    void setUmbralLuzMinima(int porcentaje);
    int getUmbralLuzMinima() const;
    bool requiereIluminacion() const;
};

#endif