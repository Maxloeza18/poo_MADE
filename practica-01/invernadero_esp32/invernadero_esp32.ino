#include <Arduino.h>
#include <ArduinoJson.h>

// Asignación de Pines
const int PIN_TEMP_SENSOR = 34; // ADC Sensor Térmico
const int PIN_LDR_SENSOR  = 32; // ADC Sensor LDR
const int PIN_FAN_PWM     = 18; // PWM Ventilador
const int PIN_LED_PWM     = 19; // PWM LED de Potencia

// Configuración LEDC (PWM 5kHz)
const int PWM_FREQ       = 5000;
const int PWM_RESOLUTION = 8; // 0-255
const int FAN_PWM_CHANNEL = 0;
const int LED_PWM_CHANNEL = 1;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  ledcSetup(FAN_PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PIN_FAN_PWM, FAN_PWM_CHANNEL);

  ledcSetup(LED_PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PIN_LED_PWM, LED_PWM_CHANNEL);

  ledcWrite(FAN_PWM_CHANNEL, 0);
  ledcWrite(LED_PWM_CHANNEL, 0);
}

void loop() {
  // 1. Lectura de Sensores
  int rawTemp = analogRead(PIN_TEMP_SENSOR);
  int rawLdr  = analogRead(PIN_LDR_SENSOR);

  float voltage = (rawTemp / 4095.0) * 3300.0;
  float tempC   = voltage / 10.0; // LM35: 10mV/°C

  // 2. Transmisión Serial a Python (cada 200 ms)
  static unsigned long lastSend = 0;
  if (millis() - lastSend >= 200) {
    lastSend = millis();
    StaticJsonDocument<128> docOut;
    docOut["temp"] = tempC;
    docOut["ldr"]  = rawLdr;
    serializeJson(docOut, Serial);
    Serial.println(); // Salto de línea como delimitador
  }

  // 3. Recepción de Comandos/Control desde Python
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    StaticJsonDocument<200> docIn;
    DeserializationError error = deserializeJson(docIn, input);

    if (!error) {
      if (docIn.containsKey("fan_duty")) {
        int fanDuty = docIn["fan_duty"];
        ledcWrite(FAN_PWM_CHANNEL, constrain(fanDuty, 0, 255));
      }
      if (docIn.containsKey("led_duty")) {
        int ledDuty = docIn["led_duty"];
        ledcWrite(LED_PWM_CHANNEL, constrain(ledDuty, 0, 255));
      }
    }
  }
}
