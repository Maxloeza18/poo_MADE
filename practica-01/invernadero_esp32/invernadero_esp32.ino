#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>

// Asignación de Pines para ESP32-S3
const int PIN_DHT11      = 12; // Pin de datos DHT11
const int PIN_LDR_SENSOR = 4;  // ADC Sensor LDR (GPIO 4, pin ADC válido en S3)
const int PIN_FAN_RELAY  = 3;  // Control Digital del Motor/Ventilador (ON/OFF)
const int PIN_LED_PWM    = 21; // Control PWM del LED

// Configuración PWM ESP32 (Solo para el LED)
const int PWM_FREQ        = 5000; // 5 kHz
const int PWM_RESOLUTION  = 8;    // Resolución de 8 bits (0 - 255)
const int LED_PWM_CHANNEL = 1;

// Inicialización del sensor DHT11
#define DHTTYPE DHT11
DHT dht(PIN_DHT11, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // Inicializar sensor DHT
  dht.begin();

  // Configurar el pin del motor como salida digital
  pinMode(PIN_FAN_RELAY, OUTPUT);
  digitalWrite(PIN_FAN_RELAY, LOW); // Apagado inicial

  // Configuración PWM ESP32 (Solo para el LED)
  ledcSetup(LED_PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PIN_LED_PWM, LED_PWM_CHANNEL);

  // Estado inicial (Salida LED en 0)
  ledcWrite(LED_PWM_CHANNEL, 0);
}

void loop() {
  // 1. Lectura de Sensores
  int rawLdr = analogRead(PIN_LDR_SENSOR);
  float tempC = dht.readTemperature();

  // En caso de fallo de lectura en el DHT11
  if (isnan(tempC)) {
    tempC = -127.0;
  }

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

  // 3. Recepción de Comandos desde Python
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    StaticJsonDocument<200> docIn;
    DeserializationError error = deserializeJson(docIn, input);

    if (!error) {
      // Control del Motor (ON/OFF)
      // Puede recibir "fan_state": 1/0 o true/false desde Python
      if (docIn.containsKey("fan_state")) {
        bool fanState = docIn["fan_state"];
        digitalWrite(PIN_FAN_RELAY, fanState ? HIGH : LOW);
      }

      // Control del LED (0 a 255)
      if (docIn.containsKey("led_duty")) {
        int ledDuty = docIn["led_duty"];
        ledcWrite(LED_PWM_CHANNEL, constrain(ledDuty, 0, 255));
      }
    }
  }
}
