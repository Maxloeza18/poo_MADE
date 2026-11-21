#include "ActuadorPWM.h"

ActuadorPWM::ActuadorPWM(String id, int pinSalida, uint8_t canalPWM)
    : NodoIoT(id, pinSalida, 50), _canalPWM(canalPWM),
      _cicloTrabajo(0), _porcentajeBrillo(0), _modoAutomatico(true) {}

void ActuadorPWM::iniciar() {
    ledcSetup(_canalPWM, 5000, 8); // 5 kHz, resolución 8 bits (0-255)
    ledcAttachPin(_pin, _canalPWM);
    ledcWrite(_canalPWM, 0);
    _conectado = true;
}

void ActuadorPWM::actualizar() {
    unsigned long ahora = millis();
    if (ahora - _ultimoTiempoEjecucion >= _intervaloMs) {
        _ultimoTiempoEjecucion = ahora;
        ledcWrite(_canalPWM, _cicloTrabajo);
    }
}

void ActuadorPWM::setPorcentajeBrillo(int porcentaje) {
    _porcentajeBrillo = constrain(porcentaje, 0, 100);
    _cicloTrabajo = map(_porcentajeBrillo, 0, 100, 0, 255);
}

uint8_t ActuadorPWM::getPorcentajeBrillo() const { return _porcentajeBrillo; }
uint8_t ActuadorPWM::getDutyCycle() const { return _cicloTrabajo; }
void ActuadorPWM::setModoAutomatico(bool autoMode) { _modoAutomatico = autoMode; }
bool ActuadorPWM::isModoAutomatico() const { return _modoAutomatico; }