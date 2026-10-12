# Práctica 03 | Implementación Física de Nodos IoT Heterogéneos en C++ (ESP32)

![Plataforma](https://img.shields.io/badge/Plataforma-ESP32-0A7E8C)
![Lenguaje](https://img.shields.io/badge/Lenguaje-C%2B%2B-00599C)
![Entorno](https://img.shields.io/badge/Entorno-Arduino%20IDE%20%7C%20PlatformIO-5B7F3B)
![Estado](https://img.shields.io/badge/Estado-En%20desarrollo-yellow)

## Descripción

Esta práctica consiste en implementar **nodos IoT heterogéneos** sobre un microcontrolador **ESP32** utilizando **C++** y los principios de **programación orientada a objetos (POO)**.

Como continuación de la arquitectura jerárquica diseñada en Python durante la *Práctica 02*, se traslada al hardware real una estructura de **herencia, encapsulamiento y polimorfismo**. El propósito es gestionar sensores y actuadores mediante una interfaz común, sin que el ciclo principal necesite conocer el tipo concreto de cada dispositivo.

## Objetivo

Diseñar e implementar una jerarquía de clases en C++ capaz de inicializar y controlar diferentes dispositivos físicos conectados al ESP32, aplicando:

- **Herencia:** derivar sensores y actuadores de una clase base `NodoIoT`.
- **Encapsulamiento:** proteger los atributos internos y validar los cambios de configuración.
- **Polimorfismo:** ejecutar acciones específicas mediante el mismo método virtual `ejecutarAccion()`.
- **Integración de hardware:** leer una entrada y controlar una salida del ESP32.
- **Monitoreo:** registrar lecturas y eventos mediante el puerto serie a **115200 baudios**.

## Tecnologías y materiales

| Elemento | Uso |
| --- | --- |
| ESP32 | Microcontrolador principal |
| C++ | Implementación de clases y lógica de control |
| Arduino IDE o PlatformIO | Edición, compilación y carga del programa |
| Sensor analógico (LDR, LM35 o potenciómetro) | Adquisición de una señal de entrada |
| LED, relé, zumbador o ventilador | Actuación o indicación de salida |
| Protoboard, resistencias y cables | Montaje del circuito |
| Monitor serie | Visualización de lecturas y eventos |

> **Montaje de referencia:** para realizar una prueba inicial sencilla, puede utilizarse un potenciómetro conectado a `GPIO34` y un LED conectado a `GPIO23` mediante una resistencia limitadora de corriente. El hardware definitivo debe coincidir con el utilizado en las evidencias.

## Arquitectura de software

La clase base **`NodoIoT`** define los atributos y operaciones comunes de la red. Dos clases derivadas especializan su comportamiento según el hardware conectado.

```text
                    NodoIoT
          ┌─────────────────────────┐
          │ # idDispositivo: String │
          │ # pin: int              │
          │ # conectado: bool       │
          │ + iniciar()             │
          │ + ejecutarAccion()      │
          └────────────┬────────────┘
                       │
             ┌─────────┴─────────┐
             │                   │
     NodoSensorFisico    NodoActuadorFisico
     ┌───────────────┐   ┌────────────────┐
     │ - _umbralAlerta│   │ - _estadoActivo│
     │ + setUmbral() │   │ + ejecutarAccion()│
     │ + ejecutarAccion()│ └────────────────┘
     └───────────────┘
```

### 1. Superclase `NodoIoT`

Representa cualquier dispositivo conectado al sistema.

- **Atributos:** `idDispositivo` (`String`), `pin` (`int`) y `conectado` (`bool`).
- **Constructor:** `NodoIoT(String id, int pinHardware)`.
- **`virtual void iniciar()`:** prepara el hardware, incluyendo la configuración de `pinMode()` según corresponda.
- **`virtual void ejecutarAccion()`:** proporciona una interfaz polimórfica para el comportamiento específico de cada nodo; puede declararse virtual puro si no existe una implementación general.

### 2. Subclase `NodoSensorFisico`

Hereda de `NodoIoT` y se encarga de obtener mediciones físicas.

- **Encapsulamiento:** almacena de forma privada el umbral `_umbralAlerta`.
- **Validación:** el método de configuración del umbral acepta únicamente valores entre **0 y 4095** para una lectura ADC de 12 bits.
- **Polimorfismo:** sobrescribe `ejecutarAccion()` para leer el sensor con `analogRead()` y comunicar el resultado por el monitor serie.
- **Alerta:** la lectura puede compararse con el umbral configurado para registrar un evento.

### 3. Subclase `NodoActuadorFisico`

Hereda de `NodoIoT` y controla un elemento físico de salida.

- **Encapsulamiento:** mantiene el estado de activación `_estadoActivo` como atributo privado.
- **Polimorfismo:** sobrescribe `ejecutarAccion()` para modificar la salida con `digitalWrite()` o, cuando corresponda, con las funciones PWM del ESP32.
- **Aplicaciones:** LED, módulo de relé, zumbador o motor mediante una etapa de potencia adecuada.

### 4. Gestión mediante un arreglo polimórfico

El programa administra instancias de distintos tipos a través de punteros a la clase base `NodoIoT`:

```cpp
NodoIoT* red[2];

void setup() {
    Serial.begin(115200);

    red[0] = new NodoSensorFisico("SENS_TEMP", 34);
    red[1] = new NodoActuadorFisico("ACT_RELE", 23);

    for (NodoIoT* nodo : red) {
        nodo->iniciar();
    }
}

void loop() {
    for (NodoIoT* nodo : red) {
        nodo->ejecutarAccion();
    }

    delay(500);
}
```

> Este fragmento **ilustra la integración** de las clases; no sustituye sus declaraciones, implementaciones ni la configuración específica de cada dispositivo. Los identificadores `SENS_TEMP` y `ACT_RELE` son ejemplos y deben ajustarse al hardware realmente utilizado.

## Conexiones físicas de referencia

Para una prueba con **potenciómetro y LED**, el cableado puede ser el siguiente:

| Componente | Terminal | Conexión en ESP32 |
| --- | --- | --- |
| Potenciómetro | Extremo 1 | `3V3` |
| Potenciómetro | Terminal central (cursor) | `GPIO34` (ADC) |
| Potenciómetro | Extremo 2 | `GND` |
| LED | Ánodo (+), mediante una resistencia de 220–330 Ω | `GPIO23` |
| LED | Cátodo (−) | `GND` |

**Precauciones:** las entradas del ESP32 no son tolerantes a 5 V; no se debe aplicar más de 3.3 V a `GPIO34`. Este GPIO es **solo de entrada**. Los motores y relés que requieran más corriente no deben alimentarse directamente desde un pin: necesitan un controlador o módulo apropiado y protección eléctrica según el dispositivo.

## Estructura del repositorio

```text
.
├── .gitignore
├── AUTHORS.md
├── README.md
└── practica-03/
    ├── src/
    │   ├── NodoIoT.h
    │   ├── NodoIoT.cpp
    │   ├── NodoSensorFisico.h
    │   ├── NodoSensorFisico.cpp
    │   ├── NodoActuadorFisico.h
    │   ├── NodoActuadorFisico.cpp
    │   └── practica-03.ino
    └── docs/
        └── Reporte_Evidencias_P3.pdf
```

> La estructura de `src/` es una **propuesta de organización modular**. También puede emplearse otra distribución compatible con Arduino IDE o PlatformIO, siempre que se entregue el código fuente dentro de `practica-03/src/`. Los archivos mostrados deben existir en la versión final del repositorio.

## Cómo ejecutar la práctica

1. Instalar **Arduino IDE** con el soporte de placas **ESP32** o configurar un proyecto equivalente en **PlatformIO**.
2. Incorporar los archivos `.h` y `.cpp` al proyecto y abrir el archivo principal `.ino` desde una carpeta de sketch compatible con Arduino IDE. Si se usa PlatformIO, adaptar el punto de entrada y su estructura de proyecto.
3. Conectar el sensor y el actuador según el circuito documentado.
4. Seleccionar la placa ESP32 y el puerto serie correspondiente.
5. Compilar y cargar el programa en el microcontrolador.
6. Abrir el **Monitor Serie a 115200 baudios**.
7. Modificar la señal del sensor y observar las lecturas, alertas y respuestas del actuador según la lógica implementada.

## Comportamiento esperado

- Cada nodo se inicializa utilizando la interfaz común `iniciar()`.
- El sensor registra sus lecturas ADC mediante `analogRead()`.
- El umbral de alerta solo admite valores válidos de 0 a 4095.
- El actuador ejecuta su acción de salida utilizando su propia implementación.
- El ciclo principal recorre el arreglo `NodoIoT*` y ejecuta `ejecutarAccion()` **sin identificar manualmente la clase concreta** de cada objeto.
- El Monitor Serie muestra los eventos del sistema a 115200 baudios.

> **Nota:** el comportamiento descrito constituye el resultado esperado de la práctica; su validación debe documentarse mediante las pruebas y evidencias reales.

## Evidencias de la práctica

El archivo [`practica-03/docs/Reporte_Evidencias_P3.pdf`](practica-03/docs/Reporte_Evidencias_P3.pdf) debe contener:

- Diagrama esquemático de conexiones del ESP32.
- Fotografías claras del circuito físico montado en protoboard.
- Explicación de la relación entre herencia, encapsulamiento y polimorfismo y su aplicación al código.
- Registros del Monitor Serie y resultados de pruebas con el hardware.
- Enlace público al video demostrativo de funcionamiento (**duración máxima de 3 minutos**).

**Video demostrativo:** pendiente de agregar el enlace público.

## Checklist de entrega

- [ ] Implementación modular en C++ con herencia, encapsulamiento y métodos `virtual`.
- [ ] Inicialización de la clase base mediante lista de inicialización del constructor derivado.
- [ ] Validación privada del umbral del sensor en el intervalo 0–4095.
- [ ] Arreglo de punteros `NodoIoT*` utilizado en el ciclo principal del ESP32.
- [ ] Lectura de al menos un sensor y control de al menos un actuador físico.
- [ ] Monitor Serie configurado a 115200 baudios.
- [ ] Prueba funcional con respuesta del circuito ante variaciones del sensor.
- [ ] Reporte PDF con esquemático, fotografías y resultados.
- [ ] Video público de máximo 3 minutos enlazado en el reporte.
- [ ] Archivos organizados en `practica-03/src/` y `practica-03/docs/`.
- [ ] Archivos `.gitignore` y `AUTHORS.md` ubicados en la raíz del repositorio.

## Integrantes

Consultar [`AUTHORS.md`](AUTHORS.md) para conocer a los integrantes del equipo y sus contribuciones.

---

**Práctica 03 — Programación orientada a objetos aplicada a hardware IoT con ESP32.**
