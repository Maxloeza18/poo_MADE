---
fecha_creacion: 2026-09-09
fecha_terminacion: 2026-09-28
estado: En progreso
tags:
  - ESP32
  - electronica
  - programacion-orientada-a-objetos
---

# Control de Sensores y Actuadores con ESP32 y Python

## Integrantes del Equipo

| Nombre | Matrícula | Usuario |
| :--- | :--- | :--- |
| **Jose Maximiliano Hernandez Loeza** | S23013991 | Maxloeza18 |
| **Emmanuel Perez Viveros** | S23013933 | Emma612-bit |
| **Daniel Isaac Izquierdo Hernandez** | S23013986 | DaniLeft |

---

## Descripción del Avance

Se implementó la integración de lectura de sensores analógicos (Sensor Térmico LM35 y LDR) y el control de actuadores por PWM mediante comunicación bidireccional JSON vía Serial con Python. 

Adicionalmente, se configuró el control de motor utilizando un módulo controlador en puente H (Drivers Serie L como L298N / L293D), permitiendo la modulación por ancho de pulso (PWM) y el control de dirección de giro.

---

## Mapeo de Hardware y Pines (ESP32)

| Componente | Pin ESP32 | Descripción |
| :--- | :--- | :--- |
| **LM35 (Sensor Térmico)** | GPIO 34 | Lectura analógica ADC (12 bits) |
| **LDR (Sensor Fotorresistencia)** | GPIO 32 | Lectura analógica ADC (12 bits) |
| **Módulo L (ENA / PWM Motor)** | GPIO 18 | Canal PWM 0 (Frecuencia: 5 kHz, Res: 8 bits) |
| **Módulo L (IN1 / Dir A)** | GPIO 22 | Salida digital dirección de motor |
| **Módulo L (IN2 / Dir B)** | GPIO 23 | Salida digital dirección de motor |
| **LED de Potencia** | GPIO 19 | Canal PWM 1 (Frecuencia: 5 kHz, Res: 8 bits) |

---

## Código Fuente (`src/main.cpp`)

```cpp
#include <Arduino.h>
#include <ArduinoJson.h>

// Asignación de Pines
const int PIN_TEMP_SENSOR = 34; // ADC Sensor Térmico
const int PIN_LDR_SENSOR  = 32; // ADC Sensor LDR

// Control de Motor/Ventilador (Módulo Puente H - L298N / L293D)
const int PIN_FAN_PWM   = 18;   // ENA en L298N (Habilitador PWM)
const int PIN_FAN_DIR1  = 22;   // IN1 en L298N (Dirección A)
const int PIN_FAN_DIR2  = 23;   // IN2 en L298N (Dirección B)

// Control de LED
const int PIN_LED_PWM   = 19;   // PWM LED de Potencia

// Configuración LEDC (PWM 5kHz)
const int PWM_FREQ        = 5000;
const int PWM_RESOLUTION  = 8;  // Rango 0-255
const int FAN_PWM_CHANNEL = 0;
const int LED_PWM_CHANNEL = 1;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  // Configuración de pines de dirección del motor
  pinMode(PIN_FAN_DIR1, OUTPUT);
  pinMode(PIN_FAN_DIR2, OUTPUT);

  // Sentido de giro inicial por defecto
  digitalWrite(PIN_FAN_DIR1, HIGH);
  digitalWrite(PIN_FAN_DIR2, LOW);

  // Configuración de canales PWM en ESP32
  ledcSetup(FAN_PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PIN_FAN_PWM, FAN_PWM_CHANNEL);

  ledcSetup(LED_PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PIN_LED_PWM, LED_PWM_CHANNEL);

  // Estado inicial actuadores apagados
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
        
        // Cambio de dirección de giro según el signo del duty cycle
        if (fanDuty < 0) {
          digitalWrite(PIN_FAN_DIR1, LOW);
          digitalWrite(PIN_FAN_DIR2, HIGH);
          fanDuty = abs(fanDuty);
        } else {
          digitalWrite(PIN_FAN_DIR1, HIGH);
          digitalWrite(PIN_FAN_DIR2, LOW);
        }

        ledcWrite(FAN_PWM_CHANNEL, constrain(fanDuty, 0, 255));
      }

      if (docIn.containsKey("led_duty")) {
        int ledDuty = docIn["led_duty"];
        ledcWrite(LED_PWM_CHANNEL, constrain(ledDuty, 0, 255));
      }
    }
  }
}
```

---

## Formato de Mensajes JSON

### Telemetría enviada a Python (Salida Serial):
```json
{"temp": 24.5, "ldr": 1850}
```

### Comandos recibidos de Python (Entrada Serial):
```json
{"fan_duty": 200, "led_duty": 128}
```
*Nota: Si `fan_duty` se envía negativo (ej. `-150`), el sistema invertirá la dirección de giro del motor.*