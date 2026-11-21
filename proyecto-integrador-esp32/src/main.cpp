#include <Arduino.h>
#include <SPI.h>
#include "NodoIoT.h"
#include "SensorHumedad.h"
#include "SensorDHT11.h"
#include "SensorLuz.h"
#include "ActuadorRele.h"
#include "ActuadorPWM.h"
#include "ControlEncoder.h"
#include "PantallaHMI.h"

// === GPIOs DE TU PROTOTIPO FÍSICO ===
#define PIN_DHT11      17
#define PIN_SENSOR_HUM /* ESTABLECER GPIO*/
#define PIN_SENSOR_LDR /* ESTABLECER GPIO */

#define PIN_RELE_BOMBA /* ESTABLECER GPIO */
#define PIN_PWM_LUZ    /* ESTABLECER GPIO */

#define PIN_TFT_CS     /* ESTABLECER GPIO */
#define PIN_TFT_DC     /* ESTABLECER GPIO */
#define PIN_TFT_RST    -1

#define PIN_ENC_CLK    /* ESTABLECER GPIO */
#define PIN_ENC_DT     /* ESTABLECER GPIO */
#define PIN_ENC_SW     /* ESTABLECER GPIO */
// ====================================

// Instancias de Sensores y Actuadores (Subclases de NodoIoT)
SensorHumedad sensorSuelo("HUM_SUELO", PIN_SENSOR_HUM, 500);
SensorDHT11   sensorAmbiente("DHT11_AMB", PIN_DHT11, 2000);
SensorLuz     sensorLuz("LDR_LUZ", PIN_SENSOR_LDR, 400);
ActuadorRele  bombaRiego("RELE_RIEGO", PIN_RELE_BOMBA);
ActuadorPWM   luminariaPWM("PWM_LUZ", PIN_PWM_LUZ, 0);

// Arreglo Polimórfico Global
const int TOTAL_NODOS = 5;
NodoIoT* redNodos[TOTAL_NODOS] = {
    &sensorSuelo,
    &sensorAmbiente,
    &sensorLuz,
    &bombaRiego,
    &luminariaPWM
};

// Periféricos de Interfaz Local
ControlEncoder encoder(PIN_ENC_CLK, PIN_ENC_DT, PIN_ENC_SW);
PantallaHMI    hmi(PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_RST);

void setup() {
    Serial.begin(115200);

    // Inicialización polimórfica de los 5 nodos
    for (int i = 0; i < TOTAL_NODOS; i++) {
        redNodos[i]->iniciar();
    }

    encoder.iniciar();
    hmi.iniciar(INITR_BLACKTAB);
}

void loop() {
    // 1. Lectura inmediata del KY-040 y navegación HMI
    encoder.actualizar();
    hmi.procesarEntrada(&encoder, &sensorSuelo, &bombaRiego, &luminariaPWM);

    // 2. Actualización polimórfica no bloqueante de sensores y actuadores
    for (int i = 0; i < TOTAL_NODOS; i++) {
        redNodos[i]->actualizar();
    }

    // 3. Lazo de control automático de riego
    if (bombaRiego.isModoAutomatico()) {
        bombaRiego.setEstado(sensorSuelo.hayAlerta());
    }

    // 4. Lazo de control automático proporcional de iluminación (LDR -> PWM)
    if (luminariaPWM.isModoAutomatico()) {
        int luzActual = sensorLuz.getPorcentajeLuz();
        int brilloNecesario = constrain(100 - luzActual, 0, 100);
        luminariaPWM.setPorcentajeBrillo(brilloNecesario);
    }

    // 5. Refresco de la pantalla TFT ST7735
    hmi.renderizar(&sensorSuelo, &sensorAmbiente, &sensorLuz, &bombaRiego, &luminariaPWM);
}