#ifndef ACTUADOR_RELE_H
#define ACTUADOR_RELE_H

#include "NodoIoT.h"

class ActuadorRele : public NodoIoT {
private:
    bool _estadoActivo;
    bool _modoAutomatico;

public:
    ActuadorRele(String id, int pinDigital);

    void iniciar() override;
    void actualizar() override;

    void setEstado(bool encender);
    bool getEstado() const;
    void setModoAutomatico(bool autoMode);
    bool isModoAutomatico() const;
};

#endif