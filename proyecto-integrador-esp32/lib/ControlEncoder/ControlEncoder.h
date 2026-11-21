#ifndef CONTROL_ENCODER_H
#define CONTROL_ENCODER_H

#include <Arduino.h>

class ControlEncoder {
private:
    int _pinCLK;
    int _pinDT;
    int _pinSW;
    int _ultimoEstadoCLK;
    int _deltaAcumulado;

    bool _estadoBotonEstable;
    bool _ultimaLecturaBoton;
    bool _clicPendiente;
    unsigned long _ultimoTiempoRebote;
    const unsigned long _retardoRebote = 40;

public:
    ControlEncoder(int clk, int dt, int sw);

    void iniciar();
    void actualizar();

    int leerDelta();      // Retorna pasos (+1 / -1) y limpia el acumulador
    bool leerPulsacion(); // Retorna true una vez por cada pulsación del eje
};

#endif