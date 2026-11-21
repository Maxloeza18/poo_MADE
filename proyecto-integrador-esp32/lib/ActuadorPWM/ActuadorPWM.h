#ifndef ACTUADOR_PWM_H
#define ACTUADOR_PWM_H

#include "NodoIoT.h"

class ActuadorPWM : public NodoIoT {
private:
    uint8_t _canalPWM;
    uint8_t _cicloTrabajo;    // 0 a 255
    uint8_t _porcentajeBrillo; // 0 a 100%
    bool _modoAutomatico;

public:
    ActuadorPWM(String id, int pinSalida, uint8_t canalPWM = 0);

    void iniciar() override;
    void actualizar() override;

    void setPorcentajeBrillo(int porcentaje);
    uint8_t getPorcentajeBrillo() const;
    uint8_t getDutyCycle() const;
    void setModoAutomatico(bool autoMode);
    bool isModoAutomatico() const;
};

#endif