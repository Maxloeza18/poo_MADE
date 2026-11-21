#include "PantallaHMI.h"

PantallaHMI::PantallaHMI(int8_t pinCS, int8_t pinDC, int8_t pinRST)
    : _tft(pinCS, pinDC, pinRST),
      _menuActual(MENU_MONITOREO), _menuAnterior(MENU_CONTROL_BOMBA),
      _ultimoRefresco(0), _lastHumSuelo(-1), _lastLuz(-1), _lastTemp(-1),
      _lastHumAire(-1), _lastPWM(-1), _lastUmbral(-1),
      _lastBombaOn(false), _lastBombaAuto(true), _lastLuzAuto(true) {}

void PantallaHMI::iniciar(uint8_t tabColor) {
    _tft.initR(tabColor);
    _tft.setRotation(1); // 160x128
    _tft.fillScreen(ST77XX_BLACK);
    dibujarMarcoBase();
}

void PantallaHMI::dibujarMarcoBase() {
    _tft.drawRect(0, 0, _tft.width(), _tft.height(), ST77XX_GREEN);
    _tft.fillRect(0, 0, _tft.width(), 18, ST77XX_GREEN);
    _tft.setTextColor(ST77XX_BLACK);
    _tft.setTextSize(1);
    _tft.setCursor(10, 5);
    _tft.print("INVERNADERO POO v2");
}

void PantallaHMI::procesarEntrada(ControlEncoder* encoder, SensorHumedad* suelo,
                                  ActuadorRele* bomba, ActuadorPWM* luz) {
    if (encoder->leerPulsacion()) {
        _menuActual = static_cast<EstadoMenu>((_menuActual + 1) % 4);
    }

    int delta = encoder->leerDelta();
    if (delta == 0) return;

    switch (_menuActual) {
        case MENU_UMBRAL_RIEGO:
            suelo->setUmbralAlerta(suelo->getUmbralAlerta() + (delta * 2));
            break;

        case MENU_CONTROL_LUMINARIA: {
            int nuevoBrillo = luz->getPorcentajeBrillo() + (delta * 5);
            if (nuevoBrillo <= 0) {
                luz->setModoAutomatico(true);
            } else {
                luz->setModoAutomatico(false);
                luz->setPorcentajeBrillo(nuevoBrillo);
            }
            break;
        }

        case MENU_CONTROL_BOMBA:
            if (delta > 0) {
                bomba->setModoAutomatico(false);
                bomba->setEstado(true);
            } else {
                bomba->setModoAutomatico(true);
            }
            break;

        default:
            break;
    }
}

void PantallaHMI::renderizar(SensorHumedad* suelo, SensorDHT11* dht, SensorLuz* ldr,
                             ActuadorRele* bomba, ActuadorPWM* luz) {
    unsigned long ahora = millis();
    if (ahora - _ultimoRefresco < _intervaloRefresco) return;
    _ultimoRefresco = ahora;

    bool cambio = (_menuActual != _menuAnterior);
    if (cambio) {
        _tft.fillRect(2, 20, _tft.width() - 4, _tft.height() - 22, ST77XX_BLACK);
        _menuAnterior = _menuActual;
    }

    switch (_menuActual) {
        case MENU_MONITOREO:
            dibujarMonitoreo(suelo, dht, ldr, bomba, luz, cambio);
            break;
        case MENU_UMBRAL_RIEGO:
            dibujarUmbralRiego(suelo, cambio);
            break;
        case MENU_CONTROL_LUMINARIA:
            dibujarControlLuminaria(luz, cambio);
            break;
        case MENU_CONTROL_BOMBA:
            dibujarControlBomba(bomba, cambio);
            break;
    }
}

void PantallaHMI::dibujarMonitoreo(SensorHumedad* suelo, SensorDHT11* dht, SensorLuz* ldr,
                                   ActuadorRele* bomba, ActuadorPWM* luz, bool forzar) {
    int temp = (int)dht->getTemperatura();
    int humAire = (int)dht->getHumedadAire();
    int humSuelo = (int)suelo->getHumedad();
    int porLuz = ldr->getPorcentajeLuz();
    int pwmLuz = luz->getPorcentajeBrillo();
    bool bombaOn = bomba->getEstado();

    if (forzar) {
        _tft.setTextSize(1);
        _tft.setTextColor(ST77XX_CYAN);
        _tft.setCursor(8, 25);  _tft.print("AMB:");
        _tft.setCursor(8, 45);  _tft.print("SUELO:");
        _tft.setCursor(8, 65);  _tft.print("LUZ LDR:");
        _tft.setCursor(8, 85);  _tft.print("LUM PWM:");
        _tft.setCursor(8, 105); _tft.print("RIEGO:");
    }

    if (forzar || temp != _lastTemp || humAire != _lastHumAire) {
        _tft.fillRect(62, 25, 92, 12, ST77XX_BLACK);
        _tft.setTextColor(dht->hayAlertaTemperatura() ? ST77XX_RED : ST77XX_WHITE);
        _tft.setCursor(62, 25);
        _tft.print(temp); _tft.print("C / "); _tft.print(humAire); _tft.print("%");
        _lastTemp = temp; _lastHumAire = humAire;
    }

    if (forzar || humSuelo != _lastHumSuelo) {
        _tft.fillRect(62, 45, 92, 12, ST77XX_BLACK);
        _tft.setTextColor(suelo->hayAlerta() ? ST77XX_RED : ST77XX_GREEN);
        _tft.setCursor(62, 45);
        _tft.print(humSuelo); _tft.print("% (U:"); _tft.print(suelo->getUmbralAlerta()); _tft.print("%)");
        _lastHumSuelo = humSuelo;
    }

    if (forzar || porLuz != _lastLuz) {
        _tft.fillRect(62, 65, 92, 12, ST77XX_BLACK);
        _tft.setTextColor(ST77XX_YELLOW);
        _tft.setCursor(62, 65);
        _tft.print(porLuz); _tft.print("%");
        _lastLuz = porLuz;
    }

    if (forzar || pwmLuz != _lastPWM) {
        _tft.fillRect(62, 85, 92, 12, ST77XX_BLACK);
        _tft.setTextColor(ST77XX_WHITE);
        _tft.setCursor(62, 85);
        _tft.print(pwmLuz); _tft.print(luz->isModoAutomatico() ? "% (AUTO)" : "% (MAN)");
        _lastPWM = pwmLuz;
    }

    if (forzar || bombaOn != _lastBombaOn) {
        _tft.fillRect(62, 105, 92, 12, ST77XX_BLACK);
        _tft.setTextColor(bombaOn ? ST77XX_GREEN : ST77XX_ORANGE);
        _tft.setCursor(62, 105);
        _tft.print(bombaOn ? "ON" : "OFF");
        _tft.print(bomba->isModoAutomatico() ? " (AUTO)" : " (MAN)");
        _lastBombaOn = bombaOn;
    }
}

void PantallaHMI::dibujarUmbralRiego(SensorHumedad* suelo, bool forzar) {
    int u = suelo->getUmbralAlerta();
    if (forzar) {
        _tft.setTextColor(ST77XX_YELLOW);
        _tft.setCursor(10, 28); _tft.print("UMBRAL HUMEDAD SUELO");
        _tft.setTextColor(ST77XX_WHITE);
        _tft.setCursor(10, 108); _tft.print("Gira KY-040 | Clic: Sig");
    }
    if (forzar || u != _lastUmbral) {
        _tft.fillRect(35, 55, 95, 30, ST77XX_BLACK);
        _tft.setTextColor(ST77XX_GREEN);
        _tft.setTextSize(3);
        _tft.setCursor(40, 58);
        _tft.print(u); _tft.print("%");
        _tft.setTextSize(1);
        _lastUmbral = u;
    }
}

void PantallaHMI::dibujarControlLuminaria(ActuadorPWM* luz, bool forzar) {
    int pwm = luz->getPorcentajeBrillo();
    bool autoM = luz->isModoAutomatico();
    if (forzar) {
        _tft.setTextColor(ST77XX_YELLOW);
        _tft.setCursor(10, 28); _tft.print("INTENSIDAD LUMINARIA");
        _tft.setTextColor(ST77XX_WHITE);
        _tft.setCursor(10, 108); _tft.print("0% = AUTO | >0% = MAN");
    }
    if (forzar || pwm != _lastPWM || autoM != _lastLuzAuto) {
        _tft.fillRect(20, 52, 125, 35, ST77XX_BLACK);
        _tft.setTextColor(ST77XX_CYAN);
        _tft.setTextSize(3);
        _tft.setCursor(35, 55);
        _tft.print(pwm); _tft.print("%");
        _tft.setTextSize(1);
        _tft.setCursor(55, 85);
        _tft.print(autoM ? "[AUTO]" : "[MANUAL]");
        _lastPWM = pwm; _lastLuzAuto = autoM;
    }
}

void PantallaHMI::dibujarControlBomba(ActuadorRele* bomba, bool forzar) {
    bool autoM = bomba->isModoAutomatico();
    if (forzar) {
        _tft.setTextColor(ST77XX_YELLOW);
        _tft.setCursor(10, 28); _tft.print("CONTROL BOMBA RIEGO");
        _tft.setTextColor(ST77XX_WHITE);
        _tft.setCursor(10, 108); _tft.print("Der: Manual | Izq: Auto");
    }
    if (forzar || autoM != _lastBombaAuto) {
        _tft.fillRect(15, 58, 135, 22, ST77XX_BLACK);
        _tft.setTextColor(ST77XX_GREEN);
        _tft.setTextSize(2);
        _tft.setCursor(18, 60);
        _tft.print(autoM ? "AUTOMATICO" : "MANUAL ON");
        _tft.setTextSize(1);
        _lastBombaAuto = autoM;
    }
}