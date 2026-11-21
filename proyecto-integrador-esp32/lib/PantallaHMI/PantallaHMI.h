#ifndef PANTALLA_HMI_H
#define PANTALLA_HMI_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "SensorHumedad.h"
#include "SensorDHT11.h"
#include "SensorLuz.h"
#include "ActuadorRele.h"
#include "ActuadorPWM.h"
#include "ControlEncoder.h"

enum EstadoMenu {
    MENU_MONITOREO,
    MENU_UMBRAL_RIEGO,
    MENU_CONTROL_LUMINARIA,
    MENU_CONTROL_BOMBA
};

class PantallaHMI {
private:
    Adafruit_ST7735 _tft;
    EstadoMenu _menuActual;
    EstadoMenu _menuAnterior;
    unsigned long _ultimoRefresco;
    const unsigned long _intervaloRefresco = 250;

    // Caché de valores para evitar parpadeo en SPI
    int _lastHumSuelo, _lastLuz, _lastTemp, _lastHumAire, _lastPWM, _lastUmbral;
    bool _lastBombaOn, _lastBombaAuto, _lastLuzAuto;

    void dibujarMarcoBase();
    void dibujarMonitoreo(SensorHumedad* suelo, SensorDHT11* dht, SensorLuz* ldr,
                          ActuadorRele* bomba, ActuadorPWM* luz, bool forzar);
    void dibujarUmbralRiego(SensorHumedad* suelo, bool forzar);
    void dibujarControlLuminaria(ActuadorPWM* luz, bool forzar);
    void dibujarControlBomba(ActuadorRele* bomba, bool forzar);

public:
    PantallaHMI(int8_t pinCS, int8_t pinDC, int8_t pinRST = -1);

    void iniciar(uint8_t tabColor = INITR_BLACKTAB);
    void procesarEntrada(ControlEncoder* encoder, SensorHumedad* suelo,
                         ActuadorRele* bomba, ActuadorPWM* luz);
    void renderizar(SensorHumedad* suelo, SensorDHT11* dht, SensorLuz* ldr,
                    ActuadorRele* bomba, ActuadorPWM* luz);
};

#endif